#include <Arduino.h>
#include <SoftwareSerial.h>
#include "math.h"

const int arrayPhotoLength = 5;
float arrayPhoto[arrayPhotoLength];
int arrayPhotoPosition = 0;
SoftwareSerial serial(PA10, PA9);
const int nb_pwr = PC8;
const int nb_rst = PC9;
const int nb_delay_const = 5000;
const int photo = PA0;
const int flush_light = PB0;
const int led1 = PA5;

float mean(float array[], int size){
    float sum = 0;
    for (int i = 0; i < size; ++i) {
        sum += array[i];
    }
    return sum / size;
}

void calibrate(float array[], int size){
    for (int i = 0; i < size; ++i) {
        digitalWrite(led1, LOW);
        float value = analogRead(photo);
        array[i] = value;
        delay(15);
        digitalWrite(led1, HIGH);
    }
}

int get_light(float resistor_params){
    const int min_x = 480;
    const int max_x = 800;
    const int max_y = 255;
    const float ratio = (float) max_y / (float) (max_x - min_x);
    if (resistor_params <= min_x){
        return 0;
    }
    if (resistor_params >= max_x){
        return 255;
    }
    float params = resistor_params - min_x;
    return floor(params * ratio);
}
void setup(){
    serial.begin(9600);
    serial.println("Init");
    pinMode(nb_pwr, OUTPUT);
    pinMode(nb_rst, OUTPUT);
    pinMode(photo, INPUT);
    pinMode(led1, OUTPUT);
    pinMode(flush_light, OUTPUT);
    digitalWrite(nb_rst, LOW);
    digitalWrite(nb_pwr, HIGH);
    digitalWrite(led1, HIGH);
    delay(500);
    digitalWrite(nb_pwr, LOW);
    delay(nb_delay_const);
    serial.println("Ok");
    calibrate(arrayPhoto, arrayPhotoLength);
    analogWrite(flush_light, 1024);
    delay(1000);
    analogWrite(flush_light, 0);
}
void loop(){
    arrayPhoto[arrayPhotoPosition] = analogRead(photo);
    arrayPhotoPosition = (arrayPhotoPosition + 1) % arrayPhotoLength;
    float p = mean(arrayPhoto, arrayPhotoLength);
    int f = get_light(p);
    serial.print("Value is ");
    serial.print(p);
    serial.print(" light is ");
    serial.println(f);
    analogWrite(flush_light, f);
    delay(1000);
}

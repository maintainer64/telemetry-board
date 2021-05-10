#include <Arduino.h>
#include <SoftwareSerial.h>
#include <AxisElementary.h>
#include <GpsElementary.h>
const uint8_t DS1721TempI2C7bitAddr = 0x48;
const uint8_t LIS3DHI2C7bitAddr = 0x18;
const int led_port = PC7;
const int photo_resistor = PA0;
SoftwareSerial serial(PA10, PA9);
SoftwareSerial serial_gps_module(PA3, PA2);
AxisElementary axis(I2C_MODE, LIS3DHI2C7bitAddr);
GpsElementary gps;

void setup() {
    serial.begin(9600);
    serial_gps_module.begin(9600);
    delay(1000);
    serial.println(axis.begin());
    serial.println(gps.begin(serial_gps_module));
    pinMode(led_port, OUTPUT);
    pinMode(photo_resistor, INPUT);
    digitalWrite(led_port, LOW);
}

void loop() {
    delay(1000);
    auto axis_d = axis.read();
    auto axis_p = toPrintAxisElementaryMm(axis_d);
    serial.println(axis_p);

    auto gps_d = gps.read();
    auto gps_p = toPrintGpsElementaryLocation(gps_d);
    serial.println(gps_p);

    int val = analogRead(photo_resistor);
    serial.println(val);
}

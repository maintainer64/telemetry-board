#include <Arduino.h>
#include <SoftwareSerial.h>
#include <SlowSoftI2CMaster.h>
#include <DS1721Temp.h>

SoftwareSerial serial(PA10, PA9);
SlowSoftI2CMaster i2c1(14, 15, true);
DS1721Temp sensor(i2c1, 0x90, serial);
void setup() {
    serial.begin(9600);
    auto info = i2c1.i2c_init() ? "Success init I2C" : "Not work module I2C";
    serial.println(info);
    info = sensor.init() ? "Success init Temperature" : "Not work module Temperature";
    serial.println(info);
}

void loop() {
    int temperature = sensor.readTemperature();
    serial.print("Temperature:");
    serial.println(temperature);
    delay(1000);
}

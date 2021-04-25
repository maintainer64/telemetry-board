//
// Created by Profes_sional on 18.04.2021.
//

#include <SlowSoftI2CMaster.h>
#include "ScanI2C.h"

void ScanI2C::SetPrinter(SoftwareSerial &serial_){
    _serial = serial_;
    _serial.println("I2C Scanner re-init");
}

void ScanI2C::GetInfo(){
    uint8_t add = 0;
    int found = false;
    _serial.println("Scanning ...");

    _serial.println("       8-bit 7-bit addr");
    // try read
    do {
        if (_si.i2c_start(add | I2C_READ)) {
            found = true;
            _si.i2c_read(true);
            _si.i2c_stop();
            _serial.print("Read:   0x");
            if (add < 0x0F) _serial.print(0, HEX);
            _serial.print(add+I2C_READ, HEX);
            _serial.print("  0x");
            if (add>>1 < 0x0F) _serial.print(0, HEX);
            _serial.println(add>>1, HEX);
        } else _si.i2c_stop();
        add += 2;
    } while (add);

    // try write
    add = 0;
    do {
        if (_si.i2c_start(add | I2C_WRITE)) {
            found = true;
            _si.i2c_stop();
            _serial.print("Write:  0x");
            if (add < 0x0F) _serial.print(0, HEX);
            _serial.print(add+I2C_WRITE, HEX);
            _serial.print("  0x");
            if (add>>1 < 0x0F) _serial.print(0, HEX);
            _serial.println(add>>1, HEX);
        } else _si.i2c_stop();
        _si.i2c_stop();
        add += 2;
    } while (add);
    if (!found) _serial.println("No I2C device found.");
    _serial.println("Done\n\n");
    delay(1000);
}

ScanI2C::ScanI2C(SlowSoftI2CMaster &si_, SoftwareSerial &serial_){
    _si = si_;
    _serial = serial_;
    _serial.println("I2C Scanner init");
}
//
// Created by Professional on 20.04.2021.
//
#include "DS1721Temp.h"
#include <SoftwareSerial.h>

void DS1721Temp::debug(const String &string){
    _serial.print("[DS1721Temp] ");
    _serial.println(string);
}

DS1721Temp::DS1721Temp(SlowSoftI2CMaster &i2c_master_, uint8_t address_, SoftwareSerial &serial_){
    i2c_master = i2c_master_;
    address = address_;
    is_init = false;
    _serial = serial_;
}

bool DS1721Temp::init(){
    if (!i2c_master.i2c_start(address | I2C_WRITE)) {
        debug("Init not start by address");
        return false;
    }
    if (!i2c_master.i2c_write(to_init_byte)) {
        debug("Init not start by init_byte");
        return false;
    }
    // i2c_master.i2c_stop();
    is_init = true;
    return true;
}

bool DS1721Temp::startActionReadTemperature(){
    if (!i2c_master.i2c_start(address | I2C_WRITE)) {
        debug("readTemperatureError by address");
        return readTemperatureError;
    }
    if (!i2c_master.i2c_write(to_read_byte)) {
        debug("readTemperatureError by to_read_byte");
        return false;
    }
    return true;
}

int DS1721Temp::readTemperature(){
    if (!is_init & !init()){
        return initTemperatureError;
    }
    if (!startActionReadTemperature()) {
        return readTemperatureError;
    }
    if (!i2c_master.i2c_start(address | I2C_READ)) {
        debug("readTemperatureError by address to read");
        return readTemperatureError;
    }
    uint8_t msb = i2c_master.i2c_read(false);
    uint8_t lsb = i2c_master.i2c_read(true);
    int ans = (int) msb * 256 + (int) lsb;
    // i2c_master.i2c_stop();
    return ans;
}

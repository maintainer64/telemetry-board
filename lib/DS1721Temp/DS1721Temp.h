//
// Created by Professional on 20.04.2021.
//

#ifndef MTS_SUB_BOARD_DS1721TEMP_H
#define MTS_SUB_BOARD_DS1721TEMP_H

#include <SlowSoftI2CMaster.h>
#include <SoftwareSerial.h>

class DS1721Temp {
private:
    bool is_init = false;
    uint8_t to_init_byte = 0x51;
    uint8_t to_read_byte = 0xAA;
    bool startActionReadTemperature();
    SoftwareSerial _serial = {0x00, 0x01};
protected:
    SlowSoftI2CMaster i2c_master = {0x00, 0x01};
    uint8_t address = 0x90;
    void debug(const String &string);
public:
    int readTemperatureError = -1000;
    int initTemperatureError = -2000;
    DS1721Temp(SlowSoftI2CMaster &i2c_master_, uint8_t address_, SoftwareSerial &serial_);
    bool init();
    int readTemperature();
};


#endif //MTS_SUB_BOARD_DS1721TEMP_H

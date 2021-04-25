//
// Created by Professional on 18.04.2021.
//

#ifndef MTS_SUB_BOARD_SCANI2C_H
#define MTS_SUB_BOARD_SCANI2C_H
#include <SoftwareSerial.h>
#include <SlowSoftI2CMaster.h>

class ScanI2C {
protected:
    SoftwareSerial _serial = {0x00, 0x01};
    SlowSoftI2CMaster _si = {14, 15};
public:
    ScanI2C(SlowSoftI2CMaster &si_, SoftwareSerial &serial_);
    void SetPrinter(SoftwareSerial &serial_);
    void GetInfo();
};


#endif //MTS_SUB_BOARD_SCANI2C_H

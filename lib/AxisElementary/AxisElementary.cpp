//
// Created by Professional on 26.04.2021.
//

#include "AxisElementary.h"

AxisElementary::AxisElementary(uint8_t busType, uint8_t inputArg) : LIS3DH(busType, inputArg){

}

String AxisElementary::begin() {
    return LIS3DH::begin() == IMU_SUCCESS ? "[AxisElementary] Success init Axis" : "[AxisElementary] Not work module Axis";
}

AxisElementaryMm AxisElementary::read(){
    const int ratio = 1000;
    return AxisElementaryMm{
            (int) (readFloatAccelX() * ratio),
            (int) (readFloatAccelY() * ratio),
            (int) (readFloatAccelZ() * ratio)
    };
}

String toPrintAxisElementaryMm(AxisElementaryMm &data){
    return "{'aX':'" + String(data.x) + "','aY':'" + String(data.y) + "','aZ':'"+ String(data.z) + "'}";
}

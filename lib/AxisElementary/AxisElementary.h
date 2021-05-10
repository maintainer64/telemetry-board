//
// Created by Professional on 26.04.2021.
//

#ifndef MTS_SUB_BOARD_AXISELEMENTARY_H
#define MTS_SUB_BOARD_AXISELEMENTARY_H

#include <SparkFunLIS3DH.h>
#include <Arduino.h>
struct AxisElementaryMm{
    int x;
    int y;
    int z;
};

String toPrintAxisElementaryMm(AxisElementaryMm &data);

class AxisElementary: public LIS3DH{
public:
    AxisElementary(uint8_t busType, uint8_t inputArg);
    AxisElementaryMm read();
    String begin();
};


#endif //MTS_SUB_BOARD_AXISELEMENTARY_H

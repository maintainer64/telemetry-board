//
// Created by Professional on 10.05.2021.
//

#ifndef MTS_SUB_BOARD_GPSELEMENTARY_H
#define MTS_SUB_BOARD_GPSELEMENTARY_H

#include <iarduino_GPS_NMEA.h>
struct GpsElementaryLocation{
    float latitude;
    float longitude;
    bool is_valid;
};
String toPrintGpsElementaryLocation(GpsElementaryLocation &data);

class GpsElementary: public iarduino_GPS_NMEA{
public:
    String begin(SoftwareSerial &i);
    GpsElementaryLocation read();
};


#endif //MTS_SUB_BOARD_GPSELEMENTARY_H

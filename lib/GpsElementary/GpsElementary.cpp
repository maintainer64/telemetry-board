//
// Created by Professional on 10.05.2021.
//

#include "GpsElementary.h"
String GpsElementary::begin(SoftwareSerial &i){
    return iarduino_GPS_NMEA::begin(i) ? "[GpsElementary] Success init GpsModule" : "[GpsElementary] Not work module Gps";
}

GpsElementaryLocation GpsElementary::read(){
    iarduino_GPS_NMEA::read();
    if(iarduino_GPS_NMEA::errPos){
        return GpsElementaryLocation{0, 0, 0};
    }
    return GpsElementaryLocation{latitude, longitude, 1};
}

String toPrintGpsElementaryLocation(GpsElementaryLocation &data){
    return "{'latitude':'" + String(data.latitude) + "','longitude':'"+ String(data.longitude) + "','GNSS_data_valid':'"+ String((int) data.is_valid) + "'}";
}
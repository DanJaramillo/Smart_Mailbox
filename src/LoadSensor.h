#ifndef LOADSENSOR_H
#define LOADSENSOR_H

#include <arduino.h>

#include "HX711.h"

class LoadSensor: public HX711 {
    public:
        /**
         * Constructors
         * All constructors require setting the data pin and the clock pin to use the underlaying HX711 ADC. 
         * Added constructors allow setting the offset and scale factors.
        */
        LoadSensor(uint32_t d_pin, uint32_t c_pin);
        LoadSensor(uint32_t d_pin, uint32_t c_pin, int32_t offset);
        LoadSensor(uint32_t d_pin, uint32_t c_pin, int32_t offset, float scale);

        /**
         * tare()
         * Sets the offset for the zero measurement. Defaults to 16 samples to reduce noise.
        */
        int32_t tare(uint16_t samples = 16);


        /**
         * scale()
         * Sets the scale factor to calibrate the load sensor. Offset should be calibrated first.
        */
        float scale(float test_load, uint16_t samples = 16);

        /**
         * measure()
         * Using the scale factor and offset, calculates the force applied to the load cell. 
         * Offset and scale factor should be set first.
        */
        float measure(uint16_t samples = 16);

    private:
        int32_t m_offset;
        float m_scale;

};

#endif
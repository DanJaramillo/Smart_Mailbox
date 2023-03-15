#ifndef LOADSENSOR_H
#define LOADSENSOR_H

#include <arduino.h>

#include "HX711.h"

class LoadSensor: public HX711 {
    public:
        /**
         * Constructors
        */
        LoadSensor(uint32_t d_pin, uint32_t c_pin);
        LoadSensor(uint32_t d_pin, uint32_t c_pin, int32_t offset);
        LoadSensor(uint32_t d_pin, uint32_t c_pin, int32_t offset, float scale);

        /**
         * tare()
         * Sets the offset for the zero measurement. Defaults to 16 samples to reduce noise.
        */
        void tare(uint16_t samples = 16);


        /**
         * scale()
         * Sets the scale factor to calibrate the load sensor.
        */
        void scale(float test_load, uint16_t samples = 16);

        /**
         * measure()
         * 
        */
        float measure(uint16_t samples = 16);

    private:
        int32_t m_offset;
        float m_scale;

};

#endif
#include "LoadSensor.h"

LoadSensor::LoadSensor(uint32_t d_pin, uint32_t c_pin) : HX711(d_pin, c_pin), m_offset(0), m_scale(1) { }

LoadSensor::LoadSensor(uint32_t d_pin, uint32_t c_pin, int32_t offset) : HX711(d_pin, c_pin), m_offset(0), m_scale(1) {}

LoadSensor::LoadSensor(uint32_t d_pin, uint32_t c_pin, int32_t offset, float scale) : HX711(d_pin, c_pin), m_offset(offset), m_scale(scale) {}

int32_t LoadSensor::tare(uint16_t samples = 16) {
    int32_t offset = 0, temp = 0;
    for(int i = 0; i < samples; i++) {
        temp = read();
        if(temp == INT32_MIN) {
            return temp;
        }
        offset += temp;
    }
    offset /= samples;
    m_offset = offset;
    return offset;
}

float LoadSensor::scale(float test_load, uint16_t samples = 16) {}

float LoadSensor::measure(uint16_t samples = 16);
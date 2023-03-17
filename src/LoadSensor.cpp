#include "LoadSensor.h"

LoadSensor::LoadSensor(uint32_t d_pin, uint32_t c_pin) : HX711(d_pin, c_pin), m_offset(0), m_scale(1) { }

LoadSensor::LoadSensor(uint32_t d_pin, uint32_t c_pin, int32_t offset) : HX711(d_pin, c_pin), m_offset(0), m_scale(1) {}

LoadSensor::LoadSensor(uint32_t d_pin, uint32_t c_pin, int32_t offset, float scale) : HX711(d_pin, c_pin), m_offset(offset), m_scale(scale) {}

int32_t LoadSensor::tare(uint16_t samples = 16) {
    int32_t temp = 0;
    for(int i = 0; i < samples; i++) {
        temp = read();
        if(temp == INT32_MIN) {
            // Check for error with HX711 Sensor
            return temp;
        }
        m_offset += temp;
    }
    m_offset /= samples;
    return m_offset;
}

float LoadSensor::scale(float test_load, uint16_t samples = 16) {
    int32_t measurement = 0, temp = 0;
    for(int i = 0; i < samples; i++) {
        temp = read();
        if(temp == INT32_MIN) {
            // Check for error with HX711 Sensor
            return temp;
        }
        measurement += temp;
    }
    m_scale = test_load / (float)(measurement / samples - m_offset);
    return m_scale;
}

float LoadSensor::measure(uint16_t samples = 16) {
    int32_t measurement = 0, temp = 0;
    for(int i = 0; i < samples; i++) {
        temp = read();
        if(temp == INT32_MIN) {
            // Check for error with HX711 Sensor
            return temp;
        }
        measurement += temp;
    }
    measurement /= samples;

    return (measurement - m_offset) * m_scale;
}
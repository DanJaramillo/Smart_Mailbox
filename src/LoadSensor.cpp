#include "LoadSensor.h"

LoadSensor::LoadSensor(uint32_t d_pin, uint32_t c_pin) : HX711(d_pin, c_pin), m_offset(0), m_scale(1) { }

LoadSensor::LoadSensor(uint32_t d_pin, uint32_t c_pin, int32_t offset) : HX711(d_pin, c_pin), m_offset(0), m_scale(1) {}

LoadSensor::LoadSensor(uint32_t d_pin, uint32_t c_pin, int32_t offset, float scale) : HX711(d_pin, c_pin), m_offset(offset), m_scale(scale) {}

void tare(uint16_t samples = 16);

void scale(float test_load, uint16_t samples = 16);

float measure(uint16_t samples = 16);
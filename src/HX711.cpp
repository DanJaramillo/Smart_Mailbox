#include "HX711.h"

HX711::HX711(uint32_t data_pin, uint32_t clock_pin) : m_data_pin(data_pin), m_clock_pin(clock_pin), m_mode(a_128) { 
    pinMode(m_data_pin, INPUT_PULLUP);
    pinMode(m_clock_pin, OUTPUT);
}

bool HX711::is_ready() {
    return m_mode && !digitalRead(m_data_pin);
}

int32_t HX711::read() {
    m_raw_data = 0;

    uint32_t i = 0;
    // read data
    for(; i < data_width; i++) {
        digitalWrite(m_clock_pin, HIGH);
        delayMicroseconds(clock_high_time);
        m_raw_data = m_raw_data << 1;
        m_raw_data = m_raw_data | digitalRead(m_data_pin);
        digitalWrite(m_clock_pin, LOW);
        delayMicroseconds(clock_low_time);
    }

    // set mode
    for(; i < m_mode; i++) {
        digitalWrite(m_clock_pin, HIGH);
        delayMicroseconds(clock_high_time);
        digitalWrite(m_clock_pin, LOW);
        delayMicroseconds(clock_low_time);
    }

    return m_raw_data;
}

int32_t HX711::read(hx711_mode mode) {
    m_raw_data = 0;

    uint32_t i = 0;
    // read data
    for(; i < data_width; i++) {
        digitalWrite(m_clock_pin, HIGH);
        delayMicroseconds(clock_high_time);
        m_raw_data = m_raw_data << 1;
        m_raw_data = m_raw_data | digitalRead(m_data_pin);
        digitalWrite(m_clock_pin, LOW);
        delayMicroseconds(clock_low_time);
    }

    // finish mode
    for(; i < mode; i++) {
        digitalWrite(m_clock_pin, HIGH);
        delayMicroseconds(clock_high_time);
        digitalWrite(m_clock_pin, LOW);
        delayMicroseconds(clock_low_time);
    }

    return m_raw_data;
}

inline void HX711::power_down() {
    digitalWrite(m_clock_pin, HIGH);
    delayMicroseconds(power_down_time);
    m_mode = a_128;
}

inline void HX711::power_up() {
    digitalWrite(m_clock_pin, LOW);
}
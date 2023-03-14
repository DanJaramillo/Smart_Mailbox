#include "HX711.h"

HX711::HX711(uint32_t data_pin, uint32_t clock_pin) : m_data_pin(data_pin), m_clock_pin(clock_pin), m_mode(a_128) { 
    pinMode(m_data_pin, INPUT_PULLUP);
    pinMode(m_clock_pin, OUTPUT);
    digitalWrite(m_clock_pin, LOW);
}

bool HX711::is_ready() {
    return m_mode && !digitalRead(m_data_pin);
}

int32_t HX711::read() {
    //exit if powered down
    if(m_mode == off)
        return -1;
    
    // wait for ready
    while(!is_ready()) {
        ;
    }

    int32_t data = 0;
    uint16_t i = 0;
    // read data
    for(; i < data_width; i++) {
        digitalWrite(m_clock_pin, HIGH);
        delayMicroseconds(clock_high_time);

        data = data << 1;
        data = data | digitalRead(m_data_pin);

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

    return sign_extend_24_32(data);
}

HX711::hx711_mode HX711::get_mode() {
    return m_mode;
}

void HX711::set_mode(hx711_mode mode) {
    // check if changing to off
    if(mode == off) {
        power_down();
    }
    else {
        // check if currently off
        if(m_mode == off) {
            power_up();
        }

        // wait for ready
        while(!is_ready()) {
            ;
        }
        for(uint16_t i = 0; i < mode; i++) {
            digitalWrite(m_clock_pin, HIGH);
            delayMicroseconds(clock_high_time);

            digitalWrite(m_clock_pin, LOW);
            delayMicroseconds(clock_low_time);
        }
    }
    m_mode = mode;
} 

inline void HX711::power_down() {
    digitalWrite(m_clock_pin, HIGH);
    m_mode = off;
}

inline void HX711::power_up() {
    digitalWrite(m_clock_pin, LOW);
    m_mode = a_128;
}

/**
 * sign_extend_24_32()
 * Sign extend the 24 bit 2s compliment number to 32 bit 2s compliment.
 * Takes advantage of right shift being an arithmetic shift.
*/
int32_t HX711::sign_extend_24_32(int32_t x) {
    x = x << 8;
    x = x >> 8;
    return x;
}
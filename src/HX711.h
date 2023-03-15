/**
 * HX711 Driver
*/
#ifndef HX711_H
#define HX711_H

#include <arduino.h>

class HX711 {
    public:
        /**
         * hx711_mode: gain and channel selection
         * a_128 = Channel A with gain of 128, b_32 = Channel B with gain of 32, or a_64 = Channel A with gain of 64
        */
        typedef enum{off = 0, a_128=25, b_32=26, a_64=27} hx711_mode;

        /**
         * Constructor
         * Sets data pin and clock pin to input and output respectively. Turns on HX711 with default mode of channel A and gain of 128.
        */
        HX711(uint32_t d_pin, uint32_t c_pin);

        /**
         * ready()
         * Returns true if HX711 is on and data is ready for retrieval.
        */
        bool is_ready();

        /**
         * read()
         * Waits for ADC to be ready, then returns 24 bit value from ADC using the currently set mode. Returns -1 if ADC is powered down/off.
        */
        int32_t read();

        /**
         * get_mode()
         * Returns the current mode of the HX711.
        */
        hx711_mode get_mode();

        /**
         * set_mode()
         * Changes the ADC mode for future captures. If not already on, powers it on first.
        */
        void set_mode(hx711_mode mode);

        /**
         * power_down()
         * Puts HX711 in powered down mode. Returns after it is powered down.
        */
        void power_down();

        /**
         * power_up()
         * Powers up the HX711. Returns when ADC is ready.
        */
       void power_up();

    private:
        uint32_t    m_data_pin;
        uint32_t    m_clock_pin;
        hx711_mode  m_mode;

        // times are in micro seconds
        const uint32_t  clock_high_time = 1;
        const uint32_t  clock_low_time = 1;
        const uint32_t  power_down_time = 60;

        const uint32_t  data_width = 24;

        /**
         * sign_extend_24_32
         * Sign extend the 24 bit 2s compliment number to 32 bit 2s compliment.
         * Note: Left shift into sign bit is undefined in C++ language and right shift is implementation defined.
         * Both work correctly on Atmel M0 with Arduino Framework.
        */
        int32_t sign_extend_24_32(int32_t x);
};

#endif

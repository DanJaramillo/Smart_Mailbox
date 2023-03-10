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
         * Sets data pin and clock pin.
        */
        HX711(uint32_t d_pin, uint32_t c_pin);

        /**
         * ready()
         * Returns true if the output data is ready for retrieval.
        */
        bool is_ready();

        /**
         * read()
         * Returns raw 24 bits of data captured by ADC using currently set mode. Does not check for ready.
        */
        int32_t read();

        /**
         * read()
         * Returns raw 24 bits of data captured by ADC using previously set mode. Changes ADC mode for future captures. Does not check for ready state.
        */
        int32_t read(hx711_mode mode);

        /**
         * set_mode()
         * Stores 24 bits captured by ADC using previously set mode. Changes the ADC mode for future captures. Does not check for ready state.
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
        int32_t     m_raw_data;

        // micro seconds
        const uint32_t  clock_high_time = 1;
        const uint32_t  clock_low_time = 1;
        const uint32_t  power_down_time = 60;

        const uint32_t  data_width = 24;
};

#endif

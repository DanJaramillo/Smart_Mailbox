#include <Arduino.h>

#include "HX711.h"

HX711 hx711(10, 11);
int count;

void setup() {
    digitalWrite(8, HIGH);                      // Turn off radio
    Serial.begin(9600);
    Serial.println("Serial Console Init");
}

void loop() {
    // wait for ADC
    while(!hx711.is_ready())
        ;
    Serial.print(count++);
    Serial.print(" : ADC = ");
    Serial.println(hx711.read());
    delay(100);
}
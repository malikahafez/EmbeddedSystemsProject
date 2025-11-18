#ifndef PUSH_BUTTON_H
#define PUSH_BUTTON_H

// Include Pico SDK headers needed for hardware/gpio.h data types (bool, uint32_t)
#include "pico/stdlib.h" 
#include "hardware/gpio.h"

#define BUTTON_PIN 16 // d4/gpio16 using internal pull-up resistor

#define DEBOUNCE_DELAY 50 // Milliseconds for debouncing

// Function declarations
void button_init();
bool is_button_pressed();
bool was_button_just_pressed(); // More robust for detecting single clicks

#endif // PUSH_BUTTON_H

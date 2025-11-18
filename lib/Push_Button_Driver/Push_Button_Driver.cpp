#include "Push_Button_Driver.h"
#include <Arduino.h> 

static volatile bool button_state = true;      // Default state is now HIGH (not pressed)
static volatile bool last_button_state = true; // Previous reading is HIGH
static volatile long last_debounce_time = 0;

void button_init() {
    // Use SDK functions instead of pinMode(BUTTON_PIN, INPUT_PULLUP);
    gpio_init(BUTTON_PIN);           // Initialize the pin
    gpio_set_dir(BUTTON_PIN, GPIO_IN); // Set direction to input
    gpio_pull_up(BUTTON_PIN);        // Enable internal pull-up resistor
}

bool is_button_pressed() {
    // Use the SDK function gpio_get() instead of digitalRead()
    bool reading = gpio_get(BUTTON_PIN); 

    if (reading != last_button_state) {
        last_debounce_time = millis(); // Using Arduino timekeeping here
    }

    if ((millis() - last_debounce_time) > DEBOUNCE_DELAY) {
        if (reading != button_state) {
            button_state = reading;
        }
    }

    last_button_state = reading;
    
    // Logic Inversion: Return TRUE only when the physical pin reads LOW
    return (button_state == LOW); 
}

bool was_button_just_pressed() {
    static bool previous_press_state = false;
    bool current_press_state = is_button_pressed(); // Use the debounced state (true if pressed)

    // Check for a transition from not-pressed (false) to pressed (true)
    if (current_press_state == true && previous_press_state == false) {
        previous_press_state = current_press_state;
        return true; // A new press event occurred
    }
    
    previous_press_state = current_press_state;
    return false; // No new press event
}

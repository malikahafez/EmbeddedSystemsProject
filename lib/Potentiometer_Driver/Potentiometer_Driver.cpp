#include "POTENTIOMETER_DRIVER.h"
#include <Arduino.h> // Keep this include for the 'map' and 'constrain' functions

void potentiometer_init() {
    // Initialize the ADC hardware
    adc_init();

    // Initialize GPIO 29 for use as an ADC input pin
    adc_gpio_init(POTENTIOMETER_PIN_GPIO);

    // The resolution is 12-bit by default (0-4095) in the SDK.
}

int read_potentiometer_value() {
    // Select the correct ADC channel (Channel 3 corresponds to GPIO 29/A3)
    adc_select_input(POT_ADC_CHANNEL);
    
    // Read the value from the ADC
    return adc_read();
}

int read_potentiometer_mapped(int low_map, int high_map) {
    int raw_value = read_potentiometer_value();
    
    // Use the Arduino map() function to scale the value (Input range is 0 to 4095 for 12-bit ADC)
    int mapped_value = map(raw_value, 0, 4095, low_map, high_map);

    // Ensure the output is constrained to the map bounds
    return constrain(mapped_value, low_map, high_map);
}
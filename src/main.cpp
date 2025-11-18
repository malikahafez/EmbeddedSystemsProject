// #include <Arduino.h>
// #include "pico/stdlib.h"   // Includes common SDK functions (printf, sleep_ms, gpio funcs)
// #include "hardware/gpio.h"   // For specific, low-level GPIO control
// #include "hardware/uart.h"   // For specific UART control, if needed
// #include "hardware/gpio.h"
// #include <Wire.h> 
// // #include <LiquidCrystal_I2C.h>

// #include "LED_Driver.h"
// #include "Potentiometer_Driver.h"
// #include "Push_Button_Driver.h"
// #include "Water_Sensor_Driver.h"
// #include "RFID_READER_DRIVER.h"

// // Set the LCD address to 0x27 or 0x3F (common addresses, check your LCD)
// // LiquidCrystal_I2C lcd(0x27, 16, 2); 

// // put function declarations here:
// // int myFunction(int, int);

// void setup() {
//   // put your setup code here, to run once:
//   // int result = myFunction(2, 3);
//   // Initialize serial communication
//       // Serial.begin(115200); 
//       // Serial.begin(9600);
//       // potentiometer_init();
//       // Initialize digital pin LED_BUILTIN as an output.
//       // pinMode(LED_BUILTIN, OUTPUT);
//   //     lcd.init();      // Initialize the LCD
//   // lcd.backlight(); // Turn on the backlight
//   // lcd.print("Hello, PlatformIO!"); // Print a message to the LCD
// // water_sensor_init();
// //  Serial.println("--- Water Sensor Test Mode ---");
// //   Serial.println("Raw values range from 0 to 4095.");
// Serial.begin(115200);
//   lcd_init();
//   rfid_init();
//   lcd_print("Scan an RFID Tag");

//   // lcd_init();
// // lcd_print("Pot Value:");
//   // lcd_print("Water Level:");
//   // lcd_print("Custom I2C Driver");
//   // lcd_set_cursor(0, 1);
//   // lcd_print("LED test");


//   // LED_init();
//   // button_init();
// }

// void loop() {
//   // put your main code here, to run repeatedly:
//   // digitalWrite(LED_BUILTIN, HIGH); // Turn the LED on
//   //     delay(1000);                     // Wait for a second
//   //     digitalWrite(LED_BUILTIN, LOW);  // Turn the LED off
//   //     delay(1000);                     // Wait for a second
//        // You can update the display here
//   // lcd.setCursor(0, 1); // Move cursor to the second row, first column
//   // lcd.print("Time: ");
//   // lcd.print(millis() / 1000); // Display time in seconds
//     // lcd_set_cursor(0, 1); // Move cursor to the second row, first column
//     // delay(2000);
//   // lcd_print("Time: ");
//   // lcd_print_number(millis() / 1000); // Display time in seconds
//   // LED_on();
//   // delay(500); // Wait for half a second

//   // LED_off();
//   // delay(500); // Wait for half a second

//   // Or alternatively, use the toggle function:
//   // LED_toggle();
//   // delay(500);

//   // if (was_button_just_pressed()) {
//   //   // Serial.println("Button clicked!");
//   //   LED_toggle(); // Toggle the LED state
//   // }
//   // Read the value and map it to a range of 0 to 100
//   // int sensor_value = read_potentiometer_mapped(0, 100);
//   // // Print the value to the serial monitor
//   // Serial.print("Mapped Value: ");
//   // Serial.println(sensor_value);

//   //  // Print the value to the LCD (assuming you have the overloaded print functions)
//   // lcd_set_cursor(0, 1);
//   // lcd_print("Val: ");
//   // lcd_print_number((long)sensor_value); // Cast to long for the lcd_print(long) overload
//   // lcd_print("   "); // Clear remaining characters if the number shrinks

//   // delay(100); // Small delay before the next read

//   // // Read the water level mapped from 0% to 100%
//   // int level_percent = read_water_percent(); 

//   // // Print the value to the serial monitor
//   // Serial.print("Water Level: ");
//   // Serial.print(level_percent);
//   // Serial.println("%");

//   // // Print the value to the LCD (assuming you have the overloaded print functions)
//   // lcd_set_cursor(0, 1);
//   // lcd_print_number((long)level_percent); // Cast to long for the lcd_print(long) overload
//   // lcd_print("%"); 
//   // lcd_print("   "); // Clear remaining characters

//   // delay(500); // Wait half a second before the next reading

//   // // Read the raw sensor value
//   // int raw_value = read_water_raw(); 

//   // // Print the raw value to the Serial Monitor
//   // Serial.print("Raw Sensor Value: ");
//   // Serial.println(raw_value);

//   // // Optional: Also read and print the percentage (uses your calibrated min/max)
//   // int level_percent = read_water_percent();
//   // Serial.print("Mapped Percentage: ");
//   // Serial.print(level_percent);
//   // Serial.println("%");

//   // // Keep this delay so the Serial Monitor doesn't get flooded too quickly
//   // delay(300); 

//    // Use the driver function to check for a new card
//   if (rfid_is_card_present()) {
//     // If a card is present, read its UID
//     String cardUID = rfid_read_card_uid();

//     Serial.print("Card detected: ");
//     Serial.println(cardUID);

//     // Display UID on LCD
//     lcd_set_cursor(0, 1);
//     lcd_print(cardUID.c_str());
//   }
// }


// // put function definitions here:
// int myFunction(int x, int y) {
//   return x + y;
// }

#include <Arduino.h>
#include "pico/stdlib.h"
#include "hardware/gpio.h"
#include "LCD_Driver.h"
#include "Potentiometer_Driver.h" 
#include "LED_Driver.h"
#include "Push_Button_Driver.h"
#include "Water_Sensor_Driver.h"
#include "RFID_READER_DRIVER.h" 
#include "Water_Pump_Driver.h"

#define ONBOARD_LED_PIN 6 

void setup() {
    Serial.begin(115200);
    printf("Using standard setup/loop format with SDK functions.\n");

    gpio_init(ONBOARD_LED_PIN); 
    gpio_set_dir(ONBOARD_LED_PIN, GPIO_OUT); 

    Serial.println("Initializing LCD, Potentiometer");
    potentiometer_init();
    lcd_init();



    lcd_print("Hello :D");
    // lcd_print("Pot Raw: ");
    // lcd_set_cursor(0, 1);
    // lcd_print("Mapped: ");

    LED_init();

    button_init();

    water_sensor_init();

    // lcd_print("Water Raw:");
    // lcd_set_cursor(0, 1);
    // lcd_print("Level: ");

    rfid_init();
    // lcd_print("Scan RFID Tag");

    water_pump_init();

    

}


void loop() {
    // gpio_put(ONBOARD_LED_PIN, 1); // SDK function
    // sleep_ms(500);               // SDK function
    // gpio_put(ONBOARD_LED_PIN, 0); // SDK function
    // sleep_ms(500);               // SDK function

    // // Read the raw 0-4095 value using the SDK driver function
    // int raw_value = read_potentiometer_value();

    // // Read the value mapped to 0-100 percentage
    // int mapped_value = read_potentiometer_mapped(0, 100);

    // // Print raw value to Serial Monitor
    // Serial.print("Raw: ");
    // Serial.print(raw_value);
    // Serial.print("\tMapped: ");
    // Serial.println(mapped_value);

    // // Print raw value to LCD (Top Row)
    // lcd_set_cursor(9, 0);
    // lcd_print_number(raw_value);
    // lcd_print("    "); // Clear previous characters

    // // Print mapped value to LCD (Bottom Row)
    // lcd_set_cursor(8, 1);
    // lcd_print_number(mapped_value);
    // lcd_print("% "); // Add percentage symbol and clear space
    // lcd_print("    ");

    // // Flash the LED briefly to show activity
    // gpio_put(ONBOARD_LED_PIN, 1);
    // sleep_ms(10);
    // gpio_put(ONBOARD_LED_PIN, 0);

    // // Add a small delay so the LCD/Serial isn't updated too rapidly
    // sleep_ms(100);

    // LED_on();
    // delay(500); // Wait for half a second

    // LED_off();
    // delay(500); // Wait for half a second

//   // Or alternatively, use the toggle function:
//   LED_toggle();
//   delay(500);

// if (was_button_just_pressed()) {
//         printf("Button pressed! Toggling external LED.\n");
//         LED_toggle(); // Use the SDK LED driver toggle function
//     }
// // Blink the onboard LED rapidly to show the loop is running smoothly
//     digitalWrite(ONBOARD_LED_PIN, HIGH);
//     sleep_ms(50);
//     digitalWrite(ONBOARD_LED_PIN, LOW);
//     sleep_ms(50);

// // Read the raw value using the SDK driver function
//     int raw_value = read_water_raw();

//     // Read the value mapped to 0-100 percentage using the nonlinear SDK driver
//     int mapped_level = read_water_percent();

//     // Print values to Serial Monitor
//     Serial.print("Raw: ");
//     Serial.print(raw_value);
//     Serial.print("\tLevel: ");
//     Serial.print(mapped_level);
//     Serial.println("%");

//     // Print raw value to LCD (Top Row)
//     lcd_set_cursor(11, 0);
//     lcd_print_number(raw_value);
//     lcd_print("    "); // Clear previous characters

//     // Print mapped value to LCD (Bottom Row)
//     lcd_set_cursor(7, 1);
//     lcd_print_number(mapped_level);
//     lcd_print("% "); // Add percentage symbol and clear space
//     lcd_print("    ");

//     // Flash the LED briefly to show activity
//     digitalWrite(ONBOARD_LED_PIN, HIGH);
//     sleep_ms(10);
//     digitalWrite(ONBOARD_LED_PIN, LOW);

//     // Add a small delay so the LCD/Serial isn't updated too rapidly
//     sleep_ms(300);

// Check for a card using the SDK-based driver function
    if (rfid_is_card_present()) {
        // If a card is present, read its UID
        String cardUID = rfid_read_card_uid();

        Serial.print("Card detected: ");
        Serial.println(cardUID);

        // Display UID on LCD
        lcd_set_cursor(0, 1);
        // Use lcd_print as defined in your driver
        lcd_print(cardUID.c_str()); 

        // Flash onboard LED rapidly to indicate a successful read
        for(int i = 0; i < 5; i++) {
            digitalWrite(ONBOARD_LED_PIN, HIGH);
            sleep_ms(50);
            digitalWrite(ONBOARD_LED_PIN, LOW);
            sleep_ms(50);
        }
    }
    
//     // Small delay to keep the loop smooth when no card is present
//     sleep_ms(100);

// printf("Running pump Forward at 50%% speed...\n");
//     // Run forward (true) at 50% speed
//     water_pump_set_direction(true);
//     water_pump_set_speed(50);

//     // Keep it running for 5 seconds
//     sleep_ms(5000); 

//     printf("Stopping pump.\n");
//     // Turn the pump off
//     water_pump_off();

//     // Wait for 2 seconds
//     sleep_ms(2000);

//     printf("Running pump Reverse at 80%% speed...\n");
//     // Run in reverse (false) at 80% speed
//     water_pump_set_direction(false);
//     water_pump_set_speed(80);

//     // Keep it running for 5 seconds
//     sleep_ms(5000);

//     printf("Stopping pump. Repeating sequence in 2 seconds.\n");
//     water_pump_off();

//     // Wait for 2 seconds before the loop repeats
//     sleep_ms(2000);
}

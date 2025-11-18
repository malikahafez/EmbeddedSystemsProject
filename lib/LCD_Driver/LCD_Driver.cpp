#include "LCD_Driver.h"
#include <stdio.h> 
#include <stdlib.h> 
#include "pico/stdlib.h"
#include "hardware/i2c.h"
#include <Arduino.h> // Needed for String class if using Solution 2 for floats

// Global variable to keep track of the current I/O expander state
uint8_t i2c_lcd_backlight_state = 0x00; 

// --- Driver Core Functions ---

// Send a byte to the I2C bus using Pico SDK
void i2c_send_byte(uint8_t data) {
  i2c_write_blocking(i2c0, LCD_ADDRESS, &data, 1, false);
}

// Send a 4-bit nibble (data is passed as the high 4 bits)
void send_nibble(uint8_t nibble, uint8_t mode) {
    uint8_t output = nibble & 0xF0; 

    output |= mode; 
    output |= i2c_lcd_backlight_state; 

    // Pulse the Enable pin (High -> Low) to latch the data
    i2c_send_byte(output | (1 << EN_PIN));   // Enable High
    sleep_us(1); // Use SDK sleep function
    i2c_send_byte(output & ~(1 << EN_PIN));  // Enable Low
    sleep_us(100); // Use SDK sleep function
}

// Send a command to the LCD controller
void send_command(uint8_t command) {
    // Send high nibble, with RS pin LOW (command mode)
    send_nibble(command & 0xF0, 0); 
    // Send low nibble, with RS pin LOW (command mode)
    send_nibble((command << 4) & 0xF0, 0); 
}

// Send data (a character) to the LCD controller
void send_data(uint8_t data) {
    // Send high nibble, with RS pin HIGH (data mode)
    send_nibble(data & 0xF0, (1 << RS_PIN));
    // Send low nibble, with RS pin HIGH (data mode)
    send_nibble((data << 4) & 0xF0, (1 << RS_PIN));
}

// Initialize the LCD using Pico SDK
void lcd_init() {
  i2c_init(i2c0, 100000); 

  // Set the specific GPIO pins for I2C on the Nano RP2040 Connect
  // A4 = GP12, A5 = GP13 
  gpio_set_function(12, GPIO_FUNC_I2C); // SDA pin (A4)
  gpio_set_function(13, GPIO_FUNC_I2C); // SCL pin (A5)
  gpio_pull_up(12);
  gpio_pull_up(13);

  sleep_ms(50); 
  i2c_lcd_backlight_state = (1 << BL_PIN); 

  send_nibble(0x30, 0);
  sleep_us(5000);
  send_nibble(0x30, 0);
  sleep_us(1000);
  send_nibble(0x30, 0);
  sleep_us(1000);
  send_nibble(0x20, 0); 
  sleep_us(1000);

  send_command(LCD_FUNCTIONSET | LCD_4BITMODE | LCD_2LINE | LCD_5x8DOTS);
  send_command(LCD_DISPLAYCONTROL | LCD_DISPLAYON | LCD_CURSOROFF | LCD_BLINKOFF);
  send_command(LCD_CLEARDISPLAY);
  sleep_ms(2); 
  send_command(LCD_ENTRYMODESET | LCD_ENTRYLEFT | LCD_ENTRYSHIFTDECREMENT);
  send_command(LCD_RETURNHOME);
  sleep_ms(2);
}


// --- Helper Functions to Print Different Data Types ---

void lcd_print(const char* str) {
  while (*str) {
    send_data(*str++); // This call should now link correctly
  }
}

void lcd_print_number(unsigned long number) {
    // We must use a fixed-size stack array, not a char pointer
    char buf[20]; 
    snprintf(buf, sizeof(buf), "%lu", number);
    lcd_print(buf);
}

void lcd_print_float(double number, unsigned int decimals) {
    // Use the Arduino String class for reliable float handling
    String floatString = String(number, decimals);
    char buf[20]; 
    floatString.toCharArray(buf, sizeof(buf));
    lcd_print(buf); 
}

void lcd_set_cursor(uint8_t col, uint8_t row) {
    uint8_t row_offsets[] = { 0x00, 0x40, 0x14, 0x54 };
    send_command(LCD_SETDDRAMADDR | (col + row_offsets[row]));
}

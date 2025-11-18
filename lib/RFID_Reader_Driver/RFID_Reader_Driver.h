#ifndef RFID_READER_DRIVER
#define RFID_READER_DRIVER


#include "pico/stdlib.h"     // Primary SDK Standard Library header
#include "hardware/spi.h"    // SDK SPI specific functions
#include "hardware/gpio.h"   // SDK GPIO functions
#include <MFRC522.h>         // Keep the MFRC522 library header

// #define RFID_SDA_PIN 10//d10/gpio5
// #define RFID_SCK_PIN 13//d13/gpio6
// #define RFID_COPI_PIN 11//d11/gpio7/COPI
// #define RFID_CIPO_PIN 12//d12/gpio4/CIPO
// #define RFID_RST_PIN 9//d9/gpio21

// Use the GPIO numbers based on your wiring list
#define RFID_SS_GPIO_PIN      5  // D10 / GPIO 5
#define RFID_SCK_GPIO_PIN     6  // D13 / GPIO 6
#define RFID_COPI_GPIO_PIN    7  // D11 / GPIO 7 (MOSI)
#define RFID_CIPO_GPIO_PIN    4  // D12 / GPIO 4 (MISO)
#define RFID_RST_GPIO_PIN     21 // D9  / GPIO 21

// // The pins are defined by GPIO number
// #define RFID_SS_GPIO_PIN     10 // SDA/SS (Slave Select) Pin 
// #define RFID_RST_GPIO_PIN    9  // RST Pin 

// Function declarations
void rfid_init();
bool rfid_is_card_present();
String rfid_read_card_uid();



#endif
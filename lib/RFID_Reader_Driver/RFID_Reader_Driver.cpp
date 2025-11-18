#include "RFID_READER_DRIVER.h"
#include <Arduino.h> // Keep Arduino include for String class and general setup

// Create an instance of the MFRC522 class, it uses the Arduino SPI library internally
MFRC522 mfrc522(RFID_SS_GPIO_PIN, RFID_RST_GPIO_PIN); 

void rfid_init() {
    // --- Use Pico SDK functions for SPI peripheral configuration ---

    // Initialize SPI0 hardware at 10MHz (GPIO 4, 5, 6, 7 use SPI0 instance)
    spi_init(spi0, 10000 * 1000); 

    // Set the specific GPIO pins for SPI0
    gpio_set_function(RFID_CIPO_GPIO_PIN, GPIO_FUNC_SPI); // MISO (CIPO)
    gpio_set_function(RFID_COPI_GPIO_PIN, GPIO_FUNC_SPI); // MOSI (COPI)
    gpio_set_function(RFID_SCK_GPIO_PIN,  GPIO_FUNC_SPI); // SCK

    // Ensure SS and RST pins are configured as standard GPIO outputs for manual control
    gpio_init(RFID_SS_GPIO_PIN);
    gpio_set_dir(RFID_SS_GPIO_PIN, GPIO_OUT);
    gpio_put(RFID_SS_GPIO_PIN, 1); // Set SS high (inactive) initially

    gpio_init(RFID_RST_GPIO_PIN);
    gpio_set_dir(RFID_RST_GPIO_PIN, GPIO_OUT);
    gpio_put(RFID_RST_GPIO_PIN, 1); // Set RST high (inactive) initially
    
    // --- Use MFRC522 library functions for protocol handling ---
    mfrc522.PCD_Init();  
    printf("RFID Reader initialized via SDK SPI setup.\n");
}


bool rfid_is_card_present() {
    if (mfrc522.PICC_IsNewCardPresent() && mfrc522.PICC_ReadCardSerial()) {
        return true;
    }
    return false;
}

String rfid_read_card_uid() {
    String content = "";
    for (byte i = 0; i < mfrc522.uid.size; i++) {
        // ... (Formatting logic remains the same) ...
        content.concat(String(mfrc522.uid.uidByte[i] < 0x10 ? " 0" : " "));
        content.concat(String(mfrc522.uid.uidByte[i], HEX));
    }
    content.toUpperCase();
    
    mfrc522.PICC_HaltA(); 
    mfrc522.PCD_StopCrypto1();

    return content.substring(1); 
}
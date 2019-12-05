/*
 * This file was largely adapted from an example from the RFID library at: https://github.com/miguelbalboa/rfid
 * This sketch is used with Arduino IDE and holds the main program logic.
 */

#include <SPI.h>
#include <MFRC522.h>

#include "user.h"
#include "keysender.h"

#define SS_PIN 10
#define RST_PIN 9
#define NUM_USERS 2 // The number of different users

MFRC522 rfid(SS_PIN, RST_PIN); // Instance of the class

MFRC522::MIFARE_Key key; 

// Init array that will store new NUID 
byte nuidPICC[4];

byte buf[8] = {0, 0, 0, 0, 0, 0, 0, 0};

User users[NUM_USERS] = {
    User{{32, 04, 120, 166}, "kpandey", "***********"}, // Password not shown for github repo
    User{{0xCE, 0x3C, 0x4C, 0x79}, "torti", "pass"}
};

void setup() {
  Serial.begin(9600);
  
  SPI.begin(); // Init SPI bus
  rfid.PCD_Init(); // Init MFRC522 

  for (byte i = 0; i < 6; i++) {
    key.keyByte[i] = 0xFF;
  }

  // initialize digital pin LED_BUILTIN as an output.
  pinMode(LED_BUILTIN, OUTPUT);
  delay(200);
}
 
void loop() {

  // Reset the loop if no new card present on the sensor/reader. This saves the entire process when idle.
  if ( ! rfid.PICC_IsNewCardPresent())
    return;

  // Verify if the NUID has been readed
  if ( ! rfid.PICC_ReadCardSerial())
    return;

  MFRC522::PICC_Type piccType = rfid.PICC_GetType(rfid.uid.sak);

  // Check is the PICC of Classic MIFARE type
  if (piccType != MFRC522::PICC_TYPE_MIFARE_MINI &&  
    piccType != MFRC522::PICC_TYPE_MIFARE_1K &&
    piccType != MFRC522::PICC_TYPE_MIFARE_4K) {
    // Serial.println(F("Your tag is not of type MIFARE Classic."));
    return;
  }

  if (rfid.uid.uidByte[0] != nuidPICC[0] || 
    rfid.uid.uidByte[1] != nuidPICC[1] || 
    rfid.uid.uidByte[2] != nuidPICC[2] || 
    rfid.uid.uidByte[3] != nuidPICC[3] ) {

    // Store NUID into nuidPICC array
    for (byte i = 0; i < 4; i++) {
      nuidPICC[i] = rfid.uid.uidByte[i];
    }

    User *matching_user = find_user_by_id(users, NUM_USERS, nuidPICC);
    if (matching_user != nullptr) {
      sendKeys(buf, matching_user->username);
      const char* tab = "\t";
      sendKeys(buf, tab);
      sendKeys(buf, matching_user->password);
      const char* enter = "\n";
      sendKeys(buf, enter);
    } else {
      // Serial.println(F("This card does not match a known user."));
    }
  }

  // Halt PICC
  rfid.PICC_HaltA();

  // Stop encryption on PCD
  rfid.PCD_StopCrypto1();
}


/**
 * Helper routine to dump a byte array as hex values to Serial. 
 */
void printHex(byte *buffer, byte bufferSize) {
  for (byte i = 0; i < bufferSize; i++) {
    Serial.print(buffer[i] < 0x10 ? " 0" : " ");
    Serial.print(buffer[i], HEX);
  }
}

/**
 * Helper routine to dump a byte array as dec values to Serial.
 */
void printDec(byte *buffer, byte bufferSize) {
  for (byte i = 0; i < bufferSize; i++) {
    Serial.print(buffer[i] < 0x10 ? " 0" : " ");
    Serial.print(buffer[i], DEC);
  }
}

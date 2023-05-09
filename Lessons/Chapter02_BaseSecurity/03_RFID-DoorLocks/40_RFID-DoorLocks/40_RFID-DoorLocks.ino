/*
 * Day 0 - AI Apocalypse by inventr.io
 * Learn more at https://inventr.io/PLACEHOLDER
 *
 * The door locks work, but again they were controlled by the building AI that’s been
 * disabled.  We can lock the doors when we’re here, but it takes too long to have
 * someone come open the door, and what do we if we all have to go out at the same
 * time?  Let’s work on a way to unlock the doors from the outside using the keypads
 * next to each door.
 *
 * Our 4x4 keypad leaves us somewhat vulnerable while standing there trying to press
 * a bunch of small buttons in the right order.  It looks like our doors also have RFID
 * readers on them, and our parts box has an RFID reader in it so we can wire one up
 * here and write the code for our HERO XL so we can quickly unlock the doors.
 *
 * Alex Eschenauer
 * David Schmidt
 */

/*
CODE FROM https://www.youtube.com/watch?v=Kyz1w_T-MGo
Interconnections from the RFID to the Arduino pins:
Reset     > Pin 5
SS        > Pin 10
MOSI      > Pin 11
MISO      > Pin 12
SCK       > Pin 13
Ground    > Ground
3.3v      > 3.3v


Interconnections from the LCD (I2C) to the Arduino pins:
GND > GND of the Arduino
VCC > +5V of the Arduino
SDA > A4 pin of the Arduino
SCL > A5 pin of the Arduino
*/


#include <SPI.h>
#include <MFRC522.h>
// #include "pitches.h"
#include <LiquidCrystal.h>
// #include <Wire.h>

const uint8_t RST_PIN = 26;  // Configurable, see typical pin layout above
const uint8_t SS_PIN = 53;   // Configurable, see typical pin layout above

MFRC522_SPI spiDevice = MFRC522_SPI(SS_PIN, RST_PIN);
MFRC522 rfid = MFRC522(SS_PIN, RST_PIN);  // Create MFRC522 instance

const byte APPROVED[][10] = {
  { 217, 205, 16, 20 }  // Recognized key fob
};

LiquidCrystal lcd(22, 24, 23, 25, 27, 29);

void setup() {
  Serial.begin(9600);
  SPI.begin();
  rfid.PCD_Init();

  lcd.begin(16, 2);
  lcd.clear();
  lcd.setCursor(0, 0);
  lcd.print("  Tap to Enter  ");
}

void loop() {
  // Look for new cards
  if (rfid.PICC_IsNewCardPresent()) {

    // Select one of the cards
    if (rfid.PICC_ReadCardSerial()) {

      if (rfid.uid.size == 0) {
        Serial.println("Bad card (size = 0)");
      } else {
        char tag[sizeof(rfid.uid.uidByte) * 4] = { 0 };
        Serial.print("UID size: ");
        Serial.println(rfid.uid.size);
        for (int i = 0; i < rfid.uid.size; i++) {
          char buff[5];  // 3 digits, dash and \0.
          snprintf(buff, sizeof(buff), "%s%d", i ? "-" : "", rfid.uid.uidByte[i]);
          strncat(tag, buff, sizeof(tag));
        };
        Serial.println("Good scan: ");
        Serial.println(tag);

        Serial.println("Comparing: ");
        for (int i = 0; i < (sizeof(APPROVED) / sizeof(APPROVED[0])); i++) {
          lcd.setCursor(0, 1);
          if (strncmp(rfid.uid.uidByte, APPROVED[i], rfid.uid.size) == 0) {
            Serial.println("Matched");
            lcd.print("  Come on in!   ");
          } else {
            lcd.print("    No Match    ");
          }
          delay(2000);
          lcd.setCursor(0, 1);
          lcd.print("                ");
        }
      };

      // disengage with the card.
      //
      rfid.PICC_HaltA();

    } else {
      Serial.println("Bad read (was card removed too quickly?)");
    }
  }
}
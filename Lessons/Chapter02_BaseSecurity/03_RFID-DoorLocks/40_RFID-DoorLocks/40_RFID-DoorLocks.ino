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

// Install MFRC522-spi-i2c-uart-async from Library Manager
#include <MFRC522.h>
#include <LiquidCrystal.h>

const uint8_t RST_PIN = 26;  // Configurable, see typical pin layout above
const uint8_t SS_PIN = 53;   // Configurable, see typical pin layout above

MFRC522_SPI spiDevice = MFRC522_SPI(SS_PIN, RST_PIN);
MFRC522 rfid = MFRC522(SS_PIN, RST_PIN);  // Create MFRC522 instance

/*
 * This is a two dimentional array that will contain the RFID codes that will
 * open our doors.  RFID codes can contain 4, 7 or 10 bytes so we allocate a 10
 * byte array for EACH code.  The empty braces [] indicate that the number of
 * approved codes (and space for them) is set by how many codes are defined.
 *
 * If we define 2 codes this will allocate 2 arrays of 10 bytes, or 20 bytes.
 * Each code consists of up to 10 bytes, each of which may be defined by a *decimal*
 * number from 0-255.
 *
 * We start with NO defined codes.  We will then run the sketch and display the
 * codes of key cards or fobs that we pass by the sensor.  We can then add approved
 * codes that are allowed to open our doors.
 */
const byte APPROVED[][10] = {
  // {},         // Add additional codes with commas (',') between each sequence
  {34, 29, 168, 30}  // Recognized key fob
};

// Pins for our 16x2 LCD display
LiquidCrystal lcd(22, 24, 23, 25, 27, 29);

void setup() {
  Serial.begin(9600);

  rfid.PCD_Init();  // Initialize RFID reader

  // Initialize LCD display with our door prompt
  lcd.begin(16, 2);
  lcd.clear();
  lcd.setCursor(0, 0);  // Go to beginning of first line
  lcd.print("  Tap to Enter  ");
}

void loop() {
  // When a new RFID "card" is detected
  if (rfid.PICC_IsNewCardPresent()) {

    // Read the RFID code on the card.
    if (rfid.PICC_ReadCardSerial()) {

      // If we were able to read a valid RFID (size > 0)
      if (rfid.uid.size > 0) {
        // Allocate enough space for us to display each byte in the code
        // as a decimal number separated by ", " (like "255, 255, 255, 255")
        char tag[sizeof(rfid.uid.uidByte) * 5] = { 0 };
        Serial.print("UID size: ");
        Serial.println(rfid.uid.size);
        for (int i = 0; i < rfid.uid.size; i++) {
          char buff[6];  // 3 digits, ',', space and \0.
          snprintf(buff, sizeof(buff), "%s%d", i ? ", " : "", rfid.uid.uidByte[i]);
          strncat(tag, buff, sizeof(tag));
        };
        Serial.println("Good scan: ");
        Serial.println(tag);

        Serial.print("Comparing: ");
        bool match_found = false;   // No matches found yet
        // Check each of our approved codes.  Here we use a trick to determine how
        // many codes we have.  We simply divide the total size of our APPROVED array
        // and divide by the size of a single code.
        for (int i = 0; i < (sizeof(APPROVED) / sizeof(APPROVED[0])); i++) {
          Serial.print("  Code: ");
          Serial.println(i);
          int j;
          for (j = 0; j < rfid.uid.size; j++) {
            Serial.print("  byte: ");
            Serial.print(j);
            char buff[10]; // space for 2 decimal bytes (0-255), a dash and terminating null
            snprintf(buff, sizeof(buff), ": %d-%d", rfid.uid.uidByte[j], APPROVED[i][j]);
            Serial.print(buff);
            // Do byte comparison here.
            if (rfid.uid.uidByte[j] != APPROVED[i][j]) {
              Serial.println("  MISMATCH!");
              break;    // break out of loop early
            } else {
              Serial.println();
            }
          }
          // If we find a mis-match we break out of our inner loop early, and
          // j will be less than the size of the code we read.
          if (j == rfid.uid.size) {
            match_found = true;
            break;    // exit outer loop since we found a match
          }
        }
        
        // Now we display on the LCD whether a match was found or not
        lcd.setCursor(0, 1);
        if (match_found) {
          Serial.println("Matched");
          lcd.print("  Come on in!   ");
          // UNLOCK THE DOOR HERE!
        } else {
          Serial.println("NO Match");
          lcd.print("    NO MATCH    ");
        }
        delay(2000);
        lcd.setCursor(0, 1);
        lcd.print("                ");
      } else {
        Serial.println("Bad card (size = 0)");
      }

      // disengage with the card.
      rfid.PICC_HaltA();

    } else {
      Serial.println("Bad read (was card removed too quickly?)");
    }
  }
}
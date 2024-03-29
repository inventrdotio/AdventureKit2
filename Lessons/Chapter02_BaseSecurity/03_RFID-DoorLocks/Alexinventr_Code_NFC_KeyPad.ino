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
 * The 4x4 Matrix Array Membrane Switch Keypad used in the sketches is a simple and
 * cost-effective input device for Arduino projects. It consists of a 4x4 grid of BUTTONS,
 * providing a total of 16 keys. Each key is labeled with a number, letter, or symbol,
 * such as 0-9, A-D, *, and #.
 *
 * Let's make the feedback even better by adding an LCD1602 LCD character display.  That
 * will allow us to give better instructions and feedback as the user enters the secret
 * code.
 *
 * LCD stands for "Liquid Crystal Display." You might have seen these types of screens on
 * calculators, microwaves, or digital clocks. The "1602" part means that this display has
 * 16 columns and 2 rows, so you can show a total of 32 characters at once.
 *
 * The LCD1602 is like a tiny TV screen that shows letters, numbers, and symbols. It has a
 * special controller that helps us communicate with it using our Arduino board. We can
 * send messages to the screen and tell it what to display.
 *
 * Alex Eschenauer
 * David Schmidt
 */

#include <Wire.h>
#include <LiquidCrystal.h>
#include <MFRC522.h>
#include <SPI.h>

#define RST_PIN         9          // Configurable, see typical pin layout above
#define SS_PIN          10         // Configurable, see typical pin layout above

#define PASSWORD        "1234"
#define CARD_KEY        "supersecurepassword"

LiquidCrystal_I2C lcd(0x27, 16, 2);
MFRC522 mfrc522(SS_PIN, RST_PIN);   // Create MFRC522 instance.

const int ROWS = 4;
const int COLS = 4;
char keys[ROWS][COLS] = {
  {'1','2','3','A'},
  {'4','5','6','B'},
  {'7','8','9','C'},
  {'*','0','#','D'}
};

byte rowPins[ROWS] = {35, 37, 39, 41};
byte colPins[COLS] = {43, 45, 47, 49};

int greenLedPin = 4;
int redLedPin = 5;

bool isLocked = true;

void setup() {
  lcd.begin();
  lcd.backlight();
  SPI.begin();
  mfrc522.PCD_Init();
  pinMode(greenLedPin, OUTPUT);
  pinMode(redLedPin, OUTPUT);
  digitalWrite(redLedPin, HIGH);
  Serial.begin(9600);
  while (!Serial) {
    ; // wait for serial port to connect. Needed for native USB port only
  }
}

void loop() {
  if (isLocked) 
  {
    Read_KeyPad();
    Read_NFC();
  }
}

void Read_KeyPad() {
  lcd.clear();
  lcd.print("Enter passcode:");
  char enteredCode[5];
  int codeIndex = 0;
  while (codeIndex < 4) {
    char key = getKey();
    if (key != '\0') {
      lcd.print('*');
      enteredCode[codeIndex++] = key;
    }
  }
  enteredCode[4] = '\0';
  if (strcmp(enteredCode, PASSWORD) == 0) {
    unlock();
    lcd.clear();
    lcd.print("Access granted");
    delay(1000);
  } else {
    lcd.clear();
    lcd.print("Incorrect code");
    delay(1000);
  }
}

void Read_NFC() {
  lcd.clear();
  lcd.print("Tap card to NFC");
  while (true) {
    if (mfrc522.PICC_IsNewCardPresent() && mfrc522.PICC_ReadCardSerial()) {
      String cardData = "";
      for (int i = 0; i < mfrc522.uid.size; i++) {
        cardData += String(mfrc522.uid.uidByte[i] < 0x10 ? "0" : "");
        cardData += String(mfrc522.uid.uidByte[i], HEX);
      }
      if (cardData == CARD_KEY) {
        unlock();
        lcd.clear();
        lcd.print("Access granted");
        delay(1000);
      } else {
        lcd.clear();
        lcd.print("Access denied");
        delay(1000);
        lock();
      }
      mfrc522.PICC_HaltA();
      mfrc522.PCD_StopCrypto1();
      break;
    }
  }
}

char getKey() {
  for (int col = 0; col < COLS; col++) {
    pinMode(colPins[col], OUTPUT);
    digitalWrite(colPins[col], LOW);
    for (int row = 0; row < ROWS; row++) {
      if (digitalRead(rowPins[row]) == LOW) {
        delay(50);
        while (digitalRead(rowPins[row]) == LOW);
        {pinMode(colPins[col], INPUT_PULLUP);
         digitalWrite(colPins[col], HIGH);
    return keys[row][col];
  }
}
pinMode(colPins[col], INPUT_PULLUP);
digitalWrite(colPins[col], HIGH);
}
return '\0';
} }

void unlock() {
lcd.clear();
lcd.print("Access granted");
digitalWrite(greenLedPin, HIGH);
digitalWrite(redLedPin, LOW);
isLocked = false;
delay(1000);
}

void lock() {
lcd.clear();
lcd.print("System locked");
digitalWrite(greenLedPin, LOW);
digitalWrite(redLedPin, HIGH);
isLocked = true;
}
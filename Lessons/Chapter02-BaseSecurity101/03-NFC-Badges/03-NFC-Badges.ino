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
#include <RFID.h>
#include "pitches.h"
#include <LiquidCrystal_I2C.h>
#include <Wire.h>


RFID rfid(10,5);

byte datarfid[5] = {0x9D,0x49,0x26,0x75,0x87};

LiquidCrystal_I2C lcd(0x27,16,2);

byte serNum[5];
byte data[5];


int access_melody[] = {NOTE_G4,0,NOTE_A4,0, NOTE_B4,0,NOTE_A4,0,NOTE_B4,0, NOTE_C5,0};
int access_noteDurations[] = {8,8,8,8,8,4,8,8,8,8,8,4};
int fail_melody[] = {NOTE_G2,0,NOTE_F2,0,NOTE_D2,0};
int fail_noteDurations[] = {8,8,8,8,8,4};

int relay = 6;
int LED_access = 2;
int LED_intruder = 3;
int speaker_pin = 8;
const int buttonPin = 7;  
int buttonState = 1;  

void setup(){
 
  Serial.begin(9600); 
  lcd.init(); 
  lcd.backlight();
  lcd.clear();
  pinMode(buttonPin, INPUT);  
  SPI.begin(); 
  rfid.init(); 
 
  delay(1000);
  pinMode(LED_access,OUTPUT);
  pinMode(LED_intruder,OUTPUT);
  pinMode(speaker_pin,OUTPUT);
  pinMode(relay,OUTPUT);

}
 
void loop(){
 
  lcd.backlight();
  { 
  lcd.setCursor(0,0);
  lcd.print("TEMPELKAN KARTU");
  lcd.setCursor(0,1);
  lcd.print("   RFID ANDA");
  }
  
   buttonState = digitalRead(buttonPin);
  
   if (buttonState == LOW){
   digitalWrite(relay,HIGH);
   digitalWrite(LED_access,HIGH);
   lcd.setCursor(0,0);
   lcd.print("  Manual Aktif  ");
   lcd.setCursor(0,1);
   lcd.print("  Pintu Terbuka");
   delay(7000);
   digitalWrite(relay,LOW);
   digitalWrite(LED_access,LOW);
   lcd.clear();
  }
  
  
  boolean datarfid_card = true; 
  
  if (rfid.isCard()){ 
    if (rfid.readCardSerial()){ 
      delay(1000);
      data[0] = rfid.serNum[0]; 
      data[1] = rfid.serNum[1];
      data[2] = rfid.serNum[2];
      data[3] = rfid.serNum[3];
      data[4] = rfid.serNum[4];
    }
  
  
  lcd.backlight();
 

  lcd.setCursor(0,0);
  lcd.print("ID = ");
  
  if(data[0] < 16){
    lcd.print("0");
  }
  lcd.print(data[0],HEX);
  
  if(data[1] < 16){
    lcd.print("0");
  }
  lcd.print(data[1],HEX);
  
  if(data[2] < 16){
    lcd.print("0");
  }
  lcd.print(data[2],HEX);
  
  if(data[3] < 16){
    lcd.print("0");
  }
  lcd.print(data[3],HEX);
  
  if(data[4] < 16){
    lcd.print("0");
  }
  lcd.print(data[4],HEX);
  for(int i=0; i<5; i++){
    if(data[i] != datarfid[i]) datarfid_card = false; 
  lcd.setCursor(0,1);
  lcd.print("                    "); 
  }
  Serial.println();
     
  if (datarfid_card){ 

    
    for (int i = 0; i < 12; i++){ 
      int access_noteDuration = 1000/access_noteDurations[i];
      tone(speaker_pin, access_melody[i],access_noteDuration);
      int access_pauseBetweenNotes = access_noteDuration * 1.30;
      delay(access_pauseBetweenNotes);
      noTone(speaker_pin);
    }
  }
 
  else{ 
    lcd.setCursor(0,1);
    lcd.print(" Akses Ditolak");
   
 
    digitalWrite(LED_intruder, HIGH); 
    for (int i = 0; i < 6; i++){ 
      int fail_noteDuration = 1000/fail_noteDurations[i];
      tone(speaker_pin, fail_melody[i],fail_noteDuration);
      int fail_pauseBetweenNotes = fail_noteDuration * 1.30;
      delay(fail_pauseBetweenNotes);
      noTone(speaker_pin);
    }
    delay(1000);
    digitalWrite(LED_intruder, LOW); 
    lcd.clear();
  }
  if (datarfid_card){
    lcd.setCursor(0,1);
    lcd.print(" Akses Diterima");
    digitalWrite(LED_access,HIGH);
    delay(1000);
    lcd.setCursor(0,0);
    lcd.print("  Pintu Terbuka  ");
    lcd.setCursor(0,1);
    lcd.print(" Silahkan Masuk  ");
    digitalWrite(relay,HIGH); 
    delay(7000);
    digitalWrite(relay,LOW);
    digitalWrite(LED_access,LOW);
    lcd.clear();
  }
  
  
  Serial.println();
  delay(10);
  rfid.halt();
  lcd.backlight();
  }
}
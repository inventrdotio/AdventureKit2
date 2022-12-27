// ---------------------------------------------------------------- //
// LCD1602 - LCD 16x2
// ---------------------------------------------------------------- //
#include <LiquidCrystal.h>
// LiquidCrystal lcd(6, 7, 8, 9, 10, 11); // RS, EN, D4, D5, D6, D7
LiquidCrystal lcd(12, 11, 2, 3, 4, 5); // RS, EN, D4, D5, D6, D7

void setup() {
  Serial.begin(115200); // // Serial Communication is starting with 9600 of baudrate speed
  Serial.println("LCD1602 LCD test"); // print some text in Serial Monitor
  Serial.println("with Arduino UNO R3");
  lcd.begin(16, 2); // lcd starts with resolution 16x2
}
void loop() {
  lcd.setCursor(0, 0);
  lcd.print("0123456789ABCDEF");
  lcd.setCursor(0, 1);
  lcd.print("0123456789ABCDEF");
  delay(2000);
  for (int row = 0; row < 2; row++) {
    for (int col = 0; col < 16; col++) {
      lcd.setCursor(col, row);
      lcd.print("0");
      delay(100);
      lcd.clear();
    }
  }
}
/*
  1 Digit 7 Segment LED Display (5161AS)
*/

constexpr int a = 2;  //For displaying segment "a"
constexpr int b = 3;  //For displaying segment "b"
constexpr int c = 4;  //For displaying segment "c"
constexpr int d = 5;  //For displaying segment "d"
constexpr int e = 6;  //For displaying segment "e"
constexpr int f = 7;  //For displaying segment "f"
constexpr int g = 8;  //For displaying segment "g"

/*
  A
F   B
  G
E   C
  D

Lit segments for each digit
  0 1 2 3 4 5 6 7 8 9
A x   x x   x x x x x
B x x x x x     x x x
C x x   x x x x x x x
D x   x x   x x   x x
E x   x       x   x
F x       x x x   x x
G     x x x x x   x x

*/

void setup() {
  pinMode(a, OUTPUT);  //A
  pinMode(b, OUTPUT);  //B
  pinMode(c, OUTPUT);  //C
  pinMode(d, OUTPUT);  //D
  pinMode(e, OUTPUT);  //E
  pinMode(f, OUTPUT);  //F
  pinMode(g, OUTPUT);  //G
}

// Since there are more unlit than lit segments it's more efficient to light
// a segment when certain digits *aren't* matched
void displayDigit(int digit) {
  // Conditions for displaying segment a
  if (digit != 1 && digit != 4)
    digitalWrite(a, HIGH);

  // Conditions for displaying segment b
  if (digit != 5 && digit != 6)
    digitalWrite(b, HIGH);

  // Conditions for displaying segment c
  if (digit != 2)
    digitalWrite(c, HIGH);

  // Conditions for displaying segment d
  if (digit != 1 && digit != 4 && digit != 7)
    digitalWrite(d, HIGH);

  // Conditions for displaying segment e
  if (digit == 2 || digit == 6 || digit == 8 || digit == 0)
    digitalWrite(e, HIGH);

  // Conditions for displaying segment f
  if (digit != 1 && digit != 2 && digit != 3 && digit != 7)
    digitalWrite(f, HIGH);
  if (digit != 0 && digit != 1 && digit != 7)
    digitalWrite(g, HIGH);
}
void turnOff() {
  digitalWrite(a, LOW);
  digitalWrite(b, LOW);
  digitalWrite(c, LOW);
  digitalWrite(d, LOW);
  digitalWrite(e, LOW);
  digitalWrite(f, LOW);
  digitalWrite(g, LOW);
}


void loop() {
  /*
  turnOff();
  displayDigit(0);
  delay(1000);

  turnOff();
  digitalWrite(a,HIGH);
  delay(1000);

  turnOff();
  digitalWrite(b,HIGH);
  delay(1000);

  turnOff();
  digitalWrite(c,HIGH);
  delay(1000);

  turnOff();
  digitalWrite(d,HIGH);
  delay(1000);

  turnOff();
  digitalWrite(e,HIGH);
  delay(1000);

  turnOff();
  digitalWrite(f,HIGH);
  delay(1000);

  turnOff();
  digitalWrite(g,HIGH);
  delay(1000);
*/

  for (int i = 0; i < 10; i++) {
    displayDigit(i);
    delay(1000);
    turnOff();
  }
}
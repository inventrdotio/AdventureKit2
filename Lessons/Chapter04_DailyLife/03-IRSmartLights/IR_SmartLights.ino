#include <IRremote.h>

#define PIN_RECEIVER 5   // Signal Pin of IR receiver
#define Rpin 2
#define Gpin 3
#define Bpin 4

IRrecv receiver(PIN_RECEIVER);

int status=0;

void setup()
{
  Serial.begin(9600);
  receiver.enableIRIn(); // Start the receiver
  pinMode(Rpin, OUTPUT);
  pinMode(Gpin, OUTPUT);
  pinMode(Bpin, OUTPUT);
  }

void loop()
{
  // Checks received an IR signal
  if (receiver.decode()) {
    translateIR();
    receiver.resume();  // Receive the next value
  }
}

void translateIR()
{
  // Takes command based on IR code received
  int x=receiver.decodedIRData.command;
  Serial.println(x);
  if (x==162)
  {
    if (status==0)
    {
      status=1;
      digitalWrite(Rpin,HIGH);
      digitalWrite(Gpin,HIGH);
      digitalWrite(Bpin,HIGH);
      delay(500);
      digitalWrite(Rpin,LOW);
      digitalWrite(Gpin,LOW);
      digitalWrite(Bpin,LOW);
      delay(500);
      digitalWrite(Rpin,HIGH);
      digitalWrite(Gpin,HIGH);
      digitalWrite(Bpin,HIGH);
      delay(500);
      digitalWrite(Rpin,LOW);
      digitalWrite(Gpin,LOW);
      digitalWrite(Bpin,LOW);

    }
    else if (status==1)
    {
      status=0;
      digitalWrite(Rpin,LOW);
      digitalWrite(Gpin,LOW);
      digitalWrite(Bpin,LOW);
    }
  }
  if (status==1)
  {
    switch (x)
    {
      case 48:
      digitalWrite(Rpin,HIGH);
      break;
      case 24:
      digitalWrite(Gpin,HIGH);
      break;
      case 122:
      digitalWrite(Bpin,HIGH);
      break;
      case 16:
      digitalWrite(Rpin,LOW);
      break;
      case 56:
      digitalWrite(Gpin,LOW);
      break;
      case 90:
      digitalWrite(Bpin,LOW);
      break;
      default:
      int y=0;
    }
  }
  }

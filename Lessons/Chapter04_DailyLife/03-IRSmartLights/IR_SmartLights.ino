#include <IRremote.h>

#define PIN_RECEIVER 5   // Signal Pin of IR receiver
#define Rpin 2
#define Gpin 3
#define Bpin 4

#define PowerButton 162
#define RedOnButton 48
#define RedOffButton 16
#define BlueOnButton 122
#define BlueOffButton 90
#define GreenOnButton 24
#define GreenOffButton 56

IRrecv receiver(PIN_RECEIVER);

int powerOnStatus=0;

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
  int ButtonInput=receiver.decodedIRData.command;
  Serial.println(ButtonInput); // prints the decoded button press - use this to figure out what works for your remote!
  
  if (ButtonInput==PowerButton) // power button was pressed
  {
    if (powerOnStatus==0) // currently off, launch boot up sequence
    {
      powerOnStatus=1;
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
    else if (powerOnStatus==1) // shut down sequence
    {
      powerOnStatus=0;
      digitalWrite(Rpin,LOW);
      digitalWrite(Gpin,LOW);
      digitalWrite(Bpin,LOW);
    }
  }
  if (powerOnStatus==1) // currently on
  {
    switch (ButtonInput)
    {
      case RedOnButton:
      digitalWrite(Rpin,HIGH);
      break;
      case GreenOnButton:
      digitalWrite(Gpin,HIGH);
      break;
      case BlueOnButton:
      digitalWrite(Bpin,HIGH);
      break;
      case RedOffButton:
      digitalWrite(Rpin,LOW);
      break;
      case GreenOffButton:
      digitalWrite(Gpin,LOW);
      break;
      case BlueOffButton:
      digitalWrite(Bpin,LOW);
      break;
      default: //some other button was pressed, ignore
    }
  }
  }

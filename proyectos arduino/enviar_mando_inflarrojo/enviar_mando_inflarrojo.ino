#include <IRremote.h>
const int buttonPin = 7; 
const int xPin = A0;         // joystick Y  principal
const int yPin = A1;         // joystick Y secunadario
int buttonState;
int sensor1;
int sensor2;  
IRsend irsend;
void setup()
{
  
   pinMode(buttonPin, INPUT_PULLUP); 
  Serial.begin(9600); //solo para verificar que se esta enviando la señal
}
void loop()
{
  buttonState = digitalRead(buttonPin);
    if (buttonState == 0) 
    { Serial.print("por squi") ;
     irsend.sendPanasonic(0x8E700FF, 28); 
    for (int i = 0; i < 3; i++) {
      
       delay(100);
    }
  }
   
 
   sensor1= analogRead(xPin);
   sensor2= analogRead(yPin);
   /*if (sensor1 < 50 )
       irsend.sendNEC(0x8E7A857, 6);
  else if (sensor1 > 950 )
   irsend.sendNEC(0x8E7B04F, 6);
   
  if (sensor2 < 50 )
    irsend.sendNEC(0x8E76897, 6);
  else if (sensor2 > 950 )
   irsend.sendNEC(0x8E7708F, 6);*/
}

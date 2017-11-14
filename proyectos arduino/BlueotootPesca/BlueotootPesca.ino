int alarma=0;

int sonso1 = 0;
int sensor2 = 0;

void setup() {
  // put your setup code here, to run once:

}

void loop() {
  // put your main code here, to run repeatedly:

  sonso1 = (analogRead(joystickPanPin) - 512) / 50;
  sensor2 = (analogRead(joystickTiltPin) - 512) / -50;
  //= constrain((servoPanPosition + joystickPanSpeed), 1, 180);
 
  if (seonsor1== 180 || sensor== 180)
      alarma=1;
      
    if (Serial.available() > 0)
  {
   
    int i = Serial.readString();
    if i(i = '0')
      alarma=0;

Serial.println(alarma);
  }

}

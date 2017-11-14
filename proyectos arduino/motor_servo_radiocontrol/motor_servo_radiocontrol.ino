#include <Servo.h>   // incluimos la biblioteca Servo 
Servo miservo;       // creamos un objecto servo para controlar el motor 

int servo1;  // numero para inviar a miservo
int IN3 = 7;    // Input3 conectada al pin 5
int IN4 = 4;    // Input4 conectada al pin 4 
int ENB = 5;    // ENB conectada al pin 3 de Arduino
int motor;
int velocidadMotor;
#define sensorpir 2


     void setup() { 
  miservo.attach(6);  // liga el servo al pin 6 
  pinMode(sensorpir,INPUT);
  
  pinMode (ENB, OUTPUT); 
  pinMode (IN3, OUTPUT);
  pinMode (IN4, OUTPUT);

   servo1=90;
   motor=5;
   velocidadMotor=0;
   Serial.begin(9600); //Se inicia la comunicación serie
   
   }

     void loop() { 


    
           //si la conexion serie es correcta 
  if (Serial.available() > 0) {
    //caracteres
    int input= Serial.read();



 
    if(input=='1')
    {
       servo1=servo1 + 5;
      }
       
    else if (input=='2')
  {
    servo1=servo1 - 5;
  } 
  
     
    miservo.write(servo1);
       
     

    if(input=='3')
    {
      motor=motor+1;
     }

      if(input=='4')
    {
       motor=motor-1;
     }

       if(input=='5')
    {
      motor=5;
     }

     
      if (motor==5)
     {
      velocidadMotor=0;
      }

      else  if (motor==4 || motor==6)
     {

       if (motor==4)
       {
        digitalWrite (IN3, HIGH);
        digitalWrite (IN4, LOW);
        }
        else
        { 
        digitalWrite (IN3, LOW);
         digitalWrite (IN4, HIGH);
         }
      velocidadMotor=51;
      
      }
     else if (motor==0 || motor==10)
     {
      velocidadMotor=255;
      }

     else  if (motor==1 || motor==9)
     {
      velocidadMotor=204;
      }

     else  if (motor==2 || motor==8)
     {
      velocidadMotor=153;
      }

     else  if (motor==3 || motor==7)
     {
      velocidadMotor=102;
      }

     analogWrite(ENB,velocidadMotor);
    
     }
   
     if (digitalRead(sensorpir) == HIGH)
    { 
          Serial.println("alarma");
           delay(6000);
    }
  }

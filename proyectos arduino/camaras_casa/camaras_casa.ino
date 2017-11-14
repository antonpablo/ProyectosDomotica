#include <Servo.h>   // incluimos la biblioteca Servo 
#define LUZ  12     // se definen los pines donde se conectaran los reles                
#define VENTILADOR  13
Servo servodir;
int direcion;
     void setup() { 
    servodir.attach(5);
    direcion=8;
    pinMode(LUZ, OUTPUT);      
    pinMode(VENTILADOR, OUTPUT);
    Serial.begin(9600); //Se inicia la comunicación serie
   
   }

     void loop() { 


    
           //si la conexion serie es correcta 
  if (Serial.available() > 0) 
  {
    //caracteres
        int input= Serial.read();
        int dir;
        if (input=='0' || input=='1' || input=='2' || input=='3' || input=='4')
        {
            if (input=='0')
           direcion=0;
        else if (input=='1')
           direcion=8;         
        else if (input=='2')
                direcion=18;
        else if(input=='3'|| input=='4')
         { 
            if (direcion>0 && direcion<18)
            { 
                if (input=='3')
                direcion=direcion-1;
                else if (input=='4')
                direcion=direcion+1;
             }
             else if (direcion==18 && input=='3')
                direcion=direcion-1;
             else if (direcion==0 && input=='4')
                direcion=direcion+1;
         }
         dir=map(direcion, 0, 16, 0, 180);
         servodir.write(dir);
        }
        else if (input=='5'|| input=='6')
        {
           if (input=='5')
             digitalWrite(LUZ,LOW); //encender
           else if (input=='6')
             digitalWrite(LUZ,HIGH);//apagar
         }
        else if (input=='7'|| input=='8')
      {
           if (input=='7')
             digitalWrite(VENTILADOR,LOW); //encender
           else if (input=='8')
             digitalWrite(VENTILADOR,HIGH);//apagar
        }
  }
   
  }

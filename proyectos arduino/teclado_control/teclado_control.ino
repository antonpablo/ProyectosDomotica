

#include <Servo.h>   // incluimos la biblioteca Servo 
Servo servovel;
Servo servodir;
Servo servocam1;
Servo servocam2;
int velocidad;
int direcion;
int camara1;
int camara2;
     void setup() { 
    servovel.attach(5);  // liga el servo al pin 6 
    servodir.attach(6);
    servocam1.attach(10);
    servocam2.attach(11);
 
    velocidad=6;
    direcion=4;
    camara1=5;
    camara2=5;
    
    Serial.begin(9600); //Se inicia la comunicación serie
   
   }

     void loop() { 


    
           //si la conexion serie es correcta 
  if (Serial.available() > 0) 
  {
    //caracteres
        int input= Serial.read();
        int vel;
        if(input=='0'|| input=='1' || input=='2')
         { 
            if (input=='0')
                velocidad=6;
            else if (velocidad>0 && velocidad<12)
            { 
                if (input=='1')
                velocidad=velocidad-1;
                else if (input=='2')
                velocidad=velocidad+1;
             }
             else if (velocidad==12 && input=='1')
                velocidad=velocidad-1;
             else if (velocidad==0 && input=='2')
                velocidad=velocidad+1;
              vel=map(velocidad, 0, 12, 0, 180);
              servovel.write(vel);
           
         }
           if(input=='3'|| input=='4')
         {  
              if ( direcion>0 &&  direcion<8)
              {
                 if (input=='3')
                    direcion=direcion-1;
                 else if (input=='4')
                    direcion=direcion+1;
                }
                else if ( direcion==0 &&  input=='4')
                  direcion=direcion+1;
                   else if ( direcion==8 &&  input=='3')
                  direcion=direcion-1;

                 vel=map(direcion, 0, 8, 0, 180);
                servodir.write(vel);
          }

            if(input=='5'|| input=='6')
         {  
              if ( camara1>0 &&  camara1<10)
              {
                 if (input=='5')
                    camara1=camara1-1;
                 else if (input=='6')
                    camara1=camara1+1;
               }
             else if (camara1==0 && input=='6')
                camara1=camara1+1;
             else if (camara1==10 && input=='5')
                camara1=camara1-1;
                
             vel=map(camara1, 0, 10, 0, 180);
             servocam1.write(vel);
          }

              if(input=='7'|| input=='8')
         {  
              if ( camara2>0 &&  camara2<10)
              {
                 if (input=='7')
                    camara2=camara2-1;
                 else if (input=='8')
                    camara2=camara2+1;
                }
               else if (camara2==0 && input=='8')
                  camara2=camara2+1;
               else if (camara2==10 && input=='7')
                  camara2=camara2-1;
                  
               vel=map(camara2, 0, 10, 0, 180);
               servocam2.write(vel);
          }
            
    }
   
  }

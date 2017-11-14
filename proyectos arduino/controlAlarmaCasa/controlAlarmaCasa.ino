#include <Servo.h>   // incluimos la biblioteca Servo 
Servo servodir;
#include <DHT.h>
#define LUZ  12     // se definen los pines donde se conectaran los reles                
#define VENTILADOR  13
#define PIR  2
int temperatura;
int humedad;
int maxtem=0;
int mintem=100;
int maxhum=0;
int  minhum=100;
int num=0;
DHT dht(3,11);//pin 12 dht 11
boolean alarma=false;

void setup() {
  // put your setup code here, to run once:
  Serial.begin(9600);
  pinMode(PIR,INPUT);
   servodir.attach(5);
}


void loop() {


 
    Serial.println("#alarma");
    delay(50);
   


  if (Serial.available() > 0) 
   {
    //caracteres
        int input= Serial.read();
        int res=5;
          if (input == '5')
             {
              F_Imprimir();
              } 
         else  if (input == '6')
             {Serial.println("todo ok");
                 servodir.write(180);
              } 
         else  if (input == '7')
             {Serial.println("todo en off");
              servodir.write(0);
              } 
        else  if (input == '8')
             {Serial.println("todo en on");
              servodir.write(90);
              } 
    //activar y desacticar la alarma

      else  if (input == '9')
               {
                if (alarma==true)
                    alarma==false;
               else if (alarma==false)
                    alarma==true;
              } 
        
   }
    temperatura=dht.readTemperature();
     humedad=dht.readHumidity();
      maxmin();
  
 
}

void F_Imprimir()
{
   Serial.print(temperatura);
   Serial.print("-");
   Serial.print(humedad);
   Serial.print("-");
   Serial.print(maxtem);
   Serial.print("-");
   Serial.print(mintem);
   Serial.print("-");
   Serial.print(maxhum);
   Serial.print("-");
   Serial.print(minhum);
   Serial.println();
 }

 void maxmin()
 {
  if (maxtem<temperatura)
      maxtem=temperatura;
  else if (mintem>temperatura && temperatura>0)
      mintem=temperatura;
  if (maxhum<humedad)
      maxhum=humedad;
  else if (minhum>humedad && humedad>0) 
      minhum=humedad;
  }

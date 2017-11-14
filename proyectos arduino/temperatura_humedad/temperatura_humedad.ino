#include <DHT.h>

#define LUZ  12     // se definen los pines donde se conectaran los reles                
#define VENTILADOR  13
int temperatura;
int humedad;
int maxtem=0;
int mintem=100;
int maxhum=0;
int  minhum=100;

DHT dht(3,11);//pin 12 dht 11

void setup() {
  // put your setup code here, to run once:
  Serial.begin(9600);

}


void loop() {
  // put your main code here, to run repeatedly:
           //si la conexion serie es correcta 
  if (Serial.available() > 0) 
  {
    //caracteres
        int input= Serial.read();
        if (input=='5' )
           F_Imprimir();
        
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
  else if (mintem>temperatura)
      mintem=temperatura;
  if (maxhum<humedad)
      maxhum=humedad;
  else if (minhum>humedad) 
      minhum=humedad;
  }

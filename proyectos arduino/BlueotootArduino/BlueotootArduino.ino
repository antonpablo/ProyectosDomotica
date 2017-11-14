#include "DHT.h"
#include <Servo.h>   // incluimos la biblioteca Servo 
#define DHTPIN 3
#define DHTTYPE DHT11
#define RELAYluz 6
#define RELAYcal  7
#define RELAYven  5 
#define RELAYluz2 4
DHT dht(DHTPIN, DHTTYPE);
Servo servoAire;
int temperatura=0;
int humedad=0;
int maxtem=0;
int mintem=100;
int maxhum=0;
int  minhum=100;
float voltageValue[6] = {0,0,0,0,0,0};
String res;
char charBuf[4]={'0','0','0','0'};

void setup() {
  Serial.begin(9600);
    pinMode(RELAYven, OUTPUT);
   pinMode(RELAYcal, OUTPUT);  
   pinMode(RELAYluz, OUTPUT);
  pinMode(RELAYluz2, OUTPUT);
  servoAire.attach(10);
  dht.begin();
  digitalWrite(RELAYcal,HIGH);
  digitalWrite(RELAYluz,HIGH);
  digitalWrite(RELAYven,HIGH);
  digitalWrite(RELAYluz2,HIGH);

}

void loop() {
  

 if (Serial.available() > 0)
  {
    res = Serial.readString();
    res.toCharArray(charBuf, 3) ;
    Serial.println(res);
    if (charBuf[0] == 'a')
    {
       if (charBuf[1] == '1')
        servoAire.write(90); //cerradura off
      else if (charBuf[1] == '0')
        servoAire.write(180);  
    }
  
    else if  (charBuf[0] == 'v')
    {
      if (charBuf[1] == '1')
        digitalWrite(RELAYven,LOW);
     else  if (charBuf[1] == '0')   
        digitalWrite(RELAYven,HIGH);
       
    }
     else if  (charBuf[0] == 'o')
    {
       if (charBuf[1] == '1')
        digitalWrite(RELAYluz,LOW);
     else  if (charBuf[1] == '0')   
        digitalWrite(RELAYluz,HIGH);
    }
     else if  (charBuf[0] == 'k')
    {
       if (charBuf[1] == '1')
        digitalWrite(RELAYluz2,LOW);
     else  if (charBuf[1] == '0')   
        digitalWrite(RELAYluz2,HIGH);
    }
     else if  (charBuf[0] == 'c')
    {
       if (charBuf[1] == '1')
        digitalWrite(RELAYcal,LOW);
     else  if (charBuf[1] == '0')   
        digitalWrite(RELAYcal,HIGH);
    }         
  }

     
  temperatura=dht.readTemperature();
  humedad=dht.readHumidity();
  maxMinTempeHum();

  voltageValue[0]=temperatura;
  voltageValue[1]=humedad;
  voltageValue[2]=maxtem; 
  voltageValue[3]=mintem;
  voltageValue[4]=maxhum;
  voltageValue[5]= minhum;
  sendAndroidValues();
  delay(2000);
}

//enviar los valores por el dipositivo android por el modulo Bluetooth
void sendAndroidValues()
 {
  for(int k=0; k<6; k++)
  {
    Serial.print(voltageValue[k]);
    Serial.print('-'); //separamos los datos con el +, así no es más fácil debuggear la información que enviamos
  }
 Serial.println();
 delay(20);        //agregamos este delay para eliminar tramisiones faltantes
}
void maxMinTempeHum()
{
 if (maxtem<temperatura)
      maxtem=temperatura;
  else if (mintem>temperatura && temperatura !=0)
      mintem=temperatura;
  if (maxhum<humedad)
      maxhum=humedad;
  else if (minhum>humedad && humedad !=0) 
      minhum=humedad;
 }

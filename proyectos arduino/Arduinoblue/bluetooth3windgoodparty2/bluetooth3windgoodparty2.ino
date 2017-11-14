#include "DHT.h"
#include <Servo.h>   // incluimos la biblioteca Servo 
#define DHTPIN 3
#define DHTTYPE DHT11
#define RELAYluz 6
#define RELAYcal  7
#define RELAYven  5 
DHT dht(DHTPIN, DHTTYPE);
int sensorpir= 12;//pin de entrada 
Servo servoCerradura;
Servo servoRadar;
long distancia;
long tiempo;
int temperatura=0;
int humedad=0;
int maxtem=0;
int mintem=100;
int maxhum=0;
int  minhum=100;
float voltageValue[6] = {0,0,0,0,0,0};
int puerta=0;
int alarma=0;
int modoAlarma=0;
String res;
char charBuf[3]={'0','0','0'};

void setup() {
  // initialise serial communications at 9600 bps:
  Serial.begin(9600);
  pinMode(8, INPUT); /*activación del pin 8 como entrada: tiempo del rebote del ultrasonido*/
  pinMode(9, OUTPUT); /*activación del pin 9 como salida: para el pulso ultrasónico*/
  servoCerradura.attach(10);
  servoRadar.attach(11);
  pinMode(sensorpir,INPUT);
  dht.begin();
  digitalWrite(RELAYcal,HIGH);
  digitalWrite(RELAYluz,HIGH);

}
 
void loop() {

  
  if (alarma=='1')//desactivar la alarma para que no salte
    sensorAlarma();  
  
  temperatura=dht.readTemperature();
  humedad=dht.readHumidity();
  maxMinTempeHum();
  if (Serial.available() > 0)
  {
   
    res = Serial.readString();
    res.toCharArray(charBuf, 3) ;
    Serial.println(res);
    if (charBuf[0] == 'p')
    {
       if (charBuf[1] == '0')
       {
        servoCerradura.write(0); //cerradura off
        puerta=0;
        }
        else if (charBuf[1] == '1')
        {
          servoCerradura.write(180);  //cerradura on
          puerta= 1;
         }
    }
  }   
     if (modoAlarma==1)
       Serial.println("alarma");
     else 
       {
                
          voltageValue[0]=temperatura;
          voltageValue[1]=humedad;
          voltageValue[2]=maxtem; 
          voltageValue[3]=mintem;
          voltageValue[4]=maxhum;
          voltageValue[5]= minhum;
        
          sendAndroidValues();
        }    
  delay(2000);
}

void sensorAlarma()
{
  if (digitalRead(sensorpir)== HIGH)
  {
    ///hacer una busqueda con el sonar y si es positivo mandar 1
    int hh=0;
    int distanciaMin=500;//5 metros
    while (hh<200)
    {
      
      digitalWrite(9,LOW); 
      delayMicroseconds(5);
      digitalWrite(9, HIGH); 
      delayMicroseconds(10);
      tiempo=pulseIn(8, HIGH); 
      distancia= int(0.017*tiempo); 

      if (distancia < distanciaMin)
          distanciaMin=distancia;
      hh++;
      delay(10);
      }
      //si la distancia es menor que 3 metros que salte la alarma
      if(distanciaMin <= 300)
        modoAlarma=1; 
        }
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
  else if (mintem>temperatura)
      mintem=temperatura;
  if (maxhum<humedad)
      maxhum=humedad;
  else if (minhum>humedad) 
      minhum=humedad;
 }

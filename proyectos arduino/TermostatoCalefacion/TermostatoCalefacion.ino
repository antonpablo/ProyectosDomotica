#include <DHT.h>
#include <Servo.h>   // incluimos la biblioteca Servo 
Servo leftRightServo;    // Crea una variable servo
DHT dht1(5,11);//pin 5 dht 11
DHT dht2(10,22);//pin 10 dht 22
#define RELAYluz 6
#define RELAYcal  7
#define sensorPir 13 //sensor pir movimient
#define servoPin 12 //servo
#define echoPin 8    // SRF05's Echo pin
#define trigPin 9    // SRF05's Trig pin
float temperatura[2]={0,0};
float humedad[2]={0,0};
float maxtem[2]={0,0};
float mintem[2]={100,100};
float maxhum[2]={0,0};
float minhum[2]={100,100};
float voltageValue[6] = {0,0,0,0,0,0};
int i=0;
int leftRightPos = 0;    // Variable para la posición del servo (grados)
int index = 0;    // Contador para el número de lectura

long total = 0;    // Variable para calcular el pormedio
int average = 0;    // Variable para calcular el promedio
long duration = 0;    // Variable para calcular el tiempo de llegada de la señal
int distance = 0; // Variable para calcular la distancia
int servoMin = 700;    // Anchura del pulso, en microsegundos, correspondiente al mínimo (0 grados) ángulo en del servo (por defecto 544)
int servoMax = 2400;    // Anchura del pulso, en microsegundos, correspondiente al máximo (180 grados) ángulo en del servo (por defecto 2400)
const int numReadings = 2;    // Número de lecturas en cada posición
boolean alarm = false;
boolean calef = true;
String res;
char charBuf [3] ={'0','0','0'};
int cont=0;

void setup() {
  Serial.begin(9600);
  pinMode(RELAYcal, OUTPUT);
  pinMode(RELAYluz, OUTPUT); 
  digitalWrite(RELAYcal,HIGH);
  digitalWrite(RELAYluz,HIGH);
  pinMode(sensorPir,INPUT);
  leftRightServo.attach(servoPin,700,2400);    // Pin de salida para el servo, recorrido minimo, recorrido maximo
  pinMode(trigPin, OUTPUT);    // Establece pin como salida
  pinMode(echoPin, INPUT);    // Establece pin como entrada
  digitalWrite(trigPin, LOW);    // Pone el pin a un estado logico bajo
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
        alarm = true;
      else if (charBuf[1] == '0')
        alarm = false;  
    }
    if (charBuf[0] == 'c')
    {
       if (charBuf[1] == '1')
        calef = true;
      else if (charBuf[1] == '0')
        calef = false;  
    }
  }
 
  i=0; 
  temperatura[i]=dht2.readTemperature();
  humedad[i]=dht2.readHumidity();
  maxMinTempeHum(temperatura[i],humedad[i],i);
 if (calef == true)
 {
   if (temperatura[i] < 18)
      digitalWrite(RELAYcal,LOW);
  else if (temperatura[i] > 18)
      digitalWrite(RELAYcal,HIGH);
 }
 else 
   digitalWrite(RELAYcal,HIGH);
  
  i=1;
  temperatura[i]=dht1.readTemperature();
  humedad[i]=dht1.readHumidity();
  maxMinTempeHum(temperatura[i],humedad[i],i);

//  hacer que cada vez se envie uno diferent
   if (cont % 2 == 0)     
      i=0;
   else 
      i=1;
      
  voltageValue[0]=temperatura[i];
  voltageValue[1]=humedad[i];
  voltageValue[2]=maxtem[i]; 
  voltageValue[3]=mintem[i];
  voltageValue[4]=maxhum[i];
  voltageValue[5]= minhum[i];    
  sendAndroidValues(i);
  
  cont++;
   if (cont == 20)
    cont=0;   
  
  delay(2000);
  
  if (digitalRead(sensorPir)== HIGH && alarm == true)
    alarma();
  
}
void alarma()
{
   for(leftRightPos = 0; leftRightPos < 180; leftRightPos++) {    // De izquierda a derecha.
    leftRightServo.write(leftRightPos);
        for (index = 0; index<numReadings; index++) {    // Repite tantas veces como número de lecturas en cada posicion           
        // Pulso de 10us para inicial el modulo
        digitalWrite(trigPin, HIGH); 
        delayMicroseconds(10); 
        digitalWrite(trigPin, LOW);
    
        duration = pulseIn(echoPin, HIGH, 17400);    // Devuelve la longitud del pulso del pin Echo en us (3metros maximo)
            if (!duration){    // Si la duracción es 0
            duration = 17400;    // La señal se a perdido. Se establece distancia maxima
            }
        distance = duration/58;    // Calculamos distancia en centrimetros
        total = total + distance;    // Almacenamos la distancia para calcular promedio
        delay(50);    // Esperamos hasta la siguiente medida
        }
    
    average = total/numReadings;    // Calcula el promedio
    total = 0;    // Resetea variable
  
    // Envia datos por el puerto serie
    Serial.print("X");    // Identificador X para la posicion del servo
    Serial.print(leftRightPos);    // Posición del servo
    Serial.print("V");    // Identificador V para el promedio de distancia
    Serial.println(average);    // Promedio de distancia
    }
    for(leftRightPos = 180; leftRightPos > 0; leftRightPos--) {    // De derechas a izquierda
    leftRightServo.write(leftRightPos);
        for (index = 0; index<numReadings; index++) {           
        // Pulso de 10us para inicial el modulo
        digitalWrite(trigPin, HIGH); 
        delayMicroseconds(10); 
        digitalWrite(trigPin, LOW);
    
        duration = pulseIn(echoPin, HIGH, 17400); 
            if (!duration){
            duration = 17400;
            }
        distance = duration/58;                               
        total = total + distance;                              
        delay(50);  
        }
    
    average = total/numReadings;                               
    total = 0;
  
    Serial.print("X");                                         
    Serial.print(leftRightPos);                                
    Serial.print("V");                                         
    Serial.println(average);      
    }
      leftRightServo.write(90);
 }
void sendAndroidValues(int i)
 {
   Serial.print(i+1);
   Serial.print('-'); 
  for(int k=0; k<6; k++)
  {
    Serial.print(voltageValue[k]);
    Serial.print('-'); //separamos los datos con el +, así no es más fácil debuggear la información que enviamos
  }
 Serial.println();
 delay(20);        //agregamos este delay para eliminar tramisiones faltantes
}
void maxMinTempeHum(float temperatura,float humedad,int i)
{
 if (maxtem[i]<temperatura)
      maxtem[i]=temperatura;
  else if (mintem[i]>temperatura)
      mintem[i]=temperatura;
  if (maxhum[i]<humedad)
      maxhum[i]=humedad;
  else if (minhum[i]>humedad) 
      minhum[i]=humedad;
 }

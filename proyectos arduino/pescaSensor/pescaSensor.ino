#include <DHT.h>
DHT dht(3,11);//pin 12 dht 11
#include <Wire.h>
#include <LiquidCrystal_I2C.h>
LiquidCrystal_I2C lcd(0x3F, 16, 2);
#include "RTClib.h"
RTC_DS1307 RTC;
#include <OneWire.h> 
#include <DallasTemperature.h>
#define Pin 4 //Se declara el pin donde se conectará la DATA
OneWire ourWire(Pin); //Se establece el pin declarado como bus para la comunicación OneWire
DallasTemperature sensors(&ourWire); //Se instancia la librería DallasTemperature


const int buttonPin = 2;      // switch to turn on and off mouse control
const int y1Pin = A0;         // joystick Y  principal
const int x1Pin = A1;
const int y2Pin = A2;// joystick Y secunadario
const int alarma = 7;         // buffer de aviso y led
const int buzzer = 10;
int buttonState;
int sensor1;
int sensorMoverLcd;
int sensor2;
int temperatura;
int humedad;
int maxtem=0;
int mintem=100;
int maxhum=0;
int  minhum=100;
bool lcdOn=false;
int pagina=1;
void setup() {
  Wire.begin();
  lcd.begin (16,2);
  RTC.begin();
  //RTC.adjust(DateTime(__DATE__, __TIME__)); // Establece la fecha y hora (Comentar una vez establecida la hora)
  sensors.begin(); //Se inician los sensores 
  pinMode(buttonPin, INPUT_PULLUP); 
  pinMode(alarma, OUTPUT);
  pinMode(buzzer, OUTPUT);
  pinMode(y1Pin, INPUT);
  pinMode(x1Pin, INPUT);
  pinMode(y2Pin, INPUT);
   Serial.begin(9600);    
}

void loop() {

  temperatura=dht.readTemperature();
  humedad=dht.readHumidity();
  maxmin();

  buttonState = digitalRead(buttonPin);
    if (buttonState == 0) {
     Serial.println("apagar alarm!");
     digitalWrite(alarma, LOW);
     analogWrite(buzzer,0
     );
     //apagar pantalla
       lcd.clear();
       lcd.noBacklight();
       lcdOn=false;
       
    }

   sensor1= analogRead(y1Pin);
   sensorMoverLcd= analogRead(x1Pin);
   //sensor2= analogRead(y2Pin);
   
   if (sensor1 < 450 )// || sensor2 < 450
   {
     digitalWrite(alarma, HIGH);
     analogWrite(buzzer,150);
     lcd.backlight();
     lcdOn=true;
    }
    else if (sensor1 > 600 && lcdOn==false)
    {
      lcd.backlight();
      lcdOn=true;
     }
     
if (lcdOn==true)
{
  
  if (sensorMoverLcd < 100)
     pagina--;
   else if  (sensorMoverLcd > 900)
     pagina++; 
  if (pagina==0)
    pagina=4;
  else if (pagina==5)
    pagina=1;

  if (pagina==1)
    F_imprimir1();
  else if (pagina==2)
    F_imprimir2();
  else if (pagina==3)
    F_imprimir3();
  else if (pagina==4)
    F_imprimir4();
}
  delay(50);
}


void F_imprimir1()
{//temperatura agua reloj
   DateTime now = RTC.now(); // Obtiene la fecha y hora del RTC
    sensors.requestTemperatures(); //Prepara el sensor para la lectura
    lcd.clear();
    lcd.setCursor ( 0, 0 );  ;                   
    lcd.print("temp Agua  Hora");
    lcd.setCursor ( 0, 1 );      
    lcd.print(sensors.getTempCByIndex(0));
    lcd.print("   ");
    lcd.print(now.hour(), DEC);
    lcd.print(':');
    lcd.print(now.minute(), DEC);
    
    delay(1000);
    
 
 }
 void F_imprimir2()
 {  
    lcd.clear();
    lcd.setCursor ( 0, 0 );  ;                   
    lcd.print("temperatura: ");
    lcd.print(temperatura);
    lcd.print("C");
    lcd.setCursor ( 0, 1 );      
    lcd.print("humedad:     ");
    lcd.print(humedad);
    lcd.print("%");
    delay(1000);
      
  //temperatura y humedad
 }
 void F_imprimir3()
 {
    lcd.clear();
    lcd.setCursor ( 0, 0 );                     
    lcd.print("temp max:   ");
    lcd.print(maxtem);
    lcd.print("C");
    lcd.setCursor ( 0, 1 );      
    lcd.print("temp min:   ");
    lcd.print(mintem);
    lcd.print("C");
    delay(1000);
 }

  void F_imprimir4()
 {
    lcd.clear();
    lcd.setCursor ( 0, 0 );  ;                   
    lcd.print("hum max:   ");
    lcd.print(maxhum);
    lcd.print("%");
    lcd.setCursor ( 0, 1 );      
    lcd.print("hum min:   ");
    lcd.print(mintem);
    lcd.print("%");
    delay(1000);
 }
 

 void maxmin()
 {
  if (maxtem<temperatura)
      maxtem=temperatura;
  else if (mintem>temperatura && temperatura!=0)
      mintem=temperatura;
  if (maxhum<humedad)
      maxhum=humedad;
  else if (minhum>humedad && humedad!=0) 
      minhum=humedad;
  }

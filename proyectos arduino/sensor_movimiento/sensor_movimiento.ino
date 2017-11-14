int sensorpir= 2;//pin de entrada
byte led= 13; //pin de salida

void setup() {
  // put your setup code here, to run once:
  pinMode(sensorpir,INPUT);
  pinMode(led,OUTPUT); //modo salida
  Serial.begin(9600);

}

void loop() {
  // put your main code here, to run repeatedly:
  if (digitalRead(sensorpir)== HIGH)
  {
    Serial.println("Detectado movimiento");
    digitalWrite(led,HIGH);
   // delay(1000);
    digitalWrite(led,LOW);
   }

}

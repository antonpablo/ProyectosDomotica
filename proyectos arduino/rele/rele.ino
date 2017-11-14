#define RELAY1  7     // se definen los pines donde se conectaran los reles                
#define RELAY2  10                        
#define RELAY3  9                        
#define RELAY4  8
     
void setup(){    
// Se configuran los pines como salidas
  pinMode(RELAY1, OUTPUT);      
  pinMode(RELAY2, OUTPUT);
  pinMode(RELAY3, OUTPUT);
  pinMode(RELAY4, OUTPUT);
}

void loop(){  
   digitalWrite(RELAY1,LOW);           // Se enciende el relay 1
   delay(2000);                        // Se espera 2 segundos
   digitalWrite(RELAY1,HIGH);          // Se apaga el relay 1

   digitalWrite(RELAY2,LOW);           // Se enciende el relay 2
   delay(2000);                        // Se espera 2 segundos
   digitalWrite(RELAY2,HIGH);          // Se apaga el relay 2

   digitalWrite(RELAY3,LOW);           // Se enciende el relay 3
   delay(2000);                        // Se espera 2 segundos
   digitalWrite(RELAY3,HIGH);          // Se apaga el relay 3

   digitalWrite(RELAY4,LOW);           // Se enciende el relay 4
   delay(2000);                        // Se espera 2 segundos
   digitalWrite(RELAY4,HIGH);          // Se apaga el relay 4        
 }  

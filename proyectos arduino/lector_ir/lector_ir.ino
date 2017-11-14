#include <IRremote.h>
int RECV_PIN = 11; 

IRrecv irrecv(RECV_PIN);

decode_results results;

void setup()
{
  Serial.begin(9600);
  irrecv.enableIRIn(); // Empezamos la recepción  por IR
}


void dump(decode_results *results) {
  // Dumps out the decode_results structure.
  // Call this after IRrecv::decode()
  
  Serial.print("(");
  Serial.print(results->bits, DEC);
  Serial.print(" bits)");
  
  if (results->decode_type == UNKNOWN) {
    Serial.print("Unknown encoding: ");
  }
  else if (results->decode_type == NEC) {
    Serial.print("Decoded NEC: ");

  }
  else if (results->decode_type == SONY) {
    Serial.print("Decoded SONY: ");
  }
  else if (results->decode_type == RC5) {
    Serial.print("Decoded RC5: ");
  }
  else if (results->decode_type == RC6) {
    Serial.print("Decoded RC6: ");
  }
  else if (results->decode_type == PANASONIC) {
    Serial.print("Decoded PANASONIC - Address: ");
    Serial.print(results->address, HEX);
    Serial.print(" Value: ");
  }
  else if (results->decode_type == LG) {
    Serial.print("Decoded LG ");
  }
  else if (results->decode_type == JVC) {
    Serial.print("Decoded JVC ");
  }
  else if (results->decode_type == AIWA_RC_T501) {
    Serial.print("Decoded AIWA RC T501 ");
  }
  else if (results->decode_type == WHYNTER) {
    Serial.print("Decoded Whynter ");
  }
  Serial.print(results->value, HEX);
  Serial.print(" (HEX) , ");
  Serial.print(results->value, BIN);
  Serial.println(" (BIN)");

}

void loop() {
  if (irrecv.decode(&results)) {
    dump(&results);
    irrecv.resume(); // empezamos una nueva recepción
  }
  delay(300);
}


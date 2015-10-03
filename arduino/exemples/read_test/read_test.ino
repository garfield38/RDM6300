/*
  RFID RDM6300 data decoder library
 (c) Stephane Driussi 20150623
 Not for commercial use
 
 Refer to rdm6300_decoder_wiring.jpg diagram for proper connection
 
 */

#include <SoftwareSerial.h>
#include <RDM6300.h>
SoftwareSerial RFID(2, 3); // RX and TX

int Led=13;
uint8_t Payload[6]; // used for read comparisons

RDM6300 RDM6300(Payload);

void setup()
{
  pinMode(Led, OUTPUT);
  RFID.begin(9600);    // start serial to RFID reader
  Serial.begin(9600);  // start serial to PC 
}

void loop()
{
  while (RFID.available() > 0) 
  {
    digitalWrite(Led, HIGH);
    uint8_t c = RFID.read();
    //Serial.print(c,HEX);
    if (RDM6300.decode(c)) {
      for (int i=0; i < 5; i++){
        Serial.print(Payload[i], HEX);
        Serial.print(" ");
      } 
      Serial.println();
    }  
  }
  digitalWrite(Led, LOW);   
  delay(100);
}

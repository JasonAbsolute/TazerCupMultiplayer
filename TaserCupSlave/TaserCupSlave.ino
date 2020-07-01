
#include <EasyTransfer.h>

// the value of the 'other' resistor
#define SERIESRESISTOR 560    
 
// What pin to connect the sensor to
#define SENSORPIN A0 


struct SEND_DATA_STRUCTURE{
  boolean taze = false;
};
struct ACKNOWLEDGE{
  boolean recived = false;
};


SEND_DATA_STRUCTURE data;
ACKNOWLEDGE acknowledge;


EasyTransfer ETin, ETout;
 
void setup(void) {
  pinMode(7,OUTPUT);
  Serial.begin(9600);
  ETout.begin(details(data),&Serial);
  ETin.begin(details(acknowledge),&Serial);
}
 
void loop(void) {
  float reading;



  //If the cup is empty then send notice to relay to taze
  if(ETin.receiveData()){
    if(acknowledge.recived == true){
      if(data.taze == true){
        digitalWrite(7,HIGH);
        delay(1000);
        digitalWrite(7,LOW);
      }
    }
  } 
  Serial.print("Analog reading "); 
  Serial.println(reading);
  if(reading > 755){
    data.taze = true;
  }
  ETout.sendData();
 

  
  digitalWrite(7,HIGH);
  delay(200);
  digitalWrite(7,LOW);
  delay(5000);
 
  reading = analogRead(SENSORPIN);
 
  Serial.print("Analog reading "); 
  Serial.println(reading);
 
  delay(1000);
}

#include <EasyTransfer.h>

// the value of the 'other' resistor
#define SERIESRESISTOR 560    
 
// What pin to connect the sensor to
#define SENSORPIN A0 


struct SEND_DATA_STRUCTURE{
  boolean taze = false;
  boolean startGame = true;
};
struct ACKNOWLEDGE{
  boolean recived = false;
};

SEND_DATA_STRUCTURE data;
ACKNOWLEDGE acknowledge;

EasyTransfer ETin, ETout;
int led = 9;
int buttonPin = 11;

boolean gameRunning = false;

void setup(void) {
  pinMode(led, OUTPUT);
  pinMode(buttonPin, INPUT_PULLUP);
  pinMode(7,OUTPUT);
  pinMode(LED_BUILTIN, OUTPUT);
  Serial.begin(9600);
  ETout.begin(details(data),&Serial);
  ETin.begin(details(acknowledge),&Serial);
}
 
void loop(void) {
  float reading;
  int buttonValue = digitalRead(buttonPin);
  digitalWrite(led, HIGH);   
  digitalWrite(7,HIGH);
  //delay(1000);
  //digitalWrite(7,LOW);
  //delay(5000);
  //this will start the game
  if(buttonValue == LOW){
    gameRunning = true;
  }else{
    gameRunning = false;
  }
    while(gameRunning){
      if(ETin.receiveData()){
        if(data.taze){
          digitalWrite(7,HIGH);
          delay(2000);
          digitalWrite(7,LOW);
          gameRunning = false;
          
        }
      }
      reading = analogRead(SENSORPIN);
      //delay(1000);
      Serial.print("Analog reading "); 
      Serial.println(reading);
      if(reading > 1000){
         digitalWrite(LED_BUILTIN, HIGH); 
      delay(1000);     
      digitalWrite(LED_BUILTIN, LOW);
      delay(1000);
      }
    }
  }

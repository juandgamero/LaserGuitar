#include "pitches.h"
#include "strings.h"
const int speaker1Pin = 9;
const int strumPin1 = 2; //strum
const int fretPin1 = A5;// frett
const int fretPin2 = A3;

//const float highMin = 1.60;
//const int highMax = 2;
//const int lowMin = 1;
//const float lowMax = 1.3;
volatile byte state = HIGH;
//volatile byte state2 = LOW;



void setup() {
  // put your setup code here, to run once:
  Serial.begin(9600); //debugging purposes
  pinMode(speaker1Pin, OUTPUT);
  pinMode(strumPin1, INPUT_PULLUP); 
  pinMode(fretPin1, INPUT_PULLUP); 
  pinMode(fretPin2, INPUT_PULLUP);
  attachInterrupt(digitalPinToInterrupt(strumPin1), strum1, CHANGE); // interrupt on diode voltage change

  //attachInterrupt(digitalPinToInterrupt(strumPin1), strum1, CHANGE); // interrupt on diode voltage change
}
void loop() {
  // put your main code here, to run repeatedly:
  int value1 = digitalRead(strumPin1);
  Serial.println("Strum Pin1:");
  Serial.println(value1); //debugging purposes
  
  float value2 = analogRead(fretPin1);
  float volts2 = (value2/1023.0) * 5;
  Serial.println("Fret Pin1:");
  Serial.println(volts2); //debugging purposes
  
  float value3 = analogRead(fretPin2);
  float volts3 = (value3/1023.0) * 5;
  
  Serial.println("Fret Pin2:");
  Serial.println(volts3); //debugging purposes
  //delay(1000);
  
  if(state == 0){
      if(volts2 < 3 && volts3 > 3 ){
        //low voltage
        tone(speaker1Pin, NOTE_B0);
        while(state == 0){}
        //delay(700); // Play note for on second longer after laser is unblocked
        noTone(speaker1Pin);
      }
      else if(volts2 < 3 && volts3 < 3){
        tone(speaker1Pin, NOTE_G1);
        while(state == 0){}
        //delay(700); // Play note for on second longer after laser is unblocked
        noTone(speaker1Pin);
      }
      else if(volts2 > 3 && volts3 < 3){
        tone(speaker1Pin, NOTE_F2);
        while(state == 0){}
        //delay(700); // Play note for on second longer after laser is unblocked
        noTone(speaker1Pin);
      }      
      else{
        tone(speaker1Pin, NOTE_E1);
        while(state == 0){}
        //delay(1000); // Play note for on second longer after laser is unblocked
        noTone(speaker1Pin);
      }
  }
}
void strum1 () {
  state = !state;
}

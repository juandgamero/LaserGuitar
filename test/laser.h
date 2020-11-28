#ifndef LASER_H
#define LASER_H

// Import file with all the port numbers 
// only read digit pins 0 or 1
class Laser
{

 public:
  int strumPin; 
  int fretPin1;
  int fretPin2;
  int fretPin3;
  volatile byte state;

  Laser(int strum, int fret1, int fret2, int fret3){
    // Assigning to memeber varibles
    this->strumPin = strum;
    
    this->fretPin1 = fret1;
    this->fretPin2 = fret2;
    this->fretPin3 = fret3;

    setup();

    state = HIGH;
  } 

  void setup(void){
    pinMode(this->strumPin, INPUT_PULLUP);
    pinMode(fretPin1, INPUT_PULLUP);
    pinMode(fretPin2, INPUT_PULLUP);
    pinMode(fretPin3, INPUT_PULLUP);
  }

  int readStrumPin(){
    return digitalRead(this->strumPin);
  } 

  float getAnalogRead(int fretPin){
    float value = analogRead(fretPin);
    return (value/1023.0) * 5;
  }
  
  float selectReading(int trigger){
    float value;
    switch(trigger){
      case 1: 
        value = getAnalogRead(fretPin1);
        break;
      case 2: 
        value = getAnalogRead(fretPin2);
        break;
      case 3: 
        value = getAnalogRead(fretPin3);
        break;   
    }

    return value;
  }

};
#endif

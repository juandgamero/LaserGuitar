#include <Tone.h>
#include "pitches.h"
#include "pins.h"
#include "laser.h"

Laser *string1, *string2, *string3, *string4;
Tone tone1, tone2, tone3, tone4;

int fretIndex1, fretIndex2, fretIndex3, fretIndex4;
int fretSet4[4] = {NOTE_GS4, NOTE_A4, NOTE_AS4, NOTE_G4};
int fretSet3[4] = {NOTE_D4, NOTE_DS4, NOTE_CS4, NOTE_C4};
int fretSet2[4] = {NOTE_FS4, NOTE_G4, NOTE_F4,  NOTE_E4};
int fretSet1[4] = {NOTE_AS4, NOTE_B4, NOTE_C5,  NOTE_A4};

void setup() {
  // Output Monitor
  Serial.begin(9600);

  // Tone library to speaker pins
  tone1.begin(SPPIN1);
  tone2.begin(SPPIN2);
  tone3.begin(SPPIN3);
  tone4.begin(SPPIN4);

  // Set up objects with it's interrupts
  string1 = new Laser(SPIN1, FPIN1, FPIN0, FPIN2);
  attachInterrupt(digitalPinToInterrupt(string1->strumPin), append, CHANGE); // interrupt on diode voltage change

  string2 = new Laser(SPIN2, FPIN3, FPIN4, FPIN5);
  attachInterrupt(digitalPinToInterrupt(string2->strumPin), append2, CHANGE); // interrupt on diode voltage change

  string3 = new Laser(SPIN3, FPIN7, FPIN6, FPIN8);
  attachInterrupt(digitalPinToInterrupt(string3->strumPin), append3, CHANGE); // interrupt on diode voltage change

  string4 = new Laser(SPIN4, FPIN9, FPIN10, FPIN11);
  attachInterrupt(digitalPinToInterrupt(string4->strumPin), append4, CHANGE); // interrupt on diode voltage change

}
void loop() {
  getReadings();
  //delay(3000);

  fretIndex1 = checkFretPosition(string1);
  fretIndex2 = checkFretPosition(string2);
  fretIndex3 = checkFretPosition(string3);
  fretIndex4 = checkFretPosition(string4);

  // Laser 1
  if (string1->state == 0) {
    while (string1->state == 0) {
      tone1.play(fretSet1[fretIndex1], 200);
      if (string2->state == 0)
        tone2.play(fretSet2[fretIndex2], 200);
      if (string3->state == 0)
        tone3.play(fretSet3[fretIndex3], 200);
      if (string4->state == 0)
        tone4.play(fretSet4[fretIndex4], 200);
    }
  }
  // Laser 2
  if (string2->state == 0) {
    while (string2->state == 0) {
      tone2.play(fretSet2[fretIndex2], 200);
      if (string3->state == 0)
        tone3.play(fretSet3[fretIndex3], 200);
      if (string4->state == 0)
        tone4.play(fretSet4[fretIndex4], 200);
      if(string1->state == 0)
        tone1.play(fretSet1[fretIndex1],200);
    }
  }

  // Laser 3
  if (string3->state == 0) {
    while (string3->state == 0) {
      tone3.play(fretSet3[fretIndex3], 200);
      if (string4->state == 0)
        tone4.play(fretSet4[fretIndex4], 200);
      if(string1->state == 0)
        tone1.play(fretSet1[fretIndex1],200);
      if (string2->state == 0)
        tone2.play(fretSet2[fretIndex2], 200);
    }
  }

  // Laser 4
  if (string4->state == 0) {
    while (string4->state == 0) {
      tone4.play(fretSet4[fretIndex4], 200);
      if(string1->state == 0)
        tone1.play(fretSet1[fretIndex1],200);
      if (string2->state == 0)
        tone2.play(fretSet2[fretIndex2], 200);
      if (string3->state == 0)
        tone3.play(fretSet3[fretIndex3], 200);
    }
  }
}

void append () {
  string1->state = !string1->state;
}
void append2 () {
  string2->state = !string2->state;
}
void append3 () {
  string3->state = !string3->state;
}
void append4 () {
  string4->state = !string4->state;
}


int checkFretPosition(Laser *fretPostion) {
  if (fretPostion->selectReading(1) > 0.95)
    return 0;
  if (fretPostion->selectReading(2) > 0.95)
    return 1;
  if (fretPostion->selectReading(3) > 0.95)
    return 2;
  return 3;
}

void getReadings() {

  //Strum Reading
  Serial.print("Strum1 Reading: ");
  Serial.println(string1->readStrumPin()); //debugging purposes

  Serial.println("FRET 1: ");
  Serial.print(string1->selectReading(1));
  Serial.println("");

  Serial.println("FRET 2: ");
  Serial.print(string1->selectReading(2));
  Serial.println("");

  Serial.println("FRET 3: ");
  Serial.print(string1->selectReading(3));
  Serial.println("");
  Serial.println("");
  //----------------------------------------------------------------------
  Serial.print("Strum2 Reading: ");
  Serial.println(string2->readStrumPin()); //debugging purposes
  Serial.println("FRET 1: ");
  Serial.print(string2->selectReading(1));
  Serial.println("");

  Serial.println("FRET 2: ");
  Serial.print(string2->selectReading(2));
  Serial.println("");

  Serial.println("FRET 3: ");
  Serial.print(string2->selectReading(3));
  Serial.println("");
  Serial.println("");
  //----------------------------------------------------------------------
  Serial.print("Strum3 Reading: ");
  Serial.println(string3->readStrumPin()); //debugging purposes
  Serial.println("FRET 1: ");
  Serial.print(string3->selectReading(1));
  Serial.println("");

  Serial.println("FRET 2: ");
  Serial.print(string3->selectReading(2));
  Serial.println("");

  Serial.println("FRET 3: ");
  Serial.print(string3->selectReading(3));
  Serial.println("");
  Serial.println("");
  //----------------------------------------------------------------------
  Serial.print("Strum4 Reading: ");
  Serial.println(string4->readStrumPin()); //debugging purposes
  Serial.println("FRET 1: ");
  Serial.print(string4->selectReading(1));
  Serial.println("");

  Serial.println("FRET 2: ");
  Serial.print(string4->selectReading(2));
  Serial.println("");

  Serial.println("FRET 3: ");
  Serial.print(string4->selectReading(3));
  Serial.println("");
  Serial.println("");

}

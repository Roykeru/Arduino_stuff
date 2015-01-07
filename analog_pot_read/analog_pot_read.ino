#include <MIDI.h>
#include <midi_Defs.h>
#include <midi_Message.h>
#include <midi_Namespace.h>
#include <midi_Settings.h>

MIDI_CREATE_DEFAULT_INSTANCE();

const int potpin = A0;
int prePotValue;

void setup(){
  MIDI.begin(1);
}

void loop(){
  
  int potVal = round(analogRead(potpin)*0.1240234375);
 
  if (potVal != prePotValue){
    MIDI.sendControlChange(0,potVal,1);

    prePotValue = potVal;
  }
}

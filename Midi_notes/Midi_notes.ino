#include <MIDI.h>
#include <midi_Defs.h>
#include <midi_Message.h>
#include <midi_Namespace.h>
#include <midi_Settings.h>

#define LENGTH(a) (sizeof((a))/sizeof((a)[0]))
#define ON LOW
#define OFF HIGH
MIDI_CREATE_DEFAULT_INSTANCE();

//long lastDebounceTime = 0;  // the last time the output pin was toggled
const long debounceDelay = 10; // the debounce time; increase if the output flickers

struct {
  byte pin;
  byte notePitch;
  long lastDebounceTime;
  int buttonState;
  int lastButton;
}
  data[] = {
    {13,54,0,OFF,ON,},
    {12,58,0,OFF,ON,},
    {11,61,0,OFF,ON,},
    {10,66,0,OFF,ON,},
    {9,69,0,OFF,ON,},
  };

void setup(){
  MIDI.begin(1);

  for (int i=0; i<LENGTH(data); ++i){
    pinMode(data[i].pin, INPUT_PULLUP);
  }
}
void loop()
{
  for (int i=0; i<LENGTH(data); ++i){

    int reading = digitalRead(data[i].pin);
    long now = millis();
    long delta = now - data[i].lastDebounceTime;

    // If the switch changed, due to noise or pressing:
    if (reading == data[i].lastButton){
      //if (data[i].lastDebounceTime == 0) {
        // reset the debouncing timer
        data[i].lastDebounceTime = millis();
      //}
    }else{
      if (delta > debounceDelay && reading != ON) {
        data[i].lastDebounceTime = 0;
        MIDI.sendNoteOff(data[i].notePitch,0,1);
        //data[i].buttonState = reading;
        data[i].lastButton = reading;
        
      }
    }
    if (delta > debounceDelay && reading != OFF) {
      
      // whatever the reading is at, it's been there for longer
      // than the debounce delay, so take it as the actual current state:

      // if the button state has changed:
      if (reading != data[i].buttonState) {
        data[i].buttonState = reading;

        // only toggle the LED if the new button state is HIGH
      }
      MIDI.sendNoteOn(data[i].notePitch,127,1);
      
      
      data[i].lastButton = reading;
      }/* else {
      data[i].buttonState = reading;
    
  }*/
  }
}
  

#include <MIDI.h>
#include <midi_Defs.h>
#include <midi_Message.h>
#include <midi_Namespace.h>
#include <midi_Settings.h>


#define NUM_TRIANGLES 255
#define LENGTH(a) (sizeof((a))/sizeof((a)[0]))
#define ON LOW
#define OFF HIGH
MIDI_CREATE_DEFAULT_INSTANCE();

const byte ledPin = 10;
int triangle[NUM_TRIANGLES];
int curInt;

void setup() {
  Serial.begin(115200);
  pinMode(ledPin, OUTPUT);

  curInt = 0;

  for (int i = 0; i < 256 ; i++) {
    long oneVal = (fmod(millis(), (2 * 127)) - 127);
    long curVal = (127 - abs(oneVal));
    oneVal = curVal * 127;
    triangle[i] = oneVal / 127;
 
  }
}

byte Tringle(long amplitude, long period) {
  long oneVal = (fmod(millis(), (2 * period)) - period);
  long curVal = (period - abs(oneVal));
  oneVal = curVal * amplitude;
  return (byte)(oneVal / period);
}

void loop() {
  //int curVal = triangle[curInt];
  //MIDI.sendControlChange (0,curVal,1);
  Serial.println(curInt);

  if (curInt == 0) {
    digitalWrite(ledPin, HIGH);
  }
  else if (curInt == 127) {
    digitalWrite(ledPin, LOW);

  }
  if (curInt = 255) {
    curInt = 0;
  }
  else {
    curInt = curInt + 1;
    Serial.print(":)");
  }


}

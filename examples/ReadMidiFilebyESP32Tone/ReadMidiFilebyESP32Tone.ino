// esp32 SPIFFS library
#include "FS.h"
#include "SPIFFS.h"
// MD_MIDIFile for SPIFFS
#include <MD_MIDIFile.h>
#include <MD_MIDIHelper.h>
// ESP32 servo library for tone
#include <ESP32Servo.h>
// hertz list , from arduino tone example
#include "pitches.h"


#define USE_MIDI  0   // set to 1 to enable MIDI output, otherwise debug output

#if USE_MIDI // set up for direct MIDI serial output

#define DEBUG(x)
#define DEBUGX(x)
#define DEBUGS(s)
#define SERIAL_RATE 31250

#else // don't use MIDI to allow printing debug statements

#define DEBUG(x)  Serial.print(x)
#define DEBUGX(x) Serial.print(x, HEX)
#define DEBUGS(s) Serial.print(F(s))
#define SERIAL_RATE 115200

#endif // USE_MIDI

int leftpin =18;   // connect to speaker direct
int rightpin = 19; // too!

int notes[] = {NOTE_C1 ,NOTE_CS1 ,NOTE_D1 ,NOTE_DS1 ,NOTE_E1 ,NOTE_F1 ,NOTE_FS1 ,NOTE_G1 ,NOTE_GS1 ,NOTE_A1 ,NOTE_AS1 ,NOTE_B1 ,NOTE_C2 ,NOTE_CS2 ,NOTE_D2 ,NOTE_DS2 ,NOTE_E2 ,NOTE_F2 ,NOTE_FS2 ,NOTE_G2 ,NOTE_GS2 ,NOTE_A2 ,NOTE_AS2 ,NOTE_B2 ,NOTE_C3 ,NOTE_CS3 ,NOTE_D3 ,NOTE_DS3 ,NOTE_E3 ,NOTE_F3 ,NOTE_FS3 ,NOTE_G3 ,NOTE_GS3 ,NOTE_A3 ,NOTE_AS3 ,NOTE_B3,NOTE_C4  ,NOTE_CS4 ,NOTE_D4  ,NOTE_DS4 ,NOTE_E4  ,NOTE_F4  ,NOTE_FS4 ,NOTE_G4  ,NOTE_GS4 ,NOTE_A4  ,NOTE_AS4 ,NOTE_B4  ,NOTE_C5  ,NOTE_CS5 ,NOTE_D5  ,NOTE_DS5 ,NOTE_E5  ,NOTE_F5  ,NOTE_FS5 ,NOTE_G5  ,NOTE_GS5 ,NOTE_A5  ,NOTE_AS5 ,NOTE_B5  ,NOTE_C6  ,NOTE_CS6 ,NOTE_D6  ,NOTE_DS6 ,NOTE_E6  ,NOTE_F6  ,NOTE_FS6 ,NOTE_G6  ,NOTE_GS6 ,NOTE_A6  ,NOTE_AS6 ,NOTE_B6  ,NOTE_C7  ,NOTE_CS7 ,NOTE_D7  ,NOTE_DS7 ,NOTE_E7  ,NOTE_F7  ,NOTE_FS7 ,NOTE_G7  ,NOTE_GS7 ,NOTE_A7  ,NOTE_AS7 ,NOTE_B7  ,NOTE_C8  ,NOTE_CS8 ,NOTE_D8  ,NOTE_DS8};

#define FORMAT_SPIFFS_IF_FAILED true

void midiCallback(midi_event *pev)
// Called by the MIDIFile library when a file event needs to be processed
// thru the midi communications interface.
// This callback is set up in the setup() function.
{  
  int pin = 0;
  if(pev->data[0] == 0x90 || pev->data[0] == 0x80 ){
    pin = (pev->track == 0) ? 18 : 19;
    if(pev->data[2] == 0){
      tone(pin, 0);
    }
    else {
      tone(pin, notes[pev->data[1] -12]);
    } 
  }
}

MD_MIDIFile SMF;
static enum { S_IDLE, S_PLAYING, S_END, S_WAIT_BETWEEN } state = S_IDLE;

void setup() {
  int  err;
  Serial.begin(SERIAL_RATE);
  if(!SPIFFS.begin(FORMAT_SPIFFS_IF_FAILED)){
        Serial.println("SPIFFS Mount Failed");
        return;
  }
  SMF.begin(SPIFFS);
  SMF.setMidiHandler(midiCallback);

  err = SMF.load("/score.mid");
    if (err != MD_MIDIFile::E_OK)
    {
      Serial.print("SMF load Error ");
      Serial.println(err);
      state = S_END;
    }
    else {
      // SMF.dump(); // for debug    
    }
}

void loop() {
  if (!SMF.isEOF() && state != S_END) {
    SMF.getNextEvent();
  }
  else {
    if(state != S_END){
      Serial.println("Stop music");
      noTone(leftpin);
      noTone(rightpin);
      state = S_END;
      SMF.pause(true);
    }
  }    
}

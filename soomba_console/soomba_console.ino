#include "ir_def.h"
#include "IRLibAll.h"
#include <IRLibSendBase.h>    //We need the base code
#include <IRLib_HashRaw.h>    //Only use raw sender
#include <Adafruit_NeoPixel.h>


typedef uint16_t* ir_code;
const int KHZ = 38;
const int BAUD_RATE = 9600;
const int EYES_PIN = 6;

IRsendRaw sender; // Defaults to pin 3
Adafruit_NeoPixel eyeStrip = Adafruit_NeoPixel(24, EYES_PIN, NEO_GRB + NEO_KHZ800);

/* RECEIVING CODE
IRrecvPCI myReceiver(2); // Defaults to pin 2
IRdecode decoder;
*/

void setup() {
	Serial.begin(BAUD_RATE);
  delay(2000); while (!Serial);
  
  eyeStrip.begin();
  eyeStrip.show();
  
  // receiver.enableIRIn(); // Start the receiver
  Serial.println(F("Ready to receive IR signals"));
}

ir_code string2code(String command) {
	if (command.equals("up")) {
		return ir_up;
	} else if (command.equals("down")) {
		return ir_down;
	} else if (command.equals("left")) {
		return ir_left;
	} else if (command.equals("right")) {
		return ir_right;
	} else {
		return NULL;
	}
}

void sendCommand(char * command) {
    ir_code code = string2code(command);
    if (code != NULL) {
      Serial.print("Executing: ");
      Serial.println(command);
      sender.send(code, CODE_SIZE,KHZ);//Pass the buffer,length, optionally frequency
    } else {
      Serial.print("Don't know how to: ");
      Serial.println(command);
    }
}

void simpleTest() {
  while (true) {
    for(int i = 0; i < 6; i++) {
      sendCommand("up");
      delay(200);
    }
    for(int i = 0; i < 2; i++) {
      sendCommand("right");
      delay(200);
    }
    for(int i = 0; i < 3; i++) {
      sendCommand("up");
      delay(200);
    }
    for(int i = 0; i < 6; i++) {
      sendCommand("left");
      delay(200);
    }
  }
}

void cycle_eyes() {
  for(int i=0; i< eyeStrip.numPixels(); i++) {
    eyeStrip.setPixelColor(i, 21, 19, 23);
  }
  eyeStrip.show();
}

void loop() {
  // simpleTest();

  cycle_eyes();

  // Keep receiving commands
	if (Serial.available()) {
		String command = Serial.readStringUntil('\n');
    sendCommand(command.c_str());
	}

  /*
  RECEIVING CODE (removed to save RAM)
  // Continue looping until you get a complete signal received
  if (myReceiver.getResults()) {
    myDecoder.decode();           //Decode it
    Serial.println("COMPLEX:");
    myDecoder.dumpResults(true);  //Now print results. Use false for less detail
    myReceiver.enableIRIn();      //Restart receiver
  }*/
}

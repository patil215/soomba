#include "ir_def.h"
#include "IRLibAll.h"
#include <IRLibSendBase.h>    //We need the base code
#include <IRLib_HashRaw.h>    //Only use raw sender

typedef uint16_t* ir_code;
const int KHZ = 38;
const int BAUD_RATE = 9600;

IRrecvPCI myReceiver(2);
IRdecode myDecoder;
IRsendRaw mySender;

void setup() {
	Serial.begin(BAUD_RATE);
  
  delay(2000); while (!Serial); //delay for Leonardo
  myReceiver.enableIRIn(); // Start the receiver
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

void loop() {
	if (Serial.available()) {
		String command = Serial.readStringUntil('\n');
		ir_code code = string2code(command);
		if (code != NULL) {
			Serial.print("Doing: ");
			Serial.println(command);
      mySender.send(code, CODE_SIZE,KHZ);//Pass the buffer,length, optionally frequency
		} else {
			Serial.print("Don't know how to: ");
			Serial.println(command);
		}
	}

  // Continue looping until you get a complete signal received
  if (myReceiver.getResults()) {
    myDecoder.decode();           //Decode it
    Serial.println("COMPLEX:");
    myDecoder.dumpResults(true);  //Now print results. Use false for less detail
    myReceiver.enableIRIn();      //Restart receiver
  }
}

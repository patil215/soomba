#include "ir_def.h"
#include <IRLibSendBase.h>    //We need the base code
#include <IRLib_HashRaw.h>    //Only use raw sender
#include <Adafruit_NeoPixel.h>


typedef uint16_t* ir_code;
const int KHZ = 38;
const int BAUD_RATE = 9600;
const int EYES_PIN = 6;
const int BASE_PIN = 5;
bool TURN_EYE_ON = false;

int trigPin = 11;    //Trig - green Jumper
int echoPin = 12;    //Echo - yellow Jumper
long duration, cm, inches;

IRsendRaw sender; // Defaults to pin 3
Adafruit_NeoPixel eyeStrip = Adafruit_NeoPixel(24, EYES_PIN, NEO_GRB + NEO_KHZ800);
Adafruit_NeoPixel baseStrip = Adafruit_NeoPixel(60, BASE_PIN, NEO_RGBW + NEO_KHZ800);

/* RECEIVING CODE
#include "IRLibAll.h"
IRrecvPCI myReceiver(2); // Defaults to pin 2
IRdecode decoder;
*/

void setup() {
	Serial.begin(BAUD_RATE);
	delay(2000); while (!Serial);
  
	// receiver.enableIRIn(); // Start the receiver

  eyeStrip.begin();
  eyeStrip.show();

  baseStrip.begin();
  baseStrip.show();
  
  pinMode(trigPin, OUTPUT);
  pinMode(echoPin, INPUT);
  
  // receiver.enableIRIn(); // Start the receiver
	Serial.println("ready");

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

void sendEyes(String command) {
  if (command.equals("up")) {
    setLeftEye(0, 200, 0);
    setRightEye(0, 200, 0);
  } else if (command.equals("down")) {
    setLeftEye(200, 200, 0);
    setRightEye(200, 200, 0);
  } else if (command.equals("left")) {
    if (TURN_EYE_ON) {
      setLeftEye(0xff,0x8c,00);
      setRightEye(100,100,100);
      TURN_EYE_ON = false;
    } else {
      setLeftEye(0,0,0);
      setRightEye(100,100,100);
      TURN_EYE_ON = true;
    }
  } else if (command.equals("right")) {
    if (TURN_EYE_ON) {
      setRightEye(0xff,0x8c,00);
      setLeftEye(100,100,100);
      TURN_EYE_ON = false;
    } else {
      setRightEye(0,0,0);
      setLeftEye(100,100,100);
      TURN_EYE_ON = true;
    }
  }
}

int index = 0;
void sendCommand(char * command) {
	ir_code code = string2code(command);
	if (code != NULL) {

      
    // The sensor is triggered by a HIGH pulse of 10 or more microseconds.
    // Give a short LOW pulse beforehand to ensure a clean HIGH pulse:
    digitalWrite(trigPin, LOW);
    delayMicroseconds(5);
    digitalWrite(trigPin, HIGH);
    delayMicroseconds(10);
    digitalWrite(trigPin, LOW);
   
    // Read the signal from the sensor: a HIGH pulse whose
    // duration is the time (in microseconds) from the sending
    // of the ping to the reception of its echo off of an object.
    pinMode(echoPin, INPUT);
    duration = pulseIn(echoPin, HIGH);
   
    // convert the time into a distance
    cm = (duration/2) / 29.1;
    inches = (duration/2) / 74; 

    if (inches < 20) {
      index += 1;
      index %= 30;
      if (index > 15) {
        code = string2code("right");
      } else if (index > 0) {
        code = string2code("left");
      }
    }

  
		sender.send(code, CODE_SIZE, KHZ);
		Serial.print("good ");
		Serial.println(command);
	} else {
		Serial.print("bad ");
		Serial.print("unknown_command_");
		Serial.print(command);
		Serial.println();
	}
}

void simpleTest() {
  while (true) {
    for(int i = 0; i < 6; i++) {
      sendCommand("up");
      sendEyes("up");
      delay(200);
    }
    for(int i = 0; i < 10; i++) {
      sendCommand("right");
      sendEyes("right");
      delay(200);
    }
    for(int i = 0; i < 6; i++) {
      sendCommand("down");
      sendEyes("down");
      delay(200);
    }
    for(int i = 0; i < 10; i++) {
      sendCommand("left");
      sendEyes("left");
      delay(200);
    }
    rainbowCycle();
    delay(1000);
  }
}

void rainbowCycle() {
  uint16_t i, j;

  for(j=0; j<256*5; j++) { // 5 cycles of all colors on wheel
    for(i=0; i< 12; i++) {
      eyeStrip.setPixelColor(i, Wheel(((i * 256 / 12) + j) & 255));
    }
    eyeStrip.show();
  }
}
uint32_t Wheel(byte WheelPos) {
  WheelPos = 255 - WheelPos;
  if(WheelPos < 85) {
    return eyeStrip.Color(255 - WheelPos * 3, 0, WheelPos * 3);
  }
  if(WheelPos < 170) {
    WheelPos -= 85;
    return eyeStrip.Color(0, WheelPos * 3, 255 - WheelPos * 3);
  }
  WheelPos -= 170;
  return eyeStrip.Color(WheelPos * 3, 255 - WheelPos * 3, 0);
}

void setLeftEye(int r, int g, int b) {
  for(int i=0; i< 12; i++) {
    eyeStrip.setPixelColor(i, r, g, b);
  }
  for (int i = 0; i < 15; i++) {
    baseStrip.setPixelColor(i, g, r, b);
  }
  for (int i = 45; i < 60; i++) {
    baseStrip.setPixelColor(i, g, r, b);
  }
  eyeStrip.show();
  baseStrip.show();
}

void setRightEye(int r, int g, int b) {
  for(int i = 12; i< 24; i++) {
    eyeStrip.setPixelColor(i, r, g, b);
  }
  for (int i=15; i < 45; i++) {
    baseStrip.setPixelColor(i, g, r, b);
  }
  eyeStrip.show();
  baseStrip.show();
}
//void cycle_eyes() {
//  for(int i=0; i< eyeStrip.numPixels(); i++) {
//    eyeStrip.setPixelColor(i, 21, 19, 23);
//  }
//  eyeStrip.show();
//}

void loop() {
//   simpleTest();


  // Keep receiving commands
	if (Serial.available()) {
		String command = Serial.readStringUntil('\n');
    sendCommand(command.c_str());
    sendEyes(command.c_str());
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

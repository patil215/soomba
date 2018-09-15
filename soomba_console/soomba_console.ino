#include "ir_def.h"

#include <IRremote.h>
IRsend irsend;
typedef uint16_t* ir_code;
const int KHZ = 38;
const int BAUD_RATE = 9600;

void setup() {
	Serial.begin(BAUD_RATE);
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
	/* irsend.sendRaw(ir_down, 83, khz); */
	/* delay(1000); */

	if (Serial.available()) {
		String command = Serial.readStringUntil('\n');
		ir_code code = string2code(command);
		if (code != NULL) {
			Serial.print("Doing: ");
			Serial.println(command);
			irsend.sendRaw(code, CODE_SIZE, KHZ);
		} else {
			Serial.print("Don't know how to: ");
			Serial.println(command);
		}
	}
}

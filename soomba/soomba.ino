#include <IRremoteESP8266.h>    // IR remote lib for esp8266
#include <IRsend.h>             // IR sending
#define IR_LED 4                // ESP8266 GPIO pin to use for blaster (4 is D2 on nodeMCU devBoard)
IRsend irsend(IR_LED);          // Set the GPIO to send IR signals
int khz = 38;                   // 38kHz carrier frequency

uint16_t data[99] = { 3000 , 3000 , 500 , 500 , 500 , 1500 , 500 , 1500 , 500 , 500 , 500 , 1500 , 500 , 500 , 500 , 500 , 500 , 500 , 500 , 500 , 500 , 1500 , 1500 , 1500 , 1500 , 1500 , 1500 , 1500 , 1500 , 1500 , 1500 , 1500 , 1500 , 1500 , 1500 , 500 , 1500 , 500 , 1500 , 500 , 1500 , 500 , 500 , 500 , 500 , 500 , 500 , 1500 , 500 , 500 , 500 , 500 , 500 , 500 , 500 , 1500 , 500 , 500 , 500 , 1500 , 500 , 500 , 500 , 500 , 500 , 500 , 500 , 1500 , 500 , 1500 , 500 , 1500 , 500 , 1500 , 500 , 1500 , 500 , 1500 , 500 , 1500 , 500 , 1500 , 500 , 500 , 500 , 500 , 500 , 500 , 500 , 1500 , 500 , 500 , 500 , 500 , 500 , 500 , 500 , 500 , 500};

void setup() {
  // put your setup code here, to run once:
  Serial.begin(74880);
  Serial.println("Starting sender");
  irsend.begin();
}

void loop() {
  // put your main code here, to run repeatedly:
  irsend.sendRaw(data, 99, khz);   // Send Down signal on press
  delay(1000);
}

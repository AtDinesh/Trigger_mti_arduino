// avr-libc library includes
#include <avr/io.h> //  can be omitted
#include <avr/interrupt.h> // can be omitted

#define LEDPIN 13
#define MTI_TRIGGER_PIN 2

bool blinkState = false;
int i=0;

void setup()
{
  Serial.begin(1000000);
  delay(500);
  
  // configure Arduino LED for
    pinMode(LEDPIN, OUTPUT);
  // configure Trigger pin for MTi
    pinMode(MTI_TRIGGER_PIN, OUTPUT);
}

void loop() {
  while(1){
    i++;
    if(i==100){ //trigger camera at 30 Hz
      //digitalWrite(A0, HIGH);
      blinkState = !blinkState;
      digitalWrite(MTI_TRIGGER_PIN, blinkState);
      digitalWrite(LEDPIN, blinkState);
    }
    
    if(blinkState){
      delayMicroseconds(5000);
      //digitalWrite(A0, LOW);
      blinkState = !blinkState;
      digitalWrite(MTI_TRIGGER_PIN, blinkState);
      digitalWrite(LEDPIN, blinkState);
      i=0;
    }
    delay(10);
  }
}

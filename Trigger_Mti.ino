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
    
    //////////////////// TEST 1 /////////////////////////
// initialize Timer1
cli();         // disable global interrupts
TCCR1A = 0;    // set entire TCCR1A register to 0
TCCR1B = 0;    // set entire TCCR1A register to 0

// enable Timer1 overflow interrupt:
TIMSK1 |= (1 << TOIE1);
// Preload with value 3036
//use 64886 for 100Hz
//use 64286 for 50 Hz
//use 34286 for 2 Hz
//TCNT1=0x0F00; // a little more than 1 KHz
// use TCNT1 = 0xF700 for 25 Hz
// use TCNT1 = 0xF870 for 30 Hz
TCNT1 = 0xF870;// Set CS10 bit so timer runs at clock speed: (no prescaling)
TCCR1B |= (1 << CS12); // Sets bit CS12 in TCCR1B
// This is achieved by shifting binary 1 (0b00000001)
// to the left by CS12 bits. This is then bitwise
// OR-ed into the current value of TCCR1B, which effectively set
// this one bit high. Similar: TCCR1B |= _BV(CS12);
//  or: TCCR1B= 0x04;

// enable global interrupts:
sei();
///////////////////////////////////////////////////

}//end of setup\

ISR(TIMER1_OVF_vect)
{
  blinkState = !blinkState;
  digitalWrite(MTI_TRIGGER_PIN, blinkState);
  digitalWrite(LEDPIN, blinkState);
  delayMicroseconds(2000);
  blinkState = !blinkState;
  digitalWrite(MTI_TRIGGER_PIN, blinkState);
  digitalWrite(LEDPIN, blinkState);
  
TCNT1=0xF870; // reload the timer preload     0xFFC2

}

void loop() {
//  while(1){
//    i++;
//    if(i==33){ //trigger camera at 30 Hz
//      //digitalWrite(A0, HIGH);
//      blinkState = !blinkState;
//      digitalWrite(MTI_TRIGGER_PIN, blinkState);
//      digitalWrite(LEDPIN, blinkState);
//    }
//    
//    if(blinkState){
//      delayMicroseconds(10000);
//      //digitalWrite(A0, LOW);
//      blinkState = !blinkState;
//      digitalWrite(MTI_TRIGGER_PIN, blinkState);
//      digitalWrite(LEDPIN, blinkState);
//      i=0;
//    }
//    delay(10);
//  }
}

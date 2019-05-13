const int CK = 0;
const int A = 1;
const int B = 2;


#define SetAllLedsOff() shiftOut(A, CK, MSBFIRST, 0)
#define SetAllLedsOn() shiftOut(A, CK, MSBFIRST, 0xFF)
#define AnimationDelay 250
/*
 * Toggle leds states an amount of time and waitMS between flashes
 */
void flash(int times, int waitTime, int stateA, int stateB )
{
  int i=0;
  while( i < times ){
    //SetAllLedsOff();
    shiftOut(A, CK, MSBFIRST, stateA);
    delay(waitTime);
    //SetAllLedsOn();
    shiftOut(A, CK, MSBFIRST, stateB);
    delay(waitTime);
    i++;
  }
}

// the setup function runs once when you press reset or power the board
void setup() {
  // initialize digital pin LED_BUILTIN as an output.
  pinMode(CK, OUTPUT);
  pinMode(A, OUTPUT);
  pinMode(B, OUTPUT);
  digitalWrite(CK, LOW);
  digitalWrite(B, HIGH);   // turn the LED on (HIGH is the voltage level)
  SetAllLedsOff();
}

byte leds;
int i;
/*
 * This loop turns leds on from start to end and then back
 * then flashes all
 * then flash from corners
 */
void loop() {
  //Loop forward
  leds = 1;
  for( i=0;i<8;i++){
    /*leds = shift | leds;
    shift = shift << 1;*/
    shiftOut(A, CK, MSBFIRST, leds);
    delay(AnimationDelay);
    leds = (leds << 1) | leds;
  }
  //Loop backward
  leds = 0xFF;
  for( i=0;i<8;i++){
    leds = leds >> 1;;
    shiftOut(A, CK, MSBFIRST, leds);
    delay(AnimationDelay);
  }
  //Flash all 2 times
  flash(2, AnimationDelay/2,0x0F,0xF0 );
  //Flash from corners of two
  for( i=0;i<5;i++){
    flash(1, AnimationDelay/4,0x03,0x30 );
    flash(1, AnimationDelay/4,0x0C,0xC0 );
    flash(1, AnimationDelay/4,0x03,0x30 );
    flash(1, AnimationDelay/4,0x0C,0xC0 );
  }
}

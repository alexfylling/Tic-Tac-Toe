//Pin connected to ST_CP of 74HC595
int latchPin = 9;
//Pin connected to SH_CP of 74HC595
int clockPin = 8;
////Pin connected to DS of 74HC595
int dataPin = 10;

long testLol[9] = {0x020001, 0x010002, 0x08004, 0x04008, 0x02010, 0x01020, 0x0840, 0x0480, 0x0300};

void setup() {
  //set pins to output because they are addressed in the main loop
  pinMode(latchPin, OUTPUT);
  Serial.begin(9600);
}

void loop() {
    for(int i = 0; i < 9; i++){
		shiftOut(dataPin, clockPin, testLol[i]);
		delay(100);
	}
 }

// Shifting function to light leds
void shiftOut(int myDataPin, int myClockPin, long myDataOut) {
	//Shifts out 18 bits to board
	

  int i=0;
  int pinState;
  pinMode(myClockPin, OUTPUT);
  pinMode(myDataPin, OUTPUT);

  digitalWrite(myDataPin, 0);
  digitalWrite(myClockPin, 0);
  digitalWrite(latchPin, 0);

  for (i=17; i>=0; i--)  {
    digitalWrite(myClockPin, 0);

    //if the value passed to myDataOut and a bitmask result 
    // true then... so if we are at i=6 and our value is
    // %11010100 it would the code compares it to %01000000 
    // and proceeds to set pinState to 1.
    if ( myDataOut & (1L<<i) ) {
      pinState= 1;
    }
    else {	
      pinState= 0;
    }

    //Sets the pin to HIGH or LOW depending on pinState
    digitalWrite(myDataPin, pinState);
    //register shifts bits on upstroke of clock pin  
    digitalWrite(myClockPin, 1);
    //zero the data pin after shift to prevent bleed through
    digitalWrite(myDataPin, 0);
    Serial.print(pinState);
  }
  //stop shifting
  digitalWrite(myClockPin, 0);
  digitalWrite(latchPin, 1);
  Serial.println();
}
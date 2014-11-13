//Pin connected to ST_CP of 74HC595
const int latchPin = 9;
//Pin connected to SH_CP of 74HC595
const int clockPin = 8;
////Pin connected to DS of 74HC595
const int dataPin = 10;

const int btn1 = 1;
const int btn2 = 2;
const int btn3 = 3;
const int btn4 = 4;

const int d_UP = 1;
const int d_DOWN = 2;
const int d_LEFT = 3;
const int d_RIGHT = 4;

const int curPlayer = 1;

int cursPos = 0x01;
int gameGrid = 0x00;

long testLol[] = {1, 2, 4, 8, 16, 32, 64, 128, 256, 512, 1024, 2048, 4096, 8192};

void setup() {
  //set pins to output because they are addressed in the main loop
  pinMode(latchPin, OUTPUT);
  pinMode(btn1, INPUT);
  pinMode(btn2, INPUT);
  pinMode(btn3, INPUT);
  pinMode(btn4, INPUT);
  Serial.begin(9600);
}

void loop() {
		
			shiftOut(dataPin, clockPin, random(0, 262143));
			delay(100);
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

int buttonPush(){
	int result = 0;
	if(digitalRead(btn1) == HIGH){
		result = 1;
	}
	else if(digitalRead(btn2) == HIGH){
		result = 2;
	}
	else if(digitalRead(btn3) == HIGH){
		result = 3;
	}
	else if(digitalRead(btn4) == HIGH){
		result = 4;
	}
	return result;
}

void moveCursor(int dir){
		switch(dir){
		//Move up
			case d_UP:
				//If not on top row
				if(!(cursPos == 0 || cursPos == 1 || cursPos == 2)){
					cursPos -= 3;
				}
			break;
			
			case d_DOWN:
				//If not on bottom row
				if(!(cursPos == 6 || cursPos == 7 || cursPos == 8)){
					cursPos += 3;
				}
			break;
			
				
			case d_LEFT:
				//If not in top left corner
				if(!(cursPos == 0){
					cursPos -= 1;
				}
			break;
			
			case d_RIGHT:
				//If not in bottom right corner
				if(!(cursPos == 8 /*&& !(gameGrid & 1<<cursPos+1) )*/){
					cursPos += 1;
				}
			break;
			
			default:
			//Maybe something, dunno yet
			break;
		}			
}

void drawCursor(int pos, int player){
}
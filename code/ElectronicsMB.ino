/*
  Blink
  Turns on an LED on for one second, then off for one second, repeatedly.

  Most Arduinos have an on-board LED you can control. On the Uno and
  Leonardo, it is attached to digital pin 13. If you're unsure what
  pin the on-board LED is connected to on your Arduino model, check
  the documentation at http://www.arduino.cc

  This example code is in the public domain.

  modified 8 May 2014
  by Scott Fitzgerald
 */
const int pinarray[] = {15,2,3,4,5,6,7,8,9,10,11,12};
int curpos = 0;
int lastpos = -1;
const int arrayElements = sizeof(pinarray)/sizeof(pinarray[0]);

// Pin Names
const int TRUSTWORTHY = 15;   //points to Analog 1
const int LOYAL = 2;
const int HELPFUL = 3;
const int FRIENDLY = 4;
const int COURTEOUS = 5;
const int KIND = 6;
const int OBEDIENT = 7;
const int CHEERFUL = 8;
const int THRIFTY = 9;
const int BRAVE = 10;
const int CLEAN = 11;
const int REVERENT = 12;
const int BUTTON = A3;
const int POT = A0;

// the setup function runs once when you press reset or power the board
void setup() {

  for (int i=0; i<=arrayElements; ++i) {
    pinMode(pinarray[i], OUTPUT);
  }

  pinMode(BUTTON, INPUT_PULLUP);
  Serial.begin(9600);
  
}

// the loop function runs over and over again forever
void loop() {

  int menuValue;

  menuValue = menu();

  switch (menuValue) {
    case 0:
      spinner();
      break;
    case 1:
      break;
  }
    
  delay(20);
 
}

int menu() {
  int selected;

  while(digitalRead(BUTTON)) {
    selected = getMenuValue();
    digitalWrite(pinarray[lastpos], LOW);
    digitalWrite(pinarray[selected], HIGH);
    lastpos = selected;
    delay(5);
  }
  
  return getMenuValue();
}

int getMenuValue() {
  int l, inputval;

  inputval = analogRead(0);
  
  for(l=0; l<=11; ++l) {
    if (inputval >= (l*85) && inputval < ((l+1)*85)) {
      return 11-l;
    }
  }

  return 0;
}

void spinner() {
  while (1 != 0) {
    int waitTime;
  
    if (lastpos != -1) {
      digitalWrite(pinarray[curpos], LOW);
    }
  
    lastpos = curpos;
    ++curpos;
  
    //Serial.print("input: ");
    //Serial.println(analogRead(0));
    
    if (curpos >= arrayElements) {
      curpos = 0;
    }
  
    //Serial.print("Curpos After: ");
    //Serial.println(curpos);
    //Serial.println(pinarray[curpos]);
  
    digitalWrite(pinarray[curpos], HIGH);
    
    //delay(1000);              // wait for a second
    waitTime = analogRead(0);
  
    if (waitTime < 3) {
      waitTime = 3;
    }
    
    delay(waitTime);
  }
}


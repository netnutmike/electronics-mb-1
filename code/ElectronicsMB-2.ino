
// Setup array of pins and colors
const int pinArray[] = {15,2,3,4,5,6,7,8,9,10,11,12};
int greenArray[] = {15,4,7,10};                    // Array of all green LEDs
int yellowArray[] = {2,5,8,11};                    // Array of all yellow LEDs
int redArray[] = {3,6,9,12};                       // Array of all red LEDs
int extraLED[] = {16,16,16,16};

// current menu / selection location and last position
int curpos = 0;
int lastpos = -1;

// spin up game values
int spinRate = 0;
int nextButtonRead = 0;
int nextMoveTime = 0;
const int buttonReadMillis = 20;

// Array size calculations
const int arrayElements = sizeof(pinArray)/sizeof(pinArray[0]);
const int colorElements = sizeof(greenArray)/sizeof(greenArray[0]);

// Direction constants
const int CLOCKWISE = 1;
const int COUNTERCLOCKWISE = 2;

// Notification Parameters
const int delayBetweenFlashes = 100;
const int delayBetweenRepeats = 500;

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

// Morse code values
struct dictionnaryEntry {
	char character;
	String signal;
};

int const TIME_UNIT = 200;

dictionnaryEntry dictionnary[36] = {
	{ 'a', ".-" },
  	{ 'b', "-..." },
  	{ 'c', "-.-." } ,
        { 'd', "-.." },
        { 'e', "." },
        { 'f', "..-." },
        { 'g', "--." },
        { 'h', "...." },
        { 'i', ".." },
        { 'j', ".---" },
        { 'k', "-.-" },
        { 'l', ".-.." },
        { 'm', "--" },
        { 'n', "-." },
        { 'o', "---" },
        { 'p', ".--." },
        { 'q', "--.-" },
        { 'r', ".-." },
        { 's', "..." },
        { 't', "-" },
        { 'u', "..-" },
        { 'v', "...-" },
        { 'w', ".--" },
        { 'x', "-..-" },
        { 'y', "-.--" },
        { 'z', "--.." },
  	{ '0', "-----" },
        { '1', ".----" },
        { '2', "..---" },
        { '3', "...--" },
        { '4', "....-" },
        { '5', "....." },
        { '6', "-...." },
        { '7', "--..." },
        { '8', "---.." },
        { '9', "----."}
};

// the setup function runs once when you press reset or power the board
void setup() {

  for (int i=0; i<=arrayElements; ++i) {
    pinMode(pinArray[i], OUTPUT);
  }

  pinMode(BUTTON, INPUT_PULLUP);
  Serial.begin(9600);
  
}

// the loop function runs over and over again forever
void loop() {

  int menuValue;

  menuValue = menu();

  clearAllLEDs();
  
  switch (menuValue) {
    case 0:
      spinner();
      break;
    case 1:
      randomgame();
      break;
    case 2:
      spinupgame();
      break;
    case 3:
      stopspinnergame();
      break;
    case 4:
      forwardbackward();
      break;
    
    case 11:
      flashTest();
      break;
  }
    
  delay(20);
 
}

int menu() {
  int selected;

  while(digitalRead(BUTTON)) {
    selected = getMenuValue();
    digitalWrite(pinArray[lastpos], LOW);
    digitalWrite(pinArray[selected], HIGH);
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

void clearAllLEDs() {
  int l;
  //clear all LEDs 
  for (l = 0; l < 12; ++l) {
    digitalWrite(pinArray[l], LOW);
  }
}

void spin(int direction = CLOCKWISE) {
  
  if (lastpos != -1) {
      digitalWrite(pinArray[curpos], LOW);
    }
      
  if (direction == CLOCKWISE) {
    lastpos = curpos;
    ++curpos;
      
    if (curpos >= arrayElements) {
      curpos = 0;
    }
  } else {
    lastpos = curpos;
    --curpos;
      
    if (curpos < 0) {
      curpos = arrayElements;
    }
  }
  digitalWrite(pinArray[curpos], HIGH);
}

void flash(int pins[], int repeat = 3, int flashCount = 3) {
  int fc, rc, l;
  
  clearAllLEDs();
  //clear all LEDs before flashing
  
  for (rc = 0; rc < repeat; ++rc) {
    for (fc = 0; fc < flashCount; ++fc) {
      for (l=0; l<4; ++l) {
        digitalWrite(pins[l], HIGH);
      }
      
      delay(delayBetweenFlashes);
      
      for (l=0; l<4; ++l) {
        digitalWrite(pins[l], LOW);
      }
      
      delay(delayBetweenFlashes);
    }
    
    delay(delayBetweenRepeats);
  }
}

void spinner() {
  int currentDirection = CLOCKWISE;
  
  while (1 != 0) {
    int waitTime;
  
    spin(currentDirection);
    
    if (!digitalRead(BUTTON)) {    //time to flip the direction
      if (currentDirection == CLOCKWISE) {
        currentDirection = COUNTERCLOCKWISE;
      } else {
        currentDirection = CLOCKWISE;
      }
      
      flash(extraLED, 2, 2);
      delay(100);
    }
    
    //delay(1000);              // wait for a second
    waitTime = analogRead(0);
  
    if (waitTime < 3) {
      waitTime = 3;
    }
    
    delay(waitTime);
  }
}


void flashTest() {
  flash(greenArray);
  flash(yellowArray);
  flash(redArray);
}

// stop spinner game
// Step one, randomly pick the one they need to stop on and set the width of the match
// start and wait till button push and see if they hit it.
int getBarWidth() {
  int width;
  int l;
  
  delay(200);
  while(digitalRead(BUTTON)) {
    clearAllLEDs();
    
    width = getMenuValue();
    
    for (l=0; l<width; ++l) {
      digitalWrite(pinArray[l], HIGH);
    }
  }
  
  return width;
}

void showHitLight(int hitlight){
  clearAllLEDs();
  delay(500);      //debounce delay
  while (digitalRead(BUTTON)) {
      digitalWrite(pinArray[hitlight], HIGH);
      delay(200);
      digitalWrite(pinArray[hitlight], LOW);
      delay(200);
    }
}

int spinHit(int barWidth) {
  int pinNum;
  int l;
  int baseLED=0;
  
  delay(500);    //debounce delay
  
  while (digitalRead(BUTTON)) {
    clearAllLEDs();
    for (l=0; l<barWidth; ++l) {
      pinNum = l + baseLED;
      
      if (pinNum > 11) {
        pinNum = pinNum - 11;
      }
      
      digitalWrite(pinArray[pinNum], HIGH);
      
    }
    delay(40);

    ++baseLED;
    if (baseLED > 11) {
      baseLED=0;
    }
  }
  
  return baseLED;
}

void nohit(int hitLight, int pinhit) {
  clearAllLEDs();
  digitalWrite(pinArray[pinhit], HIGH);
  delay(500);    //debounce delay
  while(digitalRead(BUTTON)) {
    digitalWrite(pinArray[hitLight], HIGH);
    delay(100);
    digitalWrite(pinArray[hitLight], LOW);
    delay(100);
  }
}

void winnerwinner() {
  delay(500);    //debounce delay
  while(digitalRead(BUTTON)) {
    flash(greenArray,3,1);
  }
}

void stopspinnergame() {
  int barWidth;
  int hitLight;
  int pinhit;
  
  delay(500);
  while (1 != 2) {
    barWidth = getBarWidth();
    hitLight = random(0,11);
    showHitLight(hitLight);
    pinhit = spinHit(barWidth);
    if (pinhit >= hitLight && pinhit <= (hitLight + barWidth)) {
      winnerwinner();
    } else if ((pinhit + hitLight) > 11) {
      Serial.println("oddball");
    } else {
      nohit(hitLight, pinhit);
    }
    
  }
}


// Spin up game
// Speed up the circle while button is pressed then slow down at same rate
// Some concepts to take away is there is no

void spinupgame() {
  while (1 != 2) {
    //monitor the button presses to either speed up or slow down the circling
    if (nextButtonRead < millis()) {
      if (!digitalRead(BUTTON)) {
        //++spinRate;
        spinRate = spinRate + 3;
        if (spinRate > 999) {
          spinRate = 999;
        }
      } else if (spinRate > 0) {
        --spinRate;
      }
      //Serial.println(spinRate);
      nextButtonRead = millis() + buttonReadMillis;
    }
    
    //now handle the spinning if it is time
    if ((nextMoveTime < millis()) && (spinRate > 0)) {
      spin();
      nextMoveTime = millis() + (1000 - spinRate);
    }
  //delay(1);    //wait for at least 1 milisecond so we do not have a runaway CPU
  }
}

void randomgame() {
  int randomCount;
  int l;
  int ledPicked;
  
  randomCount = random(20,50);
  
  while (1 != 2) {
    for (l=0; l< randomCount; ++l) {
      digitalWrite(pinArray[ledPicked], LOW);
      ledPicked = random(0,11);
      digitalWrite(pinArray[ledPicked], HIGH);
      delay(100);
    }
    
    while (digitalRead(BUTTON)) {
      digitalWrite(pinArray[ledPicked], HIGH);
      delay(200);
      digitalWrite(pinArray[ledPicked], LOW);
      delay(200);
    }
    
  }
}

void forwardbackward() {
  int cnt = 0;
  int currentDirection = CLOCKWISE;
  
  delay(500);
  
  while (digitalRead(BUTTON)) {
    ++cnt;
    if (cnt > 11) {
      if (currentDirection == CLOCKWISE) {
        currentDirection = COUNTERCLOCKWISE;
      } else {
        currentDirection = CLOCKWISE;
      }
      
      cnt = 0;
    }
    spin(currentDirection);
    delay(50);
  }
}



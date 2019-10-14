/** 
 *  KEYS: 
 *  I2C address: 0x20 (0)
 *  Mapping of rows and columns to MPC23017 pins:
 *  13 : C1
 *  0  : C2
 *  1  : C3
 *  2  : C4
 *  3  : C5
 *  4  : C6
 *  5  : C7
 *  6  : C8
 *  7  : C9 ( Has only 2 buttons: R1 & R3 )
 *  
 *  9  : R1
 *  10 : R2
 *  12 : R3
 *  
 *  Mapping of MinigmaBus: 
 *  1 : VCC (+3V)
 *  2 : GND
 *  4 : /
 *  5 : SCL
 *  6 : SDA
 *  
 *  SDA & SCL are both connected over a 2.2k Ohmn Resistor to +3V
 *  
 *  
 */
#include <Wire.h>
// Need to update the source file for this library to use wire.begin(0,2) in stead of the default constructor when using ESP8226
#include <Adafruit_MCP23017.h>

bool readColumnOne;
bool readColumnTwo;

Adafruit_MCP23017 mcpKeys;
Adafruit_MCP23017 mcpLights;

// GPIO pins for LED Rows
int LED_NUMBER_OF_ROWS=3;
int ledRowPins[3] = {12, 13, 15};
int LED_NUMBER_OF_COLUMNS=9;
int ledColumnPins[9] = {11, 10, 8, 2, 3, 4, 5, 6, 7};

// GPIO pins for Keys
int KEY_NUMBER_OF_ROWS = 3;
int keyRowPins[3] = {9,10,12};
int KEY_NUMBER_OF_COLUMNS = 9;
int keyColumnPins[9] = {13,0,1,2,3,4,5,6,7};

int rotor1 = 0;
int rotor2 = 0;
int rotor3 = 0;

void setup() {
  Serial.begin(74880);
  
  delay(1000);
  mcpKeys.begin(0);
  delay(1000);
  mcpLights.begin(4);
  delay(1000);
  
  // Setup GPIO pins for keys
  // column pins will be scanned. ()
  for(int i = 0; i < KEY_NUMBER_OF_COLUMNS ; i++ ){
    delay(50);
    mcpKeys.pinMode(keyColumnPins[i], OUTPUT);
    mcpKeys.digitalWrite(keyColumnPins[i], HIGH);
  }  

  // Rows will be read.
  // They should be pulled down.
  for(int i = 0; i < KEY_NUMBER_OF_ROWS ; i++ ){
    delay(50);
    mcpKeys.pinMode(keyRowPins[i], INPUT);
    mcpKeys.pullUp(keyRowPins[i], HIGH);
  }  
  
  // Setup LED GPIOs for output
  // Rows
  for(int i=0; i < KEY_NUMBER_OF_ROWS; i++){
    delay(50);
    mcpLights.pinMode(ledRowPins[i], OUTPUT);
    mcpLights.digitalWrite(ledRowPins[i], LOW);
  }
  // columns
  for(int i=0; i < KEY_NUMBER_OF_COLUMNS; i++){
    delay(50);
    mcpLights.pinMode(ledColumnPins[i], OUTPUT);
    mcpLights.digitalWrite(ledRowPins[i], HIGH);
  }

  // 
  for (int i=0; i<= 26; i++){
    delay(20);
    if (i == 9) continue;
    int column = i % LED_NUMBER_OF_COLUMNS;
    int row = i / LED_NUMBER_OF_COLUMNS;
    mcpLights.digitalWrite(ledRowPins[row], HIGH);
    mcpLights.digitalWrite(ledColumnPins[column], LOW);
    delay(20);
    mcpLights.digitalWrite(ledRowPins[row], LOW);
    mcpLights.digitalWrite(ledColumnPins[column], HIGH);
  }
}

void turnAllLedsOff(){
  // reset all LEDS (All Off)
  // Rows
  for(int i=0; i < LED_NUMBER_OF_ROWS; i++){
    Serial.println("Setting" + String(ledRowPins[i]) + "LOW");
    mcpLights.digitalWrite(ledRowPins[i], LOW);
    delay(50);
  }
  // columns
  for(int i=0; i < LED_NUMBER_OF_COLUMNS; i++){
    Serial.println("Setting" + String(ledColumnPins[i]) + "HIGH");
    mcpLights.digitalWrite(ledColumnPins[i], HIGH);
    delay(50);
  }
}

void turnOnLedXms(int number, int x){
  int column = number % LED_NUMBER_OF_COLUMNS;
  int row = number / LED_NUMBER_OF_COLUMNS;
 
  mcpLights.digitalWrite(ledRowPins[row], HIGH);
  mcpLights.digitalWrite(ledColumnPins[column], LOW);
  delay(x);
  mcpLights.digitalWrite(ledRowPins[row], LOW);
  mcpLights.digitalWrite(ledColumnPins[column], HIGH);
  

}

void loop_(){
  for (int i=0; i<= 26; i++){
    if (i == 9) continue;
    Serial.println("switching on" +  String(i));
    turnOnLedXms(i, 1000);
    delay(1000);
  }
}

char keyToLetter(int keyNumber){
  switch (keyNumber){
    case 0:
      return 'P';
      break;
    case 1:
      return 'A';
      break;
    case 2:
      return 'Q';
      break;
    case 3:
      return 'Y';
      break;
    case 4:
      return 'S';
      break;
    case 5:
      return 'W';
      break;
    case 6:
      return 'X';
      break;
    case 7:
      return 'D';
      break;
    case 8:
      return 'E';
      break;
    case 9:
      return 'C';
      break;
    case 10:
      return 'F';
      break;
    case 11:
      return 'R';
      break;
    case 12:
      return 'V';
      break;
    case 13:
      return 'G';
      break;
    case 14:
      return 'T';
      break;
    case 15:
      return 'B';
      break;
    case 16:
      return 'H';
      break;
    case 17:
      return 'Z';
      break;
    case 18:
      return 'N';
      break;
    case 19:
      return 'J';
      break;
    case 20:
      return 'U';
      break;
    case 21:
      return 'M';
      break;
    case 22:
      return 'K';
      break;
    case 23:
      return 'I';
      break;
    case 24:
      return 'L';
      break;
    case 26:
      return 'O';
      break;
  }
}

int letterToLight(char letter){  
  switch (letter){
    case 'Q':
      return 0;
      break;
    case 'W':
      return 1;
      break;
    case 'E':
      return 2;
      break;
    case 'R':
      return 3;
      break;
    case 'T':
      return 4;
      break;
    case 'Z':
      return 5;
      break;
    case 'U':
      return 6;
      break;
    case 'I':
      return 7;
      break;
    case 'O':
      return 8;
      break;
  
    // Row 2
    case 'A':
      return 10;
      break;
    case 'S':
      return 11;
      break;
    case 'D':
      return 12;
      break;
    case 'F':
      return 13;
      break;
    case 'G':
      return 14;
      break;
    case 'H':
      return 15;
      break;
    case 'J':
      return 16;
      break;
    case 'K':
      return 17;
      break;
    
    // Row 3
    case 'P':
      return 18;
      break;
    case 'Y':
      return 19;
      break;
    case 'X':
      return 20;
      break;
    case 'C':
      return 21;
      break;
    case 'V':
      return 22;
      break;
    case 'B':
      return 23;
      break;
    case 'N':
      return 24;
      break;
    case 'M':
      return 25;
      break;
    case 'L':
      return 26;
      break;
  }
}


void turnOnLedTillKeyIsReleased(int led, int rowPin){
  int column = led % LED_NUMBER_OF_COLUMNS;
  int row = led / LED_NUMBER_OF_COLUMNS;
  
  mcpLights.digitalWrite(ledRowPins[row], HIGH);
  mcpLights.digitalWrite(ledColumnPins[column], LOW);
  
  while(mcpKeys.digitalRead(rowPin)){
    delay(20);
  }

  mcpLights.digitalWrite(ledRowPins[row], LOW);
  mcpLights.digitalWrite(ledColumnPins[column], HIGH);
}

int translate( ){
  
}

void loop() {
  // Rows
  int keyRead = -1;
  for (int r = 0; r < KEY_NUMBER_OF_COLUMNS; r++){
    // Scan 1 column
    // Serial.println("Set ROW " + String(r) + " HIGH");
    mcpKeys.digitalWrite(keyColumnPins[r], LOW);
    for(int c = 0; c < KEY_NUMBER_OF_ROWS; c++){
      //delay(100);
      bool cRead = mcpKeys.digitalRead(keyRowPins[c] );
      // Serial.println("Read COLUMNS " + String(c) + ": " + String(cRead));
      if (!cRead){
        keyRead = (r * KEY_NUMBER_OF_ROWS) + c ;
        char charRead = keyToLetter(keyRead);
        int ledToLight = letterToLight(charRead);
        Serial.println("Read:  number " + String(charRead));
        //turnOnLedTillKeyIsReleased(keyRead, keyRowPins[c]);
        turnOnLedXms(ledToLight, 1000);
      }
    }
    // Serial.println("Set ROW " + String(r) + " LOW");
    mcpKeys.digitalWrite(keyColumnPins[r], HIGH);
  }
}

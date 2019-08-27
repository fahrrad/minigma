
#include <Wire.h>
#include <Adafruit_MCP23017.h>

bool readColumnOne;
bool readColumnTwo;

Adafruit_MCP23017 mcp;

// GPIO pins for LED Rows
int LED_NUMBER_OF_ROWS=3;
int ledRowPins[3] = {5, 3, 2};
int LED_NUMBER_OF_COLUMNS=2;
int ledColumnPins[2] = {4, 1};

// GPIO pins for Keys
int KEY_NUMBER_OF_ROWS = 3;
int keyRowPins[3] = {0,3,5};
int KEY_NUMBER_OF_COLUMNS = 2;
int keyColumnPins[2] = {1,2};


void setup() {
  Serial.begin(9600);
  mcp.begin();
  // Setup GPIO pins for keys
  // these 2 pins will be read. (columns)
  // They should be pulled down.
  for(int i = 0; i < KEY_NUMBER_OF_COLUMNS ; i++ ){
    mcp.pinMode(keyColumnPins[i], INPUT);
  }  

  // Rows will be scanned.
  for(int i = 0; i < KEY_NUMBER_OF_ROWS ; i++ ){
    mcp.pinMode(keyRowPins[i], OUTPUT);
  }  
  
  // Setup LED GPIOs for output
  // Rows
  for(int i=0; i < 3; i++){
    mcp.pinMode(ledRowPins[i], OUTPUT);
  }
  // columns
  for(int i=0; i < 2; i++){
    mcp.pinMode(ledColumnPins[i], OUTPUT);
  }
}

void turnAllLedsOff(){
  // reset all LEDS (All Off)
  // Rows
  for(int i=0; i < LED_NUMBER_OF_ROWS; i++){
    Serial.println("Setting" + String(ledRowPins[i]) + "LOW");
    mcp.digitalWrite(ledRowPins[i], LOW);
  }
  // columns
  for(int i=0; i < LED_NUMBER_OF_COLUMNS; i++){
    Serial.println("Setting" + String(ledColumnPins[i]) + "HIGH");
    mcp.digitalWrite(ledColumnPins[i], HIGH);
  }
}

void turnOnLed1000ms(int number){
  int column = number % LED_NUMBER_OF_COLUMNS;
  int row = number / LED_NUMBER_OF_COLUMNS;
 
  mcp.digitalWrite(ledRowPins[row], HIGH);
  mcp.digitalWrite(ledColumnPins[column], LOW);
  delay(1000);
  mcp.digitalWrite(ledRowPins[row], LOW);
  mcp.digitalWrite(ledColumnPins[column], HIGH);
  

}

void loop(){
  for (int i =0; i< 6; i++){
    Serial.println("switching on" +  String(i));
    turnOnLed1000ms(i);
    delay(1000);
  }
}

void loop_() {
  // Rows
  int keyRead = -1;
  for (int r = 0; r < KEY_NUMBER_OF_ROWS; r++){
    // Scan 1 Row
    // Serial.println("Set ROW " + String(r) + " HIGH");
    mcp.digitalWrite(keyRowPins[r], HIGH);
    for(int c = 0; c < KEY_NUMBER_OF_COLUMNS; c++){
      //delay(100);
      bool cRead = mcp.digitalRead(keyColumnPins[c] );
      // Serial.println("Read COLUMNS " + String(c) + ": " + String(cRead));
      if (cRead){
        keyRead = (r * KEY_NUMBER_OF_COLUMNS) + c ;
        //delay(100);
        //Serial.println("%%%%%%%%%%%%%%%%%%%  " + String(keyRead));
        turnOnLed1000ms(keyRead);
      }
    }
    // Serial.println("Set ROW " + String(r) + " LOW");
    mcp.digitalWrite(keyRowPins[r], LOW);
  }
}

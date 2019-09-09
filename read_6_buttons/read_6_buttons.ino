
#include <Wire.h>
#include <Adafruit_MCP23017.h>

bool readColumnOne;
bool readColumnTwo;

Adafruit_MCP23017 mcp;

// GPIO pins for LED Rows
int LED_NUMBER_OF_ROWS=3;
int ledRowPins[3] = {15,15, 15};
int LED_NUMBER_OF_COLUMNS=2;
int ledColumnPins[2] = {15,15};

// GPIO pins for Keys
int KEY_NUMBER_OF_ROWS = 3;
int keyRowPins[3] = {9,10,12};
int KEY_NUMBER_OF_COLUMNS = 9;
int keyColumnPins[9] = {13,0,1,2,3,4,5,6,7};


void setup() {
  Serial.begin(74880);
  mcp.begin();
  
  // Setup GPIO pins for keys
  // column pins will be scanned. ()
  for(int i = 0; i < KEY_NUMBER_OF_COLUMNS ; i++ ){
    mcp.pinMode(keyColumnPins[i], OUTPUT);
    mcp.digitalWrite(keyColumnPins[i], HIGH);
  }  

  // Rows will be read.
  // They should be pulled down.
  for(int i = 0; i < KEY_NUMBER_OF_ROWS ; i++ ){
    mcp.pinMode(keyRowPins[i], INPUT);
    mcp.pullUp(keyRowPins[i], HIGH);
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

void loop__(){
  for (int i =0; i< 6; i++){
    Serial.println("switching on" +  String(i));
    turnOnLed1000ms(i);
    delay(1000);
  }
}

void loop() {
  // Rows
  int keyRead = -1;
  for (int r = 0; r < KEY_NUMBER_OF_COLUMNS; r++){
    // Scan 1 column
    // Serial.println("Set ROW " + String(r) + " HIGH");
    mcp.digitalWrite(keyColumnPins[r], LOW);
    for(int c = 0; c < KEY_NUMBER_OF_ROWS; c++){
      //delay(100);
      bool cRead = mcp.digitalRead(keyRowPins[c] );
      // Serial.println("Read COLUMNS " + String(c) + ": " + String(cRead));
      if (!cRead){
        keyRead = (r * KEY_NUMBER_OF_ROWS) + c ;
        
        Serial.println("%%%%%%%%%%%%%%%%%%%  " + String(keyRead));
        delay(100);
        //turnOnLed1000ms(keyRead);
      }
    }
    // Serial.println("Set ROW " + String(r) + " LOW");
    mcp.digitalWrite(keyColumnPins[r], HIGH);
  }
}

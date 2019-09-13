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
#include <Adafruit_MCP23017.h>

bool readColumnOne;
bool readColumnTwo;

Adafruit_MCP23017 mcpKeys;

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
  mcpKeys.begin(0);
  
  // Setup GPIO pins for keys
  // column pins will be scanned. ()
  for(int i = 0; i < KEY_NUMBER_OF_COLUMNS ; i++ ){
    mcpKeys.pinMode(keyColumnPins[i], OUTPUT);
    mcpKeys.digitalWrite(keyColumnPins[i], HIGH);
  }  

  // Rows will be read.
  // They should be pulled down.
  for(int i = 0; i < KEY_NUMBER_OF_ROWS ; i++ ){
    mcpKeys.pinMode(keyRowPins[i], INPUT);
    mcpKeys.pullUp(keyRowPins[i], HIGH);
  }  
  
  // Setup LED GPIOs for output
  // Rows
  for(int i=0; i < 3; i++){
    mcpKeys.pinMode(ledRowPins[i], OUTPUT);
  }
  // columns
  for(int i=0; i < 2; i++){
    mcpKeys.pinMode(ledColumnPins[i], OUTPUT);
  }
}

void turnAllLedsOff(){
  // reset all LEDS (All Off)
  // Rows
  for(int i=0; i < LED_NUMBER_OF_ROWS; i++){
    Serial.println("Setting" + String(ledRowPins[i]) + "LOW");
    mcpKeys.digitalWrite(ledRowPins[i], LOW);
  }
  // columns
  for(int i=0; i < LED_NUMBER_OF_COLUMNS; i++){
    Serial.println("Setting" + String(ledColumnPins[i]) + "HIGH");
    mcpKeys.digitalWrite(ledColumnPins[i], HIGH);
  }
}

void turnOnLed1000ms(int number){
  int column = number % LED_NUMBER_OF_COLUMNS;
  int row = number / LED_NUMBER_OF_COLUMNS;
 
  mcpKeys.digitalWrite(ledRowPins[row], HIGH);
  mcpKeys.digitalWrite(ledColumnPins[column], LOW);
  delay(1000);
  mcpKeys.digitalWrite(ledRowPins[row], LOW);
  mcpKeys.digitalWrite(ledColumnPins[column], HIGH);
  

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
    mcpKeys.digitalWrite(keyColumnPins[r], LOW);
    for(int c = 0; c < KEY_NUMBER_OF_ROWS; c++){
      //delay(100);
      bool cRead = mcpKeys.digitalRead(keyRowPins[c] );
      // Serial.println("Read COLUMNS " + String(c) + ": " + String(cRead));
      if (!cRead){
        keyRead = (r * KEY_NUMBER_OF_ROWS) + c ;
        
        Serial.println("%%%%%%%%%%%%%%%%%%%  " + String(keyRead));
        delay(100);
        //turnOnLed1000ms(keyRead);
      }
    }
    // Serial.println("Set ROW " + String(r) + " LOW");
    mcpKeys.digitalWrite(keyColumnPins[r], HIGH);
  }
}

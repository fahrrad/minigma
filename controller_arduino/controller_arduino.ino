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
  mcpKeys.begin(0);
  mcpLights.begin(4);
  
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
  for(int i=0; i < KEY_NUMBER_OF_ROWS; i++){
    mcpLights.pinMode(ledRowPins[i], OUTPUT);
    mcpLights.digitalWrite(ledRowPins[i], LOW);
  }
  // columns
  for(int i=0; i < KEY_NUMBER_OF_COLUMNS; i++){
    mcpLights.pinMode(ledColumnPins[i], OUTPUT);
    mcpLights.digitalWrite(ledRowPins[i], HIGH);
  }
}

void turnAllLedsOff(){
  // reset all LEDS (All Off)
  // Rows
  for(int i=0; i < LED_NUMBER_OF_ROWS; i++){
    Serial.println("Setting" + String(ledRowPins[i]) + "LOW");
    mcpLights.digitalWrite(ledRowPins[i], LOW);
  }
  // columns
  for(int i=0; i < LED_NUMBER_OF_COLUMNS; i++){
    Serial.println("Setting" + String(ledColumnPins[i]) + "HIGH");
    mcpLights.digitalWrite(ledColumnPins[i], HIGH);
  }
}

void turnOnLed1000ms(int number){
  int column = number % LED_NUMBER_OF_COLUMNS;
  int row = number / LED_NUMBER_OF_COLUMNS;
 
  mcpLights.digitalWrite(ledRowPins[row], HIGH);
  mcpLights.digitalWrite(ledColumnPins[column], LOW);
  delay(100);
  mcpLights.digitalWrite(ledRowPins[row], LOW);
  mcpLights.digitalWrite(ledColumnPins[column], HIGH);
  

}

void loop_(){
  for (int i =0; i< 26; i++){
    Serial.println("switching on" +  String(i));
    turnOnLed1000ms(i);
    delay(1000);
  }
}

int keyToLetter(int keyNumber){
  switch (keyNumber){
    case 1:
      return 'A';
      break;
  }
  // Row 1
  // Q => 2
  // W => 5
  // E => 8
  // R => 11
  // T => 14
  // Z => 17
  // U => 20
  // I => 23
  // O => 26

  // Row 2
  // A => 1
  // S => 4
  // D => 7
  // F => 10
  // G => 13
  // H => 16
  // J => 19
  // K => 22

  // Row 3
  // P => 0
  // Y => Y
  // X => 6
  // C => C
  // V => 12
  // B => 15
  // N => 18
  // M => 21
  // L => 24
}

int letterToLight(){
  // Q => 0
  // W => 1
  // E => 2
  // R => 
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
        
        Serial.println("%%%%%%%%%%%%%%%%%%%  " + String(keyRead));
        //delay(100);
        turnOnLed1000ms(keyRead);
      }
    }
    // Serial.println("Set ROW " + String(r) + " LOW");
    mcpKeys.digitalWrite(keyColumnPins[r], HIGH);
  }
}

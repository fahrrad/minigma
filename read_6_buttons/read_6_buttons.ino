#include <Wire.h>
#include <Adafruit_MCP23017.h>

const int16_t I2C_SLAVE = 0x20;

bool readColumnOne;
bool readColumnTwo;

// GPIO pins for LED Rows
int LED_NUMBER_OF_ROWS=3;
//int ledRowPins[3] = {D0, D2, D3};
int ledRowPins[3] = {3,4,5};
int LED_NUMBER_OF_COLUMNS=2;
//int ledColumnPins[2] = {D1, D4};
int ledColumnPins[2] = {1,2};

// GPIO pins for Keys
int KEY_NUMBER_OF_ROWS = 3;
// int keyRowPins[3] = {D5, D8, 9};
 int keyRowPins[3] = {6, 7, 8};
int KEY_NUMBER_OF_COLUMNS = 2;
// int keyColumnPins[2] = {D6, D7};
 int keyColumnPins[2] = {8, 9};

Adafruit_MCP23017 mcp;

void setup() {
  Serial.begin(9600);
  mcp.begin(I2C_SLAVE); 
  mcp.pinMode(7, OUTPUT); 
  mcp.pinMode(7, OUTPUT); 
  mcp.digitalWrite(6, LOW);
  
  // Setup GPIO pins for keys
  // these 2 pins will be read. (columns)
  // They should be pulled down.
//  for(int i = 0; i < LED_NUMBER_OF_COLUMNS ; i++ ){
//    pinMode(keyColumnPins[i], INPUT);
//  }  
//
//  // Rows will be scanned.
//  for(int i = 0; i < KEY_NUMBER_OF_ROWS ; i++ ){
//    pinMode(keyRowPins[i], OUTPUT);
//  }  
//  
//  // Setup LED GPIOs for output
//  // Rows
//  for(int i=0; i < 3; i++){
//    pinMode(ledRowPins[i], OUTPUT);
//  }
//  // columns
//  for(int i=0; i < 2; i++){
//    pinMode(ledColumnPins[i], OUTPUT);
//  }
}

void turnAllLedsOff(){
  // reset all LEDS (All Off)
  // Rows
  for(int i=0; i < LED_NUMBER_OF_ROWS; i++){
    Serial.println("Setting" + String(ledRowPins[i]) + "LOW");
    digitalWrite(ledRowPins[i], LOW);
  }
  // columns
  for(int i=0; i < LED_NUMBER_OF_COLUMNS; i++){
    Serial.println("Setting" + String(ledColumnPins[i]) + "HIGH");
    digitalWrite(ledColumnPins[i], HIGH);
  }
}

void turnOnLed100ms(int number){
  int column = number % LED_NUMBER_OF_COLUMNS;
  int row = number / LED_NUMBER_OF_COLUMNS;
 
  digitalWrite(ledRowPins[row], HIGH);
  digitalWrite(ledColumnPins[column], LOW);
  delay(100);
  digitalWrite(ledRowPins[row], LOW);
  digitalWrite(ledColumnPins[column], HIGH);
  

}

void loop_(){
  for (int i =0; i< 6; i++){
    //Serial.println("switching on" +  String(i));
    turnOnLed100ms(i);
    delay(1000);
  }
}

void loop__() {
  // Rows
  int keyRead = -1;
  for (int r = 0; r < KEY_NUMBER_OF_ROWS; r++){
    // Scan 1 Row
    //Serial.println("Set ROW " + String(keyRowPins[r]) + " HIGH");
    digitalWrite(keyRowPins[r], HIGH);
    for(int c = 0; c < KEY_NUMBER_OF_COLUMNS; c++){
      bool cRead = digitalRead(keyColumnPins[c] );
      // Serial.println("Read COLUMNS " + String(keyColumnPins[c]) + ": " + String(cRead));
      if (cRead){
        keyRead = (r * KEY_NUMBER_OF_ROWS) + c;
        Serial.println("Read key " + String(keyRead));
      }
    }
    // Serial.println("Set ROW " + String(keyRowPins[r]) + " LOW");
    digitalWrite(keyRowPins[r], LOW);
  }

  if (keyRead != -1 ) 
  {
    turnOnLed100ms(keyRead);  
    keyRead = -1; 
  }
}

void loop(){
  Serial.println("Setting 7 HIGH");
  mcp.digitalWrite(7, HIGH);
  delay(300);
//  
  mcp.digitalWrite(7, LOW);
  delay(300);
}

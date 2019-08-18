bool readColumnOne;
bool readColumnTwo;

// GPIO pins for LED Rows
int LED_NUMBER_OF_ROWS=3;
int ledRowPins[3] = {D0, D2, D3};
int LED_NUMBER_OF_COLUMNS=2;
int ledColumnPins[2] = {D1, D4};

// GPIO pins for Keys
int KEY_NUMBER_OF_ROWS = 3;
int keyRowPins[3] = {D5, D8, 10};
int KEY_NUMBER_OF_COLUMNS = 2;
int keyColumnPins[2] = {D6, D7};


void setup() {
  Serial.begin(9600);
  // Setup GPIO pins for keys
  // these 2 pins will be read. (columns)
  // They should be pulled down.
  for(int i = 0; i < LED_NUMBER_OF_COLUMNS ; i++ ){
    pinMode(keyColumnPins[i], INPUT);
  }  

  // Rows will be scanned.
  for(int i = 0; i < KEY_NUMBER_OF_ROWS ; i++ ){
    pinMode(keyRowPins[i], OUTPUT);
  }  
  
  // Setup LED GPIOs for output
  // Rows
  for(int i=0; i < 3; i++){
    pinMode(ledRowPins[i], OUTPUT);
  }
  // columns
  for(int i=0; i < 2; i++){
    pinMode(ledColumnPins[i], OUTPUT);
  }
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

void loop() {
  // Rows
  int keyRead = -1;
  for (int r = 0; r < KEY_NUMBER_OF_ROWS; r++){
    // Scan 1 Row
    Serial.println("Set ROW " + String(keyRowPins[r]) + " HIGH");
    digitalWrite(keyRowPins[r], HIGH);
    for(int c = 0; c < KEY_NUMBER_OF_COLUMNS; c++){
      delay(100);
      bool cRead = digitalRead(keyColumnPins[c] );
      Serial.println("Read COLUMNS " + String(keyColumnPins[c]) + ": " + String(cRead));
      if (cRead){
        keyRead = ((r+1) * KEY_NUMBER_OF_ROWS) + c;
        delay(100);
        Serial.println("Read key " + String(keyRead));
      }
    }
    Serial.println("Set ROW " + String(keyRowPins[r]) + " LOW");
    digitalWrite(keyRowPins[r], LOW);

    delay(1000);
  }

  if (keyRead != -1 ) 
  {
    turnOnLed100ms(keyRead);  
    keyRead = -1; 
  }
  
//  digitalWrite(8, HIGH);
//  digitalWrite(9, LOW);
//  digitalWrite(10, LOW);
//
//  readColumnOne = digitalRead(2);
//  readColumnTwo = digitalRead(3);
//
//  if (readColumnOne) turnOnLed100ms(0); 
//  if (readColumnTwo) turnOnLed100ms(1);
//
//  // Row 2
//  digitalWrite(8, LOW);
//  digitalWrite(9, HIGH);
//  digitalWrite(10, LOW);
//
//  readColumnOne = digitalRead(2);
//  readColumnTwo = digitalRead(3);
//
//  if (readColumnOne) turnOnLed100ms(2);
//  if (readColumnTwo) turnOnLed100ms(3);
//
//  // Row 3
//  digitalWrite(8, LOW);
//  digitalWrite(9, LOW);
//  digitalWrite(10, HIGH);
//
//  readColumnOne = digitalRead(2);
//  readColumnTwo = digitalRead(3);
//
//  if (readColumnOne) turnOnLed100ms(4);
//  if (readColumnTwo) turnOnLed100ms(5);
}

bool readColumnOne;
bool readColumnTwo;

// GPIO pins for LED Rows
int LED_NUMBER_OF_ROWS=3;
int ledRowPins[3] = {D0, D3, D5};
int LED_NUMBER_OF_COLUMNS=2;
int ledColumnPins[2] = {D1, D4};

void setup() {
  Serial.begin(9600);
  // Setup GPIO pins for keys
  // these 2 pins will be read. 
  // They should be pulled down.
//  pinMode(, INPUT);
//  pinMode(, INPUT);
//  
//  pinMode(, OUTPUT);
//  pinMode(, OUTPUT);
//  pinMode(, OUTPUT);

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

void turnOnLed1Sec(int number){
  int column = number % LED_NUMBER_OF_COLUMNS;
  int row = number / LED_NUMBER_OF_COLUMNS;
 
  digitalWrite(ledRowPins[row], HIGH);
  digitalWrite(ledColumnPins[column], LOW);
  delay(100);
  digitalWrite(ledRowPins[row], LOW);
  digitalWrite(ledColumnPins[column], HIGH);
  

}

void loop(){
  for (int i =0; i< 6; i++){
    Serial.println("switching on" +  String(i));
    turnOnLed1Sec(i);
    delay(1000);
  }
}

void loop_() {
  // Row 1
  digitalWrite(8, HIGH);
  digitalWrite(9, LOW);
  digitalWrite(10, LOW);

  readColumnOne = digitalRead(2);
  readColumnTwo = digitalRead(3);

  if (readColumnOne) turnOnLed1Sec(0); 
  if (readColumnTwo) turnOnLed1Sec(1);

  // Row 2
  digitalWrite(8, LOW);
  digitalWrite(9, HIGH);
  digitalWrite(10, LOW);

  readColumnOne = digitalRead(2);
  readColumnTwo = digitalRead(3);

  if (readColumnOne) turnOnLed1Sec(2);
  if (readColumnTwo) turnOnLed1Sec(3);

  // Row 3
  digitalWrite(8, LOW);
  digitalWrite(9, LOW);
  digitalWrite(10, HIGH);

  readColumnOne = digitalRead(2);
  readColumnTwo = digitalRead(3);

  if (readColumnOne) turnOnLed1Sec(4);
  if (readColumnTwo) turnOnLed1Sec(5);
}

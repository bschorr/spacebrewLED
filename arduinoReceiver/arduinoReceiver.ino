int incomingByte;  //a variable to read incoming serial data
int recordedRange; //a variable to record the last range received
boolean bIsOn; //to know if the LEDs are on or off

int noButtonState;
int yesButtonState;

boolean bWillWait;
boolean firstRead = false;

void setup() {
  
  //initiate serial communication:
  Serial.begin(9600);
  //Serial.println(F("starting up"));

  //set the digital pins to which the LEDs are connected to OUTPUT
  for (int i = 2; i <= 11; i++) {
    pinMode (i, OUTPUT);
    digitalWrite(i, LOW);
  }
  
  pinMode (12, INPUT);
  pinMode (13, INPUT);

  //start with the LEDs on
  bIsOn = true;

}  

void loop() {

  // read serial messages
  if (Serial.available() > 0) {

    incomingByte = Serial.read();
    
    //test if the values received are the on/off boolean or the ranges
    if (incomingByte >= 2) { 
      recordedRange = incomingByte;
    } 
    else {
      bIsOn = incomingByte; 
    }

    //if LEDs are off, set all of them to LOW
    if (!bIsOn) {
      for (int i = 13; i >= 2; i--) {
        digitalWrite (i, LOW);
      }
    } 
    
    //if LEDs are on, set all of them to LOW
    else {
      for (int i = 13; i >= 2; i--) {
        if (i < recordedRange) { 
          digitalWrite (i, HIGH);
        } else {
          digitalWrite(i, LOW); 
        }
      }
    }    

    //read all the bytes in the serial buffer
    while (Serial.available()) incomingByte = Serial.read();
  }
  
  noButtonState = digitalRead(12);
  yesButtonState = digitalRead(13);

  if (noButtonState == HIGH) {
    bWillWait = false;
    firstRead = true;
  }
  
  if (yesButtonState == HIGH) {
    bWillWait = true;
    firstRead = true;
  }
  
  if (firstRead) Serial.println(bWillWait);
  
}




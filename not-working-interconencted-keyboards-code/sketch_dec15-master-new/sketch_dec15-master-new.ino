int state = 0;
void setup() {
  pinMode(13, OUTPUT);
  digitalWrite(13, LOW);
  Serial.begin(9600);
  Serial1.begin(9600); // Default communication rate of the Bluetooth module
  Serial2.begin(38400);
}

//void checkForLayoutChanged(stateVoid) {
//  
//}


void loop() {
 if(Serial1.available() > 0){ // Checks whether data is comming from the serial port
    state = Serial1.read(); // Reads the data from the serial port
  
//   int x = (state >> (8*7)) & 0xff;
 
//   if (x != 0 ){
//    digitalWrite(13, HIGH);
//    Serial2.write(state);
//    delay(100);
//  }
  
  
  Serial.write(state);
  digitalWrite(13, HIGH);
  delay(10);
 } else {
  
  digitalWrite(13, LOW);
 }
 
 if(Serial2.available() > 0){ // Checks whether data is comming from the serial port
    state = Serial2.read(); // Reads the data from the serial port
 
//    int x = (state >> (8*7)) & 0xff;
// 
//   if (x != 0 ){
//    digitalWrite(13, HIGH);
//    Serial1.write(state);
//    delay(100);
//  }
  
  Serial.write(state);
  digitalWrite(13, HIGH);
 delay(10);
 } else {
  
  digitalWrite(13, LOW);
 }
 delay(10);
}

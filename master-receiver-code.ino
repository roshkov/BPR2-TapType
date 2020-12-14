int state = 0;
void setup() {
  pinMode(13, OUTPUT);
  digitalWrite(13, LOW);
  Serial.begin(9600);
  Serial1.begin(9600); // Default communication rate of the Bluetooth module
}
void loop() {
 if(Serial1.available() > 0){ // Checks whether data is comming from the serial port
    state = Serial1.read(); // Reads the data from the serial port
  Serial.write(state);
  digitalWrite(13, HIGH);
 delay(10);
 } else {
  
  digitalWrite(13, LOW);
 }
 delay(10);
}
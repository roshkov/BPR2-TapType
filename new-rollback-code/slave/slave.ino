uint8_t buf[8] = { 0 }; //Keyboard report buffer


// default layout number [starts from 0]
int pageSetup = 0;

// Maximum amount of layouts
const int maxLayouts = 3;

//Maximum amount of buttons on keyboard
const int maxButtons = 12;

bool shiftOn = false;



//IMPORTANT KEYS TO USE:
//0x4f - right arrow
//0x50 - left arrow
//0xe0 - left control (for buf[0])

// special character example
//     buf[0] = 0x02;  (shift - uppercase: 0x02)
//     buf[2] = 0x1e;



// array stores all possible codes for characters and key-combinations
// {
//  [s , 1 , !]
//  [h , 2 , @ ]
//  [a , 3 , # ]
//  etc.  
// }
// s h a r k o w l i n g t e p c
//
// IMPORTANT: for this particular case: if you choose layout #3, then it is the same as layout 2, butshould add buf[0] = 0x02
char keyChars[maxButtons][maxLayouts] = 
        { 
          {0x16  , 0x1e , 0x1e}, 
          {0x0b  , 0x1f , 0x1f}, 
          {0x04  , 0x20 , 0x20}, 
          {0x15  , 0x21 , 0x21}, 
          {0x0e  , 0x22 , 0x22}, 
          {0x12  , 0x23 , 0x23}, 
          {0x1a  , 0x24 , 0x24},
          {0x50  , 0x50 , 0x50},     
          {0x4f  , 0x4f , 0x4f}, 
          {0x0f  , 0x27 , 0x27},       
        };

void setup() {
  // put your setup code here, to run once:
 Serial1.begin(9600); // Default communication rate of the Bluetooth module  

  pinMode(2, INPUT);
  pinMode(3, INPUT);
  pinMode(4, INPUT);
  pinMode(5, INPUT);
  pinMode(6, INPUT);
  pinMode(7, INPUT);
  pinMode(8, INPUT);
  pinMode(9, INPUT);
  pinMode(10, INPUT);
  pinMode(11, INPUT);
  pinMode(12, INPUT);
  pinMode(A1, INPUT);
  pinMode(A2, INPUT);
  pinMode(A3, INPUT);
  pinMode(A4, INPUT);
  pinMode(A5, INPUT);
  pinMode(13, OUTPUT);
  
}


//Switching layout #
void switchLayoutNumber () {
  pageSetup++;  
  if (pageSetup == maxLayouts) {
    pageSetup = 0;
  }
  
}


// Adds the pressed shift.  works for special characters as !?^, and to make uppercase
void checkForPunctuationLayout () {
    if (pageSetup == 2 ) {
       buf[0] = 0x02;
    }
}


// Action that happens every time a button(any) is pressed
// parameter btnNum defines which row it takes from keyChars array
void pressButtonAction (int btnNum) {
    digitalWrite(13, HIGH);
    checkForPunctuationLayout();
    buf[2] = keyChars[btnNum][pageSetup];  
    Serial1.write(buf, 8); // Send keypress  
    releaseKey();
}

void controlAction(int num) {
  //0 - copy
  //1 - paste

  //assign controll
//  buf[0] = 0xe0 ;
   buf[0] = 0x01;

  if (num == 0 ) {
    buf[2] = 0x06 ;
  }
  else if (num == 1 ) {
    buf[2] = 0x19 ;
  }
  
  Serial1.write(buf, 8); // Send keypress  
  releaseKey();
}

void pressShift() {
  shiftOn = !shiftOn;
}


void loop() {


//switch the layout 

if (digitalRead(4) == HIGH) {
    digitalWrite(13, HIGH);
    switchLayoutNumber();
    releaseKey();
}


else if (digitalRead(2) == HIGH) {
    digitalWrite(13, HIGH);
      checkForPunctuationLayout();
      
      if (pageSetup == 2 ) {
        buf[0] = 0x02;
      }
      buf[2] = keyChars[0][pageSetup];  

    
    Serial1.write(buf, 8); 
    releaseKey();
}
else if (digitalRead(3) == HIGH) {
    pressButtonAction(1);
    
}else if (digitalRead(5) == HIGH) {
    pressButtonAction(2);
    
}else if (digitalRead(6) == HIGH) {
   pressButtonAction(3);
    
}else if (digitalRead(7) == HIGH) {
     pressButtonAction(4);
}
else if (digitalRead(8) == HIGH) {
   pressButtonAction(5);
}
else if (digitalRead(9) == HIGH) {
   pressButtonAction(6);    
}
else if (digitalRead(10) == HIGH) {
   pressButtonAction(7);
}
else if (digitalRead(11) == HIGH) {
   pressButtonAction(8);
}

//ctrl c
else if (digitalRead(12) == HIGH) {
     controlAction(0);
}
//ctrl v
else if(analogRead(A1) > 512) {
     controlAction(1);
}

//Press Shift
else if(analogRead(A2) > 512) {
    digitalWrite(13, HIGH);
    pressShift(); 
    releaseKey();
}

//Backspace
else if(analogRead(A3) > 512) {
    digitalWrite(13, HIGH);
    buf[2] = 0x2a;
    Serial1.write(buf, 8); // Send keypress  
    releaseKey();
}

// Space
else if(analogRead(A4) > 512) {
    digitalWrite(13, HIGH);
    buf[2] = 0x2c;  
    Serial1.write(buf, 8); // Send keypress  
    releaseKey();
}

//Enter
else if(analogRead(A5) > 512) {
    digitalWrite(13, HIGH);
    buf[0] = 0x02;
    Serial1.write(buf, 8); // Send keypress  
    releaseKey();
    
}
else 
{
    digitalWrite(13, LOW);
}


}

void releaseKey() {
  if (shiftOn) {
    buf[0] = 0x02; 
  }
  else {
     buf[0] = 0;
  }
  buf[2] = 0;
  Serial1.write(buf, 8); // Send Release key
  delay(250);
}

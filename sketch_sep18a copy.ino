#include <Servo.h>

const int leftIrLedPin = 10;
const int midIrLedPin = 6;
const int rightIrLedPin = 2;
const int leftIrReceiverPin = 11;
const int midIrReceiverPin = 7;
const int rightIrReceiverPin = 3; 
const int leftRedLedPin = A2;    
const int rightRedLedPin = A0;   
const int midRedLedPin = A1;
int checkSpinIndex = 0;
const int irSensorPin = A1;
const int THRESHOLD = 300; 
int checkRedLineCount = 0;
int countFinal = 0;
int ending = 0;
bool checkalreadyturn = false;

Servo servoLeft;
Servo servoRight;

void setup() {
  servoLeft.attach(13);
  servoRight.attach(12);
  pinMode(leftIrReceiverPin, INPUT);      
  pinMode(leftIrLedPin, OUTPUT);  
  pinMode(leftRedLedPin, OUTPUT);        
  pinMode(midIrReceiverPin, INPUT);
  pinMode(midIrLedPin, OUTPUT);    
  pinMode(midRedLedPin, OUTPUT);    
  pinMode(rightIrReceiverPin, INPUT);   
  pinMode(rightIrLedPin, OUTPUT);         
  pinMode(rightRedLedPin, OUTPUT);

  Serial.begin(9600);
  
  delay(1000);
}
int flag1 = 1;//上一次左边有墙
int flag2 = 1;//上一次右边有墙


void loop() {
  int leftIrVal = irDetect(leftIrLedPin, leftIrReceiverPin, 39700);
  int midIrVal = irDetect(midIrLedPin, midIrReceiverPin, 40000); 
  int rightIrVal = irDetect(rightIrLedPin, rightIrReceiverPin, 39700); 


  controlLeds(leftIrVal, midIrVal, rightIrVal);
  if (ending == 6){
    unsigned long startTime = millis();
    while (millis() - startTime < 2300){
      leftIrVal = irDetect(leftIrLedPin, leftIrReceiverPin, 39700);
      midIrVal = irDetect(midIrLedPin, midIrReceiverPin, 40000); 
      rightIrVal = irDetect(rightIrLedPin, rightIrReceiverPin, 39700); 

      controlLeds(leftIrVal, midIrVal, rightIrVal);
      if (leftIrVal == 0 && rightIrVal == 1) {
        slightTurnRight();
      } 
      else if (rightIrVal == 0 && leftIrVal == 1) {
        slightTurnLeft();
      } 
      else if (midIrVal == 0) {
        moveForward2();
      } 
      else {
        moveForward2();
      }
    }
    stop();
  }
  if (rightIrVal == 0 && leftIrVal == 0 && midIrVal == 0){
    checkSpinIndex++;
    if(checkSpinIndex == 1){
      moveBack2();
      Serial.println("Now spin it lets go!!!");
      spin720();
      checkRedLineCount++;
    }
  }

  if(rightIrVal == 1 && leftIrVal == 1 && midIrVal == 0){
    if(flag1 == 1){
      turnRight();
      flag1 = 0;
    }else{
      turnLeft();
      flag2 = 0;
    }

  }

  
  else if (midIrVal == 0 && (leftIrVal == 0 || rightIrVal == 0)) {
    if (leftIrVal == 0) {
      Serial.println("Front and left wall detected, turning right 90 degrees");
      turnRight();
    } else {
      Serial.println("Front and right wall detected, turning left 90 degrees");
      turnLeft();
    }
  } 
  else if (leftIrVal == 0 && rightIrVal == 1) {
    Serial.println("Left wall detected, slight right adjustment");
    slightTurnRight();
  } 
  else if (rightIrVal == 0 && leftIrVal == 1) {
    Serial.println("Right wall detected, slight left adjustment");
    slightTurnLeft();
  } 
  else if (rightIrVal == 0 && leftIrVal == 0 && midIrVal ==0){
    Serial.println("Now stop!!!!");
    exit(0);
  }
  else {
    moveForward();
  }

  
}

void controlLeds(int leftIrVal, int midIrVal, int rightIrVal) {
  if (leftIrVal == 0) {
    digitalWrite(leftRedLedPin, HIGH);
  } else {
    digitalWrite(leftRedLedPin, LOW);
  }

  if (midIrVal == 0) {
    digitalWrite(midRedLedPin, HIGH);
  } else {
    digitalWrite(midRedLedPin, LOW);
  }

  if (rightIrVal == 0) {
    digitalWrite(rightRedLedPin, HIGH);
  } else {
    digitalWrite(rightRedLedPin, LOW);
  }
}

void moveBack2(){
  servoLeft.writeMicroseconds(1300); 
  servoRight.writeMicroseconds(1700);
  delay(1300);
}
void moveForward2(){
  servoLeft.writeMicroseconds(1900); 
  servoRight.writeMicroseconds(1100); 
}

void spin720() {
  checkalreadyturn = true;
  servoLeft.writeMicroseconds(1700);  
  servoRight.writeMicroseconds(1700); 
  delay(4450);                 
  moveForward();   // 720+90
}
void spin180() {
  servoLeft.writeMicroseconds(1700);  
  servoRight.writeMicroseconds(1550); 
  delay(1300);                 
  moveForward();  
}
void moveALittle(){
  servoLeft.writeMicroseconds(1700); 
  servoRight.writeMicroseconds(1300); 
  delay(1200);   //need to be test

}

void moveForward() {
  servoLeft.writeMicroseconds(1800); 
  servoRight.writeMicroseconds(1200); 
}

void turnRight() {
  servoLeft.writeMicroseconds(1700);  
  servoRight.writeMicroseconds(1550);
  delay(500);                 
  moveForward();                 
}

void turnLeft() {
  if(checkalreadyturn == false){
    servoLeft.writeMicroseconds(1450); 
    servoRight.writeMicroseconds(1300);
    delay(530);                 
    moveForward();   
  }
  else{
    servoLeft.writeMicroseconds(1450); 
    servoRight.writeMicroseconds(1300);
    ending++;  
    delay(530);                 
    moveForward();   
  }
                
}

void slightTurnRight() {
  flag1 = 1;
  flag2 = 0;
  servoLeft.writeMicroseconds(1800); 
  servoRight.writeMicroseconds(1450); 
  delay(100);                     
  moveForward();                
}

void slightTurnLeft() {
  flag2 = 1;
  flag1 = 0;
  servoLeft.writeMicroseconds(1525);  
  servoRight.writeMicroseconds(1325); 
  delay(100);                   
  moveForward();                
}

void moveback(){
  servoLeft.writeMicroseconds(1400);  
  servoRight.writeMicroseconds(1600);
  delay(110);
}

void stop(){
  exit(0);

}


int irDetect(int irLedPin, int irReceiverPin, long frequency) {
  tone(irLedPin, frequency);            
  delay(3);                               
  int irVal = digitalRead(irReceiverPin);  
  noTone(irLedPin);                        
  return irVal;
}
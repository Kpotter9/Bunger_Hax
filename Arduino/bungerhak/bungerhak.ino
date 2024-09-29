#include <cvzone.h>
////////////////////////////////////////////////////////////////////////////////////////////
// This code will be flashed into an arduino to receive data from 
// a python script in which detects peoples faces using Computer Vision.
///////////////////////////////////////////////////////////////////////////////////////////
//Takes in 6 variables with 3 digits
SerialData serialData(6,3);
int valsRec[6];
//Buzzer for face detected on right
int buzzerR = 9;
//Buzzer for face detected on left
int buzzerL = 10;
//number of loops
int time = 0;

void setup() {
  pinMode(buzzerR, OUTPUT);
  pinMode(buzzerL, OUTPUT);
  serialData.begin();
  Serial.begin(9600);
}

void loop() {
  //Gets data from python script
  //Format[buffer,distance to right,distance to left,buffer,people on left, people on right]
  serialData.Get(valsRec);
  int closeR = valsRec[1];
  int closeL = valsRec[2];

  int left = valsRec[4];
  int right = valsRec[5];

  time++;
  // If the person is closer speed of check increase
  // Power increases with number of people
  if (time % (int(300/closeL)) == 0){
    
    analogWrite(buzzerL, left*50);
    
    Serial.println(time);
  }
  if (time%(int(300/closeR)) == 0){
    analogWrite(buzzerR, right*50);
    
    Serial.println(time);
  }

  delay(500);
  //reset buzzers
  analogWrite(buzzerR, 0);
  analogWrite(buzzerL, 0);
  delay(1);

  
}

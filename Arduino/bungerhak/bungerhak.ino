#include <cvzone.h>

SerialData serialData(6,3);
int valsRec[6];

unsigned long prevTimeL = 0;
unsigned long prevTimeR = 0;

const long delayL = 500;
const long delayR = 500;

int buzzerR = 9;
int buzzerL = 10;
int time = 0;

void setup() {
  pinMode(buzzerR, OUTPUT);
  pinMode(buzzerL, OUTPUT);
  serialData.begin();
  Serial.begin(9600);
}

void loop() {
  unsigned long currTime = millis();

  serialData.Get(valsRec);
  int closeR = valsRec[1];
  int closeL = valsRec[2];

  int left = valsRec[4];
  int right = valsRec[5];

  time++;
  if (time % (int(300/closeL)) == 0){
    
    analogWrite(buzzerL, left*50);
    
    Serial.println(time);
  }
  if (time%(int(300/closeR)) == 0){
    analogWrite(buzzerR, right*50);
    
    Serial.println(time);
  }

  delay(500);
  analogWrite(buzzerR, 0);
  analogWrite(buzzerL, 0);
  delay(1);

  // if (currTime % (1000-closeL) <= 10) {
  //   analogWrite(buzzerL, left * 85);
  //   delay(closeL*4);
  // }

  // if (currTime % (1000-closeR) <= 10) {
  //   analogWrite(buzzerR, right * 85);
  //   delay(closeR*4);
  // }
}

/*
  DigitalReadSerial

  Reads a digital input on pin 2, prints the result to the Serial Monitor

  This example code is in the public domain.

  https://www.arduino.cc/en/Tutorial/BuiltInExamples/DigitalReadSerial
*/

#include <SoftwareSerial.h>

SoftwareSerial HM10(9, 10); // RX, TX

// digital pin 2 has a pushbutton attached to it. Give it a name:
char appData;  
String inData = "";
int state = 0;
int pushButton = 2;
int P = 6;
int R = 5;
int Y = 4;
int G = 3;

boolean ped = false; 

// the setup routine runs once when you press reset:
void setup() {
  // initialize serial communication at 9600 bits per second:
  Serial.begin(9600);
  HM10.begin(9600);
  // make the pushbutton's pin an input:
  pinMode(pushButton, INPUT);
  pinMode(P, OUTPUT);
  pinMode(R, OUTPUT);
  pinMode(Y, OUTPUT);
  pinMode(G, OUTPUT);
}

// the loop routine runs over and over again forever:
void loop() {
  // read the input pin:
  int buttonState = digitalRead(pushButton);
  // print out the state of the button:
  Serial.println(buttonState);
  if (HM10.available() > 0) {
    appData = HM10.read();
    inData = String(appData);  // save the data in string format
    if(inData == "1") {
      Serial.println("A pedestrian used bluetooth to press the walk button");
      ped = true;
    }    
  }
  if(ped) {
    pedestrianFlow();
  } else {
    regularTrafficFlow();
  }
  delay(1);        // delay in between reads for stability
}

void checkPed() {
  int count = 0;
  while(count < 200) {
    if(digitalRead(pushButton)==HIGH){
      ped = true;
    }
    count = count + 1;
    delay(10);
  }
}

void pedestrianFlow() {
  digitalWrite(P,HIGH);
  digitalWrite(R,HIGH);
  digitalWrite(Y,LOW);
  digitalWrite(G,LOW);
  delay(6000);
  digitalWrite(P,LOW);
  ped = false;
}

void regularTrafficFlow() {
  digitalWrite(R,LOW);
  digitalWrite(Y,LOW);
  digitalWrite(G,HIGH);
  checkPed();

  digitalWrite(R,LOW);
  digitalWrite(Y,HIGH);
  digitalWrite(G,LOW);
  checkPed();

  digitalWrite(R,HIGH);
  digitalWrite(Y,LOW);
  digitalWrite(G,LOW);
  checkPed();
}

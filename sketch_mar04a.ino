#include <Servo.h>

Servo myservo;  // create servo object to control a servo
// a maximum of eight servo objects can be created

int pos;    // variable to store the servo position
int const numOfSensors = 2;
int sensorPin[numOfSensors] = {A0, A1};
int sensorValues[numOfSensors];
int photodiodeMap[numOfSensors];


void setup()
{
  myservo.attach(2);  // attaches the servo on pin 2 to the servo object
  myservo.write(90);
  Serial.begin(9600);
  pinMode(sensorPin[0], INPUT);
  pinMode(sensorPin[1], INPUT);

  // initialize photodiode prev reading to 0
  for (int i = 0; i < numOfSensors; i++) {
    sensorValues[i] = 0;
    photodiodeMap[i] = sensorValues[i];
  }
}


void loop()
{
  Serial.begin(9600);

  int randomBoy = random (0, 10);
  //  for (pos = 15; pos < 160; pos += 1) // goes from 0 degrees to 160 degrees
  //  { // in steps of 1 degree
  //    if ((randomBoy % 2) == 0) {
  //   //   pos = 0;
  //    }
  //    myservo.write(pos);              // tell servo to go to position in variable 'pos'
  //    delay(30);                       // waits 15ms for the servo to reach the position
  //  }
  //  for (pos = 160; pos >=15; pos -= 1) // goes from 180 degrees to 0 degrees
  //  {
  //    myservo.write(pos);              // tell servo to go to position in variable 'pos'
  //    delay(30);                       // waits 15ms for the servo to reach the position
  //  }

  // photodiode input extraction
  for (int i = 0; i < numOfSensors; i++) {
    sensorValues[i] = analogRead(sensorPin[i]);
    photodiodeMap[i] = sensorValues[i];
    //    Serial.print(sensorValues[0]);
    //    Serial.print(" ");
    //    Serial.println(sensorValues[1]);
  }

  if (photodiodeMap[1] - photodiodeMap[0] <= 1 && photodiodeMap[1] - photodiodeMap[0] >= -1) {
    Serial.println("Dont move");

    delay(10);
  } else if ((photodiodeMap[0] - photodiodeMap[1]) >= 1) {
    Serial.println("Move to 1");
    pos++;
    myservo.write(pos);
    delay(10);
  } else if ((photodiodeMap[1] - photodiodeMap[0]) >= 1) {
    Serial.println("Move to 0");
    pos--;
    myservo.write(pos);
    delay(10);
  }
//  //myservo.write(0);
}

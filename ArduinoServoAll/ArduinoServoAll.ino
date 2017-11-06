#include <Servo.h>
#define FINGER0 2
#define FINGER1 3
#define FINGER2 4
#define FINGER3 5
#define FINGER4 6

Servo servo0;
Servo servo1;
Servo servo2;
Servo servo3;
Servo servo4;

#define MAXVOLTAGE0 250
#define MINVOLTAGE0 145
#define SERVOMAX0 85

#define MAXVOLTAGE1 280
#define MINVOLTAGE1 155
#define SERVOMAX1 105

#define MAXVOLTAGE2 275
#define MINVOLTAGE2 200
#define SERVOMAX2 170

#define MAXVOLTAGE3 260
#define MINVOLTAGE3 155
#define SERVOMAX3 80

#define MAXVOLTAGE4 270
#define MINVOLTAGE4 215
#define SERVOMAX4 75


#define FINGER2FORCE A2
#define FINGER3FORCE A3

void setup() {
  // put your setup code here, to run once:
  servo0.attach(FINGER0);
  servo1.attach(FINGER1);
  servo2.attach(FINGER2);
  servo3.attach(FINGER3);
  servo4.attach(FINGER4);
  servo0.write(0);
  servo1.write(0);
  servo2.write(0);
  servo3.write(0);
  servo4.write(0);
  Serial.begin(9600);
  pinMode(FINGER2FORCE, INPUT);
  pinMode(FINGER3FORCE, INPUT);
}

void loop() {
  // put your main code here, to run repeatedly:
  String commandbuffer;

  if (Serial.available()) {
    commandbuffer = Serial.readStringUntil('\n');
    if (commandbuffer.toInt() > 0) {
      int commaIndex0 = commandbuffer.indexOf(',');
      int commaIndex1 = commandbuffer.indexOf(',', commaIndex0 + 1);
      int commaIndex2 = commandbuffer.indexOf(',', commaIndex1 + 1);
      int commaIndex3 = commandbuffer.indexOf(',', commaIndex2 + 1);
      String command0 = commandbuffer.substring(0, commaIndex0);
      String command1 = commandbuffer.substring(commaIndex0 + 1, commaIndex1);
      String command2 = commandbuffer.substring(commaIndex1 + 1, commaIndex2);
      String command3 = commandbuffer.substring(commaIndex2 + 1, commaIndex3);
      String command4 = commandbuffer.substring(commaIndex3 + 1);   // To the end of the string

      int value0 = map(command0.toInt(), MAXVOLTAGE0, MINVOLTAGE0, 0, SERVOMAX0);
      int value1 = map(command1.toInt(), MAXVOLTAGE1, MINVOLTAGE1, 0, SERVOMAX1);
      int value2 = map(command2.toInt(), MAXVOLTAGE2, MINVOLTAGE2, 0, SERVOMAX2);
      int value3 = map(command3.toInt(), MAXVOLTAGE3, MINVOLTAGE3, 0, SERVOMAX3);
      int value4 = map(command4.toInt(), MAXVOLTAGE4, MINVOLTAGE4, 0, SERVOMAX4);
      value0 = constrain(value0, 0, SERVOMAX0);
      value1 = constrain(value1, 0, SERVOMAX1);
      value2 = constrain(value2, 0, SERVOMAX2);
      value3 = constrain(value3, 0, SERVOMAX3);
      value4 = constrain(value4, 0, SERVOMAX4);
      servo0.write(value0);
      servo1.write(value1);
      servo2.write(value2);
      servo3.write(value3);
      servo4.write(value4);

      double voltageReading2 = 100.0 * 5.0 * analogRead(FINGER2FORCE) / 1023;
      double voltageReading3 = 100.0 * 5.0 * analogRead(FINGER3FORCE) / 1023;

      String voltageReadings;
      voltageReadings.concat((int)voltageReading2);
      voltageReadings.concat(',');
      voltageReadings.concat((int)voltageReading3);
      Serial.println(voltageReadings);
      //delay(5000);
    }
  }
}

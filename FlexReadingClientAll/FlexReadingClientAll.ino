// This sketch reads the voltage level of a 10k-15k ohm flex resistor
// with a 12.2k voltage divider.
//
//  +5 volts
//   |
//   |
//    \
//   /  Flex resistor
//    \
//   /
//   |
//   |---------------- readingPin A0
//   |
//    \
//   /  12.2k resistor
//    \
//   /
//   |
//   |
//   GND
//
//  readingPin should read 2.74 volts when straight,
//  2.24 volts when flexxed.

// Finger 0 is pinky, Finger 4 is thumb.
#define FINGER0 A0
#define FINGER1 A1
#define FINGER2 A2
#define FINGER3 A3
#define FINGER4 A4
#define resistance 12200

#define VIBRATEMIN 50 // Starts vibrating at around 65
#define VIBRATEMAX 100

#define FINGER2VIB 6
#define FINGER3VIB 7
#define FORCESENSEVOLTMIN 0
#define FORCESENSEVOLTMAX 400

void setup() {
  // put your setup code here, to run once:
  Serial.begin(9600);
  pinMode(FINGER0, INPUT);
  pinMode(FINGER1, INPUT);
  pinMode(FINGER2, INPUT);
  pinMode(FINGER3, INPUT);
  pinMode(FINGER4, INPUT);

  double voltageReading0 = 100.0 * 5.0 * analogRead(FINGER0) / 1023;
  double voltageReading1 = 100.0 * 5.0 * analogRead(FINGER1) / 1023;
  double voltageReading2 = 100.0 * 5.0 * analogRead(FINGER2) / 1023;
  double voltageReading3 = 100.0 * 5.0 * analogRead(FINGER3) / 1023;
  double voltageReading4 = 100.0 * 5.0 * analogRead(FINGER4) / 1023;

  String voltageReadings;
  voltageReadings.concat((int)voltageReading0);
  voltageReadings.concat(',');
  voltageReadings.concat((int)voltageReading1);
  voltageReadings.concat(',');
  voltageReadings.concat((int)voltageReading2);
  voltageReadings.concat(',');
  voltageReadings.concat((int)voltageReading3);
  voltageReadings.concat(',');
  voltageReadings.concat((int)voltageReading4);
  Serial.println(voltageReadings);
}

void loop() {
  // put your main code here, to run repeatedly:
  String commandbuffer;
  if (Serial.available()) {
    commandbuffer = Serial.readStringUntil('\n');
    double voltageReading0 = 100.0 * 5.0 * analogRead(FINGER0) / 1023;
    double voltageReading1 = 100.0 * 5.0 * analogRead(FINGER1) / 1023;
    double voltageReading2 = 100.0 * 5.0 * analogRead(FINGER2) / 1023;
    double voltageReading3 = 100.0 * 5.0 * analogRead(FINGER3) / 1023;
    double voltageReading4 = 100.0 * 5.0 * analogRead(FINGER4) / 1023;

    String voltageReadings;
    voltageReadings.concat((int)voltageReading0);
    voltageReadings.concat(',');
    voltageReadings.concat((int)voltageReading1);
    voltageReadings.concat(',');
    voltageReadings.concat((int)voltageReading2);
    voltageReadings.concat(',');
    voltageReadings.concat((int)voltageReading3);
    voltageReadings.concat(',');
    voltageReadings.concat((int)voltageReading4);

    // Parse the Force sensor input and output to analogWrite
    int commaIndex0 = commandbuffer.indexOf(',');
    String command2 = commandbuffer.substring(0, commaIndex0);
    String command3 = commandbuffer.substring(commaIndex0 + 1);   // To the end of the string
    int value2 = map(command2.toInt(), FORCESENSEVOLTMIN, FORCESENSEVOLTMAX, VIBRATEMIN, VIBRATEMAX);
    int value3 = map(command3.toInt(), FORCESENSEVOLTMIN, FORCESENSEVOLTMAX, VIBRATEMIN, VIBRATEMAX);
    value2 = constrain(value2, VIBRATEMIN, VIBRATEMAX);
    value3 = constrain(value3, VIBRATEMIN, VIBRATEMAX);
    analogWrite(FINGER2VIB, value2);
    analogWrite(FINGER3VIB, value3);
    Serial.println(voltageReadings);
  }
}


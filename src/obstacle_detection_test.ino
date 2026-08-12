// Ultrassonic Sensors
const int TRIG_Left = 5;
const int ECHO_Left = 18;

const int TRIG_Right = 19;
const int ECHO_Right = 21;

const int TRIG_Top = 32;
const int ECHO_Top = 33;


// Motor
const int rightMotor = 23;
const int leftMotor = 22;
const int topMotor = 25;


// Distance thresholds (cm)
const int FAR_DISTANCE = 70;
const int MEDIUM_DISTANCE = 30;
const int CLOSE_DISTANCE = 10;


// Vibration timing (ms)
const int SLOW_VIBRATION = 500;
const int FAST_VIBRATION = 100;


// Motor timing
unsigned long previousMillis_Left = 0;
unsigned long previousMillis_Right = 0;
unsigned long previousMillis_Top = 0;


bool motorState_Left = LOW;
bool motorState_Right = LOW;
bool motorState_Top = LOW;


// Ultrasonic sensor timing
unsigned long sensorTimer = 0;
unsigned long echoStart = 0;

const unsigned long ECHO_TIMEOUT = 30000;
const unsigned long SENSOR_GAP = 3000;


// Sensor states
const int SENSOR_LEFT = 0;
const int SENSOR_RIGHT = 1;
const int SENSOR_TOP = 2;

const int WAITING_FOR_TRIGGER = 0;
const int WAITING_FOR_ECHO_START = 1;
const int WAITING_FOR_ECHO_END = 2;
const int WAITING_FOR_NEXT_SENSOR = 3;

int currentSensor = SENSOR_LEFT;
int sensorState = WAITING_FOR_TRIGGER;

float distance_Left = 0;
float distance_Right = 0;
float distance_Top = 0;


// C++ code
//
void setup() {
  Serial.begin(115200);

  pinMode(TRIG_Left, OUTPUT);
  pinMode(TRIG_Right, OUTPUT);
  pinMode(TRIG_Top, OUTPUT);

  pinMode(ECHO_Left, INPUT);
  pinMode(ECHO_Right, INPUT);
  pinMode(ECHO_Top, INPUT);

  pinMode(rightMotor, OUTPUT);
  pinMode(leftMotor, OUTPUT);
  pinMode(topMotor, OUTPUT);

  digitalWrite(TRIG_Left, LOW);
  digitalWrite(TRIG_Right, LOW);
  digitalWrite(TRIG_Top, LOW);
}


void loop() {

  unsigned long currentMillis = millis();
  unsigned long currentMicros = micros();


  // Ultrasonic sensors

  if (sensorState == WAITING_FOR_TRIGGER) {

    if (currentSensor == SENSOR_LEFT) {
      digitalWrite(TRIG_Left, HIGH);
      delayMicroseconds(10);
      digitalWrite(TRIG_Left, LOW);
    }

    else if (currentSensor == SENSOR_RIGHT) {
      digitalWrite(TRIG_Right, HIGH);
      delayMicroseconds(10);
      digitalWrite(TRIG_Right, LOW);
    }

    else if (currentSensor == SENSOR_TOP) {
      digitalWrite(TRIG_Top, HIGH);
      delayMicroseconds(10);
      digitalWrite(TRIG_Top, LOW);
    }

    sensorTimer = currentMicros;
    sensorState = WAITING_FOR_ECHO_START;
  }


  else if (sensorState == WAITING_FOR_ECHO_START) {

    int echoPin;

    if (currentSensor == SENSOR_LEFT) {
      echoPin = ECHO_Left;
    }

    else if (currentSensor == SENSOR_RIGHT) {
      echoPin = ECHO_Right;
    }

    else {
      echoPin = ECHO_Top;
    }


    if (digitalRead(echoPin) == HIGH) {
      echoStart = currentMicros;
      sensorState = WAITING_FOR_ECHO_END;
    }

    else if (currentMicros - sensorTimer >= ECHO_TIMEOUT) {

      if (currentSensor == SENSOR_LEFT) {
        distance_Left = 999;
      }

      else if (currentSensor == SENSOR_RIGHT) {
        distance_Right = 999;
      }

      else {
        distance_Top = 999;
      }

      sensorTimer = currentMicros;
      sensorState = WAITING_FOR_NEXT_SENSOR;
    }
  }


  else if (sensorState == WAITING_FOR_ECHO_END) {

    int echoPin;

    if (currentSensor == SENSOR_LEFT) {
      echoPin = ECHO_Left;
    }

    else if (currentSensor == SENSOR_RIGHT) {
      echoPin = ECHO_Right;
    }

    else {
      echoPin = ECHO_Top;
    }


    if (digitalRead(echoPin) == LOW) {

      unsigned long echoDuration = currentMicros - echoStart;

      float distance = echoDuration * 0.034 / 2;


      if (currentSensor == SENSOR_LEFT) {
        distance_Left = distance;
      }

      else if (currentSensor == SENSOR_RIGHT) {
        distance_Right = distance;
      }

      else {
        distance_Top = distance;
      }


      sensorTimer = currentMicros;
      sensorState = WAITING_FOR_NEXT_SENSOR;
    }

    else if (currentMicros - echoStart >= ECHO_TIMEOUT) {

      if (currentSensor == SENSOR_LEFT) {
        distance_Left = 999;
      }

      else if (currentSensor == SENSOR_RIGHT) {
        distance_Right = 999;
      }

      else {
        distance_Top = 999;
      }

      sensorTimer = currentMicros;
      sensorState = WAITING_FOR_NEXT_SENSOR;
    }
  }


  else if (sensorState == WAITING_FOR_NEXT_SENSOR) {

    if (currentMicros - sensorTimer >= SENSOR_GAP) {

      if (currentSensor == SENSOR_LEFT) {
        currentSensor = SENSOR_RIGHT;
      }

      else if (currentSensor == SENSOR_RIGHT) {
        currentSensor = SENSOR_TOP;
      }

      else {
        currentSensor = SENSOR_LEFT;
      }

      sensorState = WAITING_FOR_TRIGGER;
    }
  }


  // Print distances

  static unsigned long previousSerialMillis = 0;

  if (currentMillis - previousSerialMillis >= 300) {

    previousSerialMillis = currentMillis;

    Serial.print("Distance Left: ");
    Serial.print(distance_Left);
    Serial.println(" cm");

    Serial.print("Distance Right: ");
    Serial.print(distance_Right);
    Serial.println(" cm");

    Serial.print("Distance Top: ");
    Serial.print(distance_Top);
    Serial.println(" cm");

    Serial.println();
  }


  // Left Side

  if (distance_Left > FAR_DISTANCE) {
    digitalWrite(leftMotor, LOW);
    motorState_Left = LOW;
  }

  else if (distance_Left > MEDIUM_DISTANCE) {

    if (currentMillis - previousMillis_Left >= SLOW_VIBRATION) {
      previousMillis_Left = currentMillis;

      if (motorState_Left == LOW) {
        motorState_Left = HIGH;
      }

      else {
        motorState_Left = LOW;
      }

      digitalWrite(leftMotor, motorState_Left);
    }
  }

  else if (distance_Left > CLOSE_DISTANCE) {

    if (currentMillis - previousMillis_Left >= FAST_VIBRATION) {
      previousMillis_Left = currentMillis;

      if (motorState_Left == LOW) {
        motorState_Left = HIGH;
      }

      else {
        motorState_Left = LOW;
      }

      digitalWrite(leftMotor, motorState_Left);
    }
  }

  else {
    digitalWrite(leftMotor, HIGH);
    motorState_Left = HIGH;
  }


  // Right Side

  if (distance_Right > FAR_DISTANCE) {
    digitalWrite(rightMotor, LOW);
    motorState_Right = LOW;
  }

  else if (distance_Right > MEDIUM_DISTANCE) {

    if (currentMillis - previousMillis_Right >= SLOW_VIBRATION) {
      previousMillis_Right = currentMillis;

      if (motorState_Right == LOW) {
        motorState_Right = HIGH;
      }

      else {
        motorState_Right = LOW;
      }

      digitalWrite(rightMotor, motorState_Right);
    }
  }

  else if (distance_Right > CLOSE_DISTANCE) {

    if (currentMillis - previousMillis_Right >= FAST_VIBRATION) {
      previousMillis_Right = currentMillis;

      if (motorState_Right == LOW) {
        motorState_Right = HIGH;
      }

      else {
        motorState_Right = LOW;
      }

      digitalWrite(rightMotor, motorState_Right);
    }
  }

  else {
    digitalWrite(rightMotor, HIGH);
    motorState_Right = HIGH;
  }


  // Top Side

  if (distance_Top > FAR_DISTANCE) {
    digitalWrite(topMotor, LOW);
    motorState_Top = LOW;
  }

  else if (distance_Top > MEDIUM_DISTANCE) {

    if (currentMillis - previousMillis_Top >= SLOW_VIBRATION) {
      previousMillis_Top = currentMillis;

      if (motorState_Top == LOW) {
        motorState_Top = HIGH;
      }

      else {
        motorState_Top = LOW;
      }

      digitalWrite(topMotor, motorState_Top);
    }
  }

  else if (distance_Top > CLOSE_DISTANCE) {

    if (currentMillis - previousMillis_Top >= FAST_VIBRATION) {
      previousMillis_Top = currentMillis;

      if (motorState_Top == LOW) {
        motorState_Top = HIGH;
      }

      else {
        motorState_Top = LOW;
      }

      digitalWrite(topMotor, motorState_Top);
    }
  }

  else {
    digitalWrite(topMotor, HIGH);
    motorState_Top = HIGH;
  }
}

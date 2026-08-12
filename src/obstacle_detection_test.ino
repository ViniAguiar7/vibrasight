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
}


void loop() {

  // Measure left side
  digitalWrite(TRIG_Left, LOW);
  delayMicroseconds(2);
  digitalWrite(TRIG_Left, HIGH);
  delayMicroseconds(10);
  digitalWrite(TRIG_Left, LOW);

  long duration_Left = pulseIn(ECHO_Left, HIGH);


  // Measure right side
  digitalWrite(TRIG_Right, LOW);
  delayMicroseconds(2);
  digitalWrite(TRIG_Right, HIGH);
  delayMicroseconds(10);
  digitalWrite(TRIG_Right, LOW);

  long duration_Right = pulseIn(ECHO_Right, HIGH);


  // Measure top side
  digitalWrite(TRIG_Top, LOW);
  delayMicroseconds(2);
  digitalWrite(TRIG_Top, HIGH);
  delayMicroseconds(10);
  digitalWrite(TRIG_Top, LOW);

  long duration_Top = pulseIn(ECHO_Top, HIGH);


  float distance_Left = duration_Left * 0.034 / 2;
  float distance_Right = duration_Right * 0.034 / 2;
  float distance_Top = duration_Top * 0.034 / 2;


  Serial.print("Distance Left: ");
  Serial.print(distance_Left);
  Serial.println(" cm");

  Serial.print("Distance Right: ");
  Serial.print(distance_Right);
  Serial.println(" cm");

  Serial.print("Distance Top: ");
  Serial.print(distance_Top);
  Serial.println(" cm");


  // Current time
  unsigned long currentMillis = millis();


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

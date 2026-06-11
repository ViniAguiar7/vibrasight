// Ultrassonic Sensors
const int TRIG_Left = 5;
const int ECHO_Left = 18;
const int TRIG_Right = 19;
const int ECHO_Right = 21;

// Motor
const int rightMotor = 23;
const int leftMotor = 22;

// Distance thresholds (cm)
const int FAR_DISTANCE = 70;
const int MEDIUM_DISTANCE = 30;
const int CLOSE_DISTANCE = 10;

// Vibration timing (ms)
const int SLOW_VIBRATION = 500;
const int FAST_VIBRATION = 100;
const int LOOP_DELAY = 300;



// C++ code
//
void setup() {
  Serial.begin(115200);
  pinMode(TRIG_Left, OUTPUT);
  pinMode(TRIG_Right, OUTPUT);
  pinMode(ECHO_Left, INPUT);
  pinMode(ECHO_Right, INPUT);
  pinMode(rightMotor, OUTPUT);
  pinMode(leftMotor, OUTPUT);
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

  float distance_Left = duration_Left * 0.034 / 2;
  float distance_Right = duration_Right * 0.034 / 2;


  Serial.print("Distance Left: ");
  Serial.print(distance_Left);
  Serial.println(" cm");

  Serial.print("Distance Right: ");
  Serial.print(distance_Right);
  Serial.println(" cm");

//Left Side

  if (distance_Left > FAR_DISTANCE) {
    digitalWrite(leftMotor, LOW);
  }

  else if (distance_Left > MEDIUM_DISTANCE) {
    digitalWrite(leftMotor, HIGH);
    delay(SLOW_VIBRATION);
    digitalWrite(leftMotor, LOW);
    delay(SLOW_VIBRATION);
  }

  else if (distance_Left > CLOSE_DISTANCE) {
    digitalWrite(leftMotor, HIGH);
    delay(FAST_VIBRATION);
    digitalWrite(leftMotor, LOW);
    delay(FAST_VIBRATION);
  }

  else {
    digitalWrite(leftMotor, HIGH);
  }

//Right Side

 if (distance_Right > FAR_DISTANCE) {
    digitalWrite(rightMotor, LOW);
  }

  else if (distance_Right > MEDIUM_DISTANCE) {
    digitalWrite(rightMotor, HIGH);
    delay(SLOW_VIBRATION);
    digitalWrite(rightMotor, LOW);
    delay(SLOW_VIBRATION);
  }

  else if (distance_Right > CLOSE_DISTANCE) {
    digitalWrite(rightMotor, HIGH);
    delay(FAST_VIBRATION);
    digitalWrite(rightMotor, LOW);
    delay(FAST_VIBRATION);
  }

  else {
    digitalWrite(rightMotor, HIGH);
  }

  delay(LOOP_DELAY);
}

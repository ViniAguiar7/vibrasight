const int TRIG = 5;
const int ECHO = 18;
const int rightMotor = 23;
const int leftMotor = 22;

// C++ code
//
void setup() {
  Serial.begin(115200);
  pinMode(TRIG, OUTPUT);
  pinMode(ECHO, INPUT);
  pinMode(rightMotor, OUTPUT);
  pinMode(leftMotor, OUTPUT);
}

void loop() {
  digitalWrite(TRIG, LOW);
  delayMicroseconds(2);

  digitalWrite(TRIG, HIGH);
  delayMicroseconds(10);

  digitalWrite(TRIG, LOW);

  long duration = pulseIn(ECHO, HIGH);

  float distance = duration * 0.034 / 2;

  Serial.print("Distance: ");
  Serial.print(distance);
  Serial.println(" cm");


  if (distance > 70) {
    digitalWrite(rightMotor, LOW);
    digitalWrite(leftMotor, LOW);
  } else if (distance > 30) {
    digitalWrite(rightMotor, HIGH);
    digitalWrite(leftMotor, HIGH);
    delay(500);
    digitalWrite(rightMotor, LOW);
    digitalWrite(leftMotor, LOW);
    delay(500);
  } else if (distance > 10) {
    digitalWrite(rightMotor, HIGH);
    digitalWrite(leftMotor, HIGH);
    delay(100);
    digitalWrite(rightMotor, LOW);
    digitalWrite(leftMotor, LOW);
    delay(100);
  } else {
    digitalWrite(rightMotor, HIGH);
    digitalWrite(leftMotor, HIGH);
  }
  delay(300);
}

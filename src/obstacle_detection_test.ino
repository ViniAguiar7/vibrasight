const int TRIG = 5;
const int ECHO = 18;
const int vibrationMotor = 23;

void setup()
{
  Serial.begin(115200);

  pinMode(TRIG, OUTPUT);
  pinMode(ECHO, INPUT);

  pinMode(vibrationMotor, OUTPUT);

  digitalWrite(TRIG, LOW);
}

void loop()
{
  digitalWrite(TRIG, LOW);
  delayMicroseconds(2);

  digitalWrite(TRIG, HIGH);
  delayMicroseconds(10);

  digitalWrite(TRIG, LOW);

  long duration = pulseIn(ECHO, HIGH);

  float distance = duration * 0.034 / 2;

  Serial.print("Distance: ");
  Serial.print(distance, 1);
  Serial.println(" cm");

  if (distance < 20)
  {
    digitalWrite(vibrationMotor, HIGH);
  }
  else
  {
    digitalWrite(vibrationMotor, LOW);
  }

  delay(300);
}

const int TRIG = 5;
const int ECHO = 18;
const int MOTOR = 23;

// C++ code
//
void setup()
{
  Serial.begin(115200);
  pinMode(TRIG, OUTPUT);
  pinMode(ECHO, INPUT);
  pinMode(MOTOR, OUTPUT);
}

void loop()
{
  digitalWrite(TRIG, LOW);
  delayMicroseconds(2);
  
  digitalWrite(TRIG, HIGH);
  delayMicroseconds(10);
  
  digitalWrite(TRIG, LOW);
  
  long duracao = pulseIn(ECHO, HIGH);
  
  float distancia = duracao * 0.034 / 2;
  
  Serial.print("Distancia: ");
  Serial.print(distancia);
  Serial.println(" cm");
  
  

  if (distancia < 20) {
  digitalWrite(MOTOR, HIGH);
}
else {
  digitalWrite(MOTOR, LOW);
}
delay(300);
}
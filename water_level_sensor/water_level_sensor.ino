int led = D4;
int sensor = D1;
void setup() {
  pinMode(led, OUTPUT);
  pinMode(sensor, INPUT);
  Serial.begin(115200);
}

void loop() {
  Serial.println(digitalRead(sensor));
  if(digitalRead(sensor) == HIGH){
    digitalWrite(led, HIGH);
  }else{
    digitalWrite(led, LOW);
  }
  delay(500);
}

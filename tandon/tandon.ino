#define LED_BUILTIN D4
#define SENSOR  D2
#define relay1 D7
#define relay2 D6
#define tandon D1

long currentMillis = 0;
long previousMillis = 0;
int interval = 1000;
boolean ledState = LOW;
float calibrationFactor = 4.5;
volatile byte pulseCount;
byte pulse1Sec = 0;
float flowRate;
unsigned int flowMilliLitres;
unsigned long totalMilliLitres;

void IRAM_ATTR pulseCounter()
{
  pulseCount++;
}

void setup(){
  Serial.begin(115200);
  pinMode(relay1, OUTPUT);
  pinMode(relay2, OUTPUT);
  pinMode(LED_BUILTIN, OUTPUT);
  pinMode(SENSOR, INPUT_PULLUP);
  pinMode(tandon, INPUT);

  pulseCount = 0;
  flowRate = 0.0;
  flowMilliLitres = 0;
  totalMilliLitres = 0;
  previousMillis = 0;
  attachInterrupt(digitalPinToInterrupt(SENSOR), pulseCounter, FALLING);
}

void loop(){
  currentMillis = millis();
  if (currentMillis - previousMillis > interval) {
    pulse1Sec = pulseCount;
    pulseCount = 0;
    flowRate = ((1000.0 / (millis() - previousMillis)) * pulse1Sec) / calibrationFactor;
    previousMillis = millis();
    flowMilliLitres = (flowRate / 60) * 1000;
    totalMilliLitres += flowMilliLitres;
    if(digitalRead(tandon) == HIGH){
      digitalWrite(relay1, LOW);
      digitalWrite(relay2, LOW);
      for(int i = 0; i < 10; i++){
        Serial.print("Jumlah Aliran: ");
        Serial.print(int(flowRate)); 
        Serial.print("L/min");
        Serial.print("\t");
    
        Serial.print("Jumlah air Yang Mengalir: ");
        Serial.print(totalMilliLitres);
        Serial.print("mL / ");
        Serial.print(totalMilliLitres / 1000);
        Serial.println("L");
        delay(1000);
      }
      for(int i = 0; i < 5; i++){
        Serial.print("Jumlah Aliran: ");
        Serial.print(int(flowRate)); 
        Serial.print("L/min");
        Serial.print("\t");
    
        Serial.print("Jumlah air Yang Mengalir: ");
        Serial.print(totalMilliLitres);
        Serial.print("mL / ");
        Serial.print(totalMilliLitres / 1000);
        Serial.println("L");
        if(int(flowRate) < 2){
          digitalWrite(relay2, HIGH);
        }
        delay(1000);
      }
    }else{
      digitalWrite(relay1, HIGH);
    }
  }
}

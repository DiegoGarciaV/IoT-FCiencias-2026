#define LED1 14
#define LED2 27
#define LED3 26
#define LED4 25
#define LED5 33

#define BACKGROUND_INPUT 2
#define LDR_INPUT 34
#define LDR_MIN 1300
#define LDR_MAX 2500

int background = LOW;
int highlight = HIGH;

int lastBackgroundState = LOW;

int ledsArray[] = {LED1, LED2, LED3, LED4, LED5};

int ledsCount = 5;

void setup() {
  
  for (int i = 0; i < ledsCount; i++) {
    pinMode(ledsArray[i], OUTPUT);
    digitalWrite(ledsArray[i], background);
  }

  pinMode(BACKGROUND_INPUT, INPUT);
  pinMode(LDR_INPUT, INPUT);
  Serial.begin(115200);

}
void loop() {
  
  int ldrValue = analogRead(LDR_INPUT);
  int ledsIndicator = (LDR_MAX - ldrValue) * ledsCount / (LDR_MAX - LDR_MIN);
  
  if (ldrValue <= LDR_MIN) {
    ledsIndicator = ledsCount;
  }
  else if (ldrValue >= LDR_MAX) {
    ledsIndicator = 0;
  }
  
  for (int i = 0; i < ledsCount; i++) {
      digitalWrite(ledsArray[i], i < ledsIndicator ? highlight : background);
    }
  Serial.println(ldrValue);

}

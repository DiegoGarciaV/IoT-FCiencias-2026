#define LED1 14
#define LED2 27
#define LED3 26
#define LED4 25
#define LED5 33

#define BACKGROUND_INPUT 2
#define INCREASE_SEQUENCE_INPUT 4
#define RESTART_SEQUENCE_INPUT 15

#define DEBOUNCE_TIME 200

int background = LOW;
int highlight = HIGH;

int lastRestartState = LOW;
int lastIncreaseState = LOW;
int lastBackgroundState = LOW;

int ledsArray[] = {LED1, LED2, LED3, LED4, LED5};

int currentPointer = 0;
int ledsCount = 5;

void setup() {
  
  for (int i = 0; i < ledsCount; i++) {
    pinMode(ledsArray[i], OUTPUT);
    digitalWrite(ledsArray[i], background);
  }

  pinMode(BACKGROUND_INPUT, INPUT);
  pinMode(INCREASE_SEQUENCE_INPUT, INPUT);
  pinMode(RESTART_SEQUENCE_INPUT, INPUT);

}

void clearSequence() {
  for (int i = 0; i < ledsCount; i++) {
    digitalWrite(ledsArray[i], background);
  }
}

int increaseSequence(int currentPointer) {
  if(currentPointer < ledsCount) {
    digitalWrite(ledsArray[currentPointer], highlight);
    return currentPointer + 1;
  }
  clearSequence();
  return 0;
}

void loop() {

  int increaseState = digitalRead(INCREASE_SEQUENCE_INPUT);
  int restartState = digitalRead(RESTART_SEQUENCE_INPUT);
  int backgroundState = digitalRead(BACKGROUND_INPUT);
  
  if (increaseState == HIGH && lastIncreaseState == LOW){
    currentPointer = increaseSequence(currentPointer);
    delay(DEBOUNCE_TIME);
  }

  else if (restartState == HIGH && lastRestartState == LOW) {
    clearSequence();
    currentPointer = 0;
    delay(DEBOUNCE_TIME);
  }
  else if (backgroundState == HIGH && lastBackgroundState == LOW) {
    highlight = background;
    background = background == LOW ? HIGH : LOW;
    for (int i = 0; i < ledsCount; i++) {
      digitalWrite(ledsArray[i], i < currentPointer ? highlight : background);
    }
    delay(DEBOUNCE_TIME);
  }
    
  lastIncreaseState = increaseState;
  lastRestartState = restartState;
  lastBackgroundState = backgroundState;

  
}

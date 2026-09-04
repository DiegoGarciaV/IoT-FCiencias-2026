#define LED1 14
#define LED2 27
#define LED3 26
#define LED4 25
#define LED5 33

#define BACKGROUND_INPUT 4

int background = LOW;
int highlight = HIGH;

int ledsArray[] = {LED1, LED2, LED3, LED4, LED5};

int currentPointer = 0;
int ledDirection = 1;
int ledsCount = 5;

int last_background_state = LOW;

void setup() {

  for (int i = 0; i < ledsCount; i++) {
    pinMode(ledsArray[i], OUTPUT);
    digitalWrite(ledsArray[i], background);
  }

  pinMode(BACKGROUND_INPUT, INPUT_PULLDOWN);
}

void loop() {

  int background_state = digitalRead(BACKGROUND_INPUT);

  if (background_state == HIGH && last_background_state == LOW) {

    highlight = background;
    background = (background == HIGH ? LOW : HIGH);

    for (int i = 0; i < ledsCount; i++) {
      digitalWrite(ledsArray[i], background);
    }
  }

  last_background_state = background_state;

  digitalWrite(ledsArray[currentPointer], highlight);
  delay(100);
  digitalWrite(ledsArray[currentPointer], background);

  currentPointer += ledDirection;

  if (currentPointer >= ledsCount) {
    currentPointer = ledsCount - 2;
    ledDirection = -1;
  }
  else if (currentPointer < 0) {
    currentPointer = 1;
    ledDirection = 1;
  }
}

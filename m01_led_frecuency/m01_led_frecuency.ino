#define BLINKER_LED 14

#define UP_BUTTON 15
#define DOWN_BUTTON 4

#define BACKWARD 2

#define STACK_SIZE 25

int operation_stack[STACK_SIZE];
int stack_pointer = 0;

unsigned long min_period = 10000;
unsigned long max_period = 1000000;

int last_up_state = LOW;
int last_down_state = LOW;
int last_back_state = LOW;

unsigned long led_period, upper_bound, lower_bound;


void setup() {

  Serial.begin(115200);
  
  pinMode(BLINKER_LED, OUTPUT);
  pinMode(UP_BUTTON, INPUT);
  pinMode(DOWN_BUTTON, INPUT);
  pinMode(BACKWARD, INPUT);

  led_period = (max_period + min_period) / 2;
  upper_bound = max_period;
  lower_bound = min_period;

}

void push_operation(int operation) {
  if (stack_pointer < STACK_SIZE) {
    operation_stack[stack_pointer] = operation;
    stack_pointer++;
  }
}

void step_up_frequency() {
  
  upper_bound = led_period;
  unsigned long new_period = (led_period + lower_bound) / 2;
  led_period = new_period;

  Serial.print("Faster: ");
  Serial.println(led_period);

  push_operation(1);
}

void step_down_frequency() {
  
  lower_bound = led_period;
  unsigned long new_period = (led_period + upper_bound) / 2;
  led_period = new_period;

  Serial.print("Slow Down: ");
  Serial.println(led_period);

  push_operation(-1);
}

void back_step() {

  if (stack_pointer == 0)
    return;

  stack_pointer--;

  int last_operation = operation_stack[stack_pointer];

  if (last_operation == 1) {
    led_period = upper_bound;
    upper_bound += upper_bound - lower_bound;
  }

  else if (last_operation == -1) {
    led_period = lower_bound;
    lower_bound += lower_bound - upper_bound;
  }

  Serial.print("Going backward: ");
  Serial.print(lower_bound);
  Serial.print(" --> ");
  Serial.print(led_period);
  Serial.print(" <-- ");
  Serial.println(upper_bound);
}

void delay_us(unsigned long us) {
  delay(us / 1000);
  delayMicroseconds(us % 1000);
}

void loop() {

  int up_state = digitalRead(UP_BUTTON);
  int down_state = digitalRead(DOWN_BUTTON);
  int back_state = digitalRead(BACKWARD);
  
  if (up_state == HIGH && last_up_state == LOW) {
    step_up_frequency();
  }
  else if (down_state == HIGH && last_down_state == LOW) {
    step_down_frequency();
  }
  else if (back_state == HIGH && last_back_state == LOW) {
    back_step();
  }
    
  last_up_state = up_state;
  last_down_state = down_state;
  last_back_state = back_state;
  
  digitalWrite(BLINKER_LED, HIGH);
  delay_us(led_period / 2);

  digitalWrite(BLINKER_LED, LOW);
  delay_us(led_period / 2);
  
}

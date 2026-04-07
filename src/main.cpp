#include <Arduino.h>
#define BUTTON_PIN 4


void Play(int mode);

int current_mode = 1;
const int max_modes = 3;
unsigned long lastDebounceTime = 0;
unsigned long debounceDelay = 50;
bool lastButtonState = HIGH;


int LED_PINS[8] = {13, 12, 14, 27, 26, 25, 33, 32};
int num_leds = sizeof(LED_PINS) / sizeof(LED_PINS[0]);



void setup() {
  pinMode(BUTTON_PIN, INPUT_PULLUP);
  for(int i = 0; i < num_leds; i++){
    pinMode(LED_PINS[i], OUTPUT);
  }
}

void checkButton(){
  bool reading = digitalRead(BUTTON_PIN);
  if(reading != lastButtonState){
    lastDebounceTime = millis();
  }
  if((millis() - lastDebounceTime) > debounceDelay){
    static bool button_state = HIGH;
    if(reading != button_state){
      button_state = reading;
      if(button_state == LOW){
        current_mode++;
        if(current_mode > max_modes){
          current_mode = 1;
        }
      }
    }
  }
  lastButtonState = reading;
}

void loop() {
  checkButton();
  Play(current_mode);
}

void Play(int mode){
  int start_mode = mode;
  switch (mode)
  {
    case 1:
      for (int i = 0; i < num_leds; i++)
      {
        if (current_mode != start_mode) return;
        digitalWrite(LED_PINS[i], HIGH);
        for(int d = 0; d < 25; d++) { 
          checkButton(); 
          delay(10); 
        }
      }
      for (int i = num_leds-1; i >= 0; i--)
      {
        if (current_mode != start_mode) return;
        digitalWrite(LED_PINS[i], LOW);
        for(int d = 0; d < 25; d++) { 
          checkButton(); 
          delay(10); 
        }
      }
      break;



    case 2:
    for (int i = 0; i < num_leds; i++)
    {
    if (current_mode != start_mode) return;
    digitalWrite(LED_PINS[i], HIGH);
    digitalWrite(LED_PINS[num_leds-i-1], HIGH);
    for(int d = 0; d < 25; d++) { 
          checkButton(); 
          delay(10); 
        }
    }
    for (int i = (num_leds-1)/2; i >= 0; i--)
    {
    if (current_mode != start_mode) return;
    digitalWrite(LED_PINS[i], LOW);
    digitalWrite(LED_PINS[num_leds-i-1], LOW);
    for(int d = 0; d < 25; d++) { 
          checkButton(); 
          delay(10); 
        }
    }
    break;

    case 3:
    for (int i = 0; i < num_leds; i++)
    {
      if (current_mode != start_mode) return;
      digitalWrite(LED_PINS[i], HIGH);
    }
    for(int d = 0; d < 25; d++) { 
          checkButton(); 
          delay(10); 
        }
    for(int i = 0; i < num_leds; i++)
    {
      if (current_mode != start_mode) return;
      digitalWrite(LED_PINS[i], LOW);
    }
    for(int d = 0; d < 25; d++) { 
          checkButton(); 
          delay(10); 
        }
    break;
  }
}

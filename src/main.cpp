#include <Arduino.h>
#include <Stepper.h>

#define STEPS 100
#define SPEED 300
#define LED1 8
#define LED2 9
#define LED3 10
#define LED4 11
#define LED5 12

// IN1, IN3, IN2, IN4
Stepper small_stepper(STEPS, 7, 5, 6, 4);

int stepsToTake = 0;
long temps = 0;

// will depend on a button state
bool isLEDsEnabled = false;

int counter;

void setup() {
  Serial.begin(9600);
  Serial.println("Test Motor; Test LEDs");
  pinMode(LED1, OUTPUT);
  pinMode(LED2, OUTPUT);
  pinMode(LED3, OUTPUT);
  pinMode(LED4, OUTPUT);
  pinMode(LED5, OUTPUT);
  delay(3000);
  digitalWrite(LED1, HIGH);
  digitalWrite(LED2, HIGH);
  digitalWrite(LED3, HIGH);
  digitalWrite(LED4, HIGH);
  digitalWrite(LED5, HIGH);
  delay(3000);
  digitalWrite(LED1, LOW);
  digitalWrite(LED2, LOW);
  digitalWrite(LED3, LOW);
  digitalWrite(LED4, LOW);
  digitalWrite(LED5, LOW);
}

void loop() {
  Serial.println(counter);
  small_stepper.setSpeed(SPEED);

  if (counter <= 20) {
    stepsToTake = -4096;
    // turn into funcion that accepts stepsToTake
    temps = millis();
    small_stepper.step(stepsToTake);
    temps = millis() - temps;
    Serial.println(temps);
    delay(2000);

    stepsToTake = 4096;
    temps = millis();
    small_stepper.step(stepsToTake);
    temps = millis() - temps;
    Serial.println(temps);
    delay(2000);

    if (isLEDsEnabled) {
      if (counter < 3) {
        digitalWrite(LED1, HIGH);
      } else if (counter == 3) {
        digitalWrite(LED2, HIGH);
      } else if (counter == 7) {
        digitalWrite(LED3, HIGH);
      } else if (counter == 11) {
        digitalWrite(LED4, HIGH);
      } else if (counter == 15) {
        digitalWrite(LED5, HIGH);
      }
    }
    
    delay(200);
    counter++;
  } else {
    int minutesElapsed = 0;
    digitalWrite(LED1, LOW);
    digitalWrite(LED2, LOW);
    digitalWrite(LED3, LOW);
    digitalWrite(LED4, LOW);
    digitalWrite(LED5, LOW);

    while (minutesElapsed <= 5) {
      delay(60000);

      if (isLEDsEnabled) {
        if (minutesElapsed == 1) {
          digitalWrite(LED1, HIGH);
        } else if (minutesElapsed == 2) {
            digitalWrite(LED2, HIGH);
        } else if (minutesElapsed == 3) {
            digitalWrite(LED3, HIGH);
        } else if (minutesElapsed == 4) {
            digitalWrite(LED4, HIGH);
        } else if (minutesElapsed == 5) {
            digitalWrite(LED5, HIGH);
        }
      }

      minutesElapsed++;
    }

    digitalWrite(LED1, LOW);
    digitalWrite(LED2, LOW);
    digitalWrite(LED3, LOW);
    digitalWrite(LED4, LOW);
    digitalWrite(LED5, LOW);
    counter = 0;
  }
}
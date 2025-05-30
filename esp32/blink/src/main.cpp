#include <Arduino.h>

#define LED_PIN 2  // On many ESP32 boards, GPIO 2 is the built-in LED

void setup() {
  pinMode(LED_PIN, OUTPUT);
}

void loop() {
  digitalWrite(LED_PIN, HIGH);  // Turn LED on
  delay(1000);                  // Wait 1 second
  digitalWrite(LED_PIN, LOW);   // Turn LED off
  delay(1000);                  // Wait 1 second
}

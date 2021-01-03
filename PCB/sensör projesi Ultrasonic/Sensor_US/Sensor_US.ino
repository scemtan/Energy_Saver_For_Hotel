#include <NewPing.h>
#define OUT 2
#define TRIGGER_PIN 3
#define ECHO_PIN 4
#define RX 0
#define MAX_DISTANCE 200
NewPing sonar(TRIGGER_PIN, ECHO_PIN, MAX_DISTANCE);
float distance;
void setup() {
  //pingTimer = millis();
  pinMode(OUT, OUTPUT);
  digitalWrite(OUT, LOW);
}
void loop() {
  distance = sonar.ping_cm();
  if (distance >= 50 || distance <= 2) 
  {
  }
  else 
  {
    digitalWrite(OUT, HIGH);
    delay(100);
    digitalWrite(OUT, LOW);
  }
  delay(500);
}

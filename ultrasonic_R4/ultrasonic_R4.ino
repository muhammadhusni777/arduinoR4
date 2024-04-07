uint8_t frame[8][12] = {
  { 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0 },
  { 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0 },
  { 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0 },
  { 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0 },
  { 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0 },
  { 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0 },
  { 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0 },
  { 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0 }
};

#include <ArduinoR4DigitDisplay.h>

#include "Arduino_LED_Matrix.h"

ArduinoLEDMatrix matrix;


const int trigPin = 6;
const int echoPin = 7;

unsigned long timer;
unsigned long timer_prev;

float duration;

int distance;
int distance_prev;

void clear_frame() {
  for (int row = 0; row < 8; row++) {
    for (int col = 0; col < 12; col++) {
      frame[row][col] = 0;
    }
  }
}

void setup() {
  pinMode(trigPin, OUTPUT);
  pinMode(echoPin, INPUT);
  Serial.begin(9600);
  matrix.begin();
  pinMode(8, OUTPUT);
}

void loop() {
  timer = millis() - timer_prev;
  if (timer > 500){
  digitalWrite(trigPin, LOW);
  delayMicroseconds(2);
  digitalWrite(trigPin, HIGH);
  delayMicroseconds(10);
  digitalWrite(trigPin, LOW);

  duration = pulseIn(echoPin, HIGH);
  distance = (duration*.0343)/2;
  Serial.print("Distance: ");
  Serial.println(distance);

  drawNumber(distance ,frame);
  matrix.renderBitmap(frame, 8, 12);

  if (distance != distance_prev){
    clear_frame();
    Serial.println("clear");
  }

  if (distance < 13){
    digitalWrite(8, HIGH);
  } else {
    digitalWrite(8, LOW);
  }

  distance_prev = distance;
  timer_prev = millis();
  }
}

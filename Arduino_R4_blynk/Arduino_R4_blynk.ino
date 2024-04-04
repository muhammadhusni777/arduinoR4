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

/* Comment this out to disable prints and save space */
#define BLYNK_PRINT Serial

/* Fill in information from Blynk Device Info here */
#define BLYNK_TEMPLATE_ID "TMPL6neSyoKz4"
#define BLYNK_TEMPLATE_NAME "ArduinoR4"
#define BLYNK_AUTH_TOKEN "0-S54gofntoxioABreYSw9uM3cnbFXp2"

#include <SPI.h>
#include <WiFiS3.h>
#include <BlynkSimpleWifi.h>

// Your WiFi credentials.
// Set password to "" for open networks.
char ssid[] = "Syergie Indo Prima";
char pass[] = "cahayaharapanhati";

BlynkTimer timer;

#include <ArduinoR4DigitDisplay.h>

#include "Arduino_LED_Matrix.h"

ArduinoLEDMatrix matrix;

int pinValue;
int led_status;

void clear_frame() {
  for (int row = 0; row < 8; row++) {
    for (int col = 0; col < 12; col++) {
      frame[row][col] = 0;
    }
  }
}

BLYNK_WRITE(V0){
  clear_frame();
  pinValue = param.asInt();
  drawNumber(pinValue ,frame);
  matrix.renderBitmap(frame, 8, 12);
  
}

BLYNK_WRITE(V3){
  led_status = param.asInt();  
  digitalWrite(13, led_status);
}

void sendSensor(){
  Blynk.virtualWrite(V1, random(0,100));
  Blynk.virtualWrite(V2, random(0,100));
}





void setup()
{
  // Debug console
  Serial.begin(9600);
  matrix.begin();
  pinMode(13, OUTPUT);

  Blynk.begin(BLYNK_AUTH_TOKEN, ssid, pass);
  // You can also specify server:
  //Blynk.begin(BLYNK_AUTH_TOKEN, ssid, pass, "blynk.cloud", 80);
  //Blynk.begin(BLYNK_AUTH_TOKEN, ssid, pass, IPAddress(192,168,1,100), 8080);

  timer.setInterval(1000L, sendSensor);

}

void loop()
{
  Blynk.run();
  timer.run();
  Serial.println(pinValue);
  delay(500);
}

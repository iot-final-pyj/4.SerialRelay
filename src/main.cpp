#include <Arduino.h>
#include <TFT_eSPI.h>
#include <SoftwareSerial.h>

SoftwareSerial swSer(21, 18);

TFT_eSPI tft = TFT_eSPI();

int i = 0;
char buf[200];
char c;
#define RELAY 2

void setup() {
    Serial.begin(115200);
    swSer.begin(9600);
    pinMode(RELAY, OUTPUT);
    tft.init();
    tft.setRotation(1);
    tft.fillScreen(TFT_BLACK);
    tft.setTextColor(TFT_WHITE);
    tft.drawString("Serial Controlled Relay", 30, 20, 4);
}

void loop() {
    if (swSer.available()) {
        c = swSer.read();
        if (c == '\n') {
            buf[i] = '\0';
            tft.fillRect(0, 60, 240, 240, TFT_BLACK);
            tft.drawString(buf, 90, 60, 4);
            i = 0;
            Serial.println(buf);
            if (!strncmp(buf, "on", 2)) {
                digitalWrite(RELAY, HIGH);
            } else if (!strncmp(buf, "off", 3)){
                digitalWrite(RELAY, LOW);
            } else {
                Serial.println("Invalid command");
            }
        } else {
            buf[i++] = c;
        }
    }
}
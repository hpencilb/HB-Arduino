#include <NTPClient.h>
// change next line to use with another board/shield
#include <ESP8266WiFi.h>
//#include <WiFi.h> // for WiFi shield
//#include <WiFi101.h> // for WiFi 101 shield or MKR1000
#include <WiFiUdp.h>
#include "wifi_info.h"

WiFiUDP ntpUDP;
NTPClient timeClient(ntpUDP, "ntp.aliyun.com", 8*3600, 60000);

void setup() {
  Serial.begin(115200);
  wifi_connect(); // in wifi_info.h
  timeClient.begin();
}

void loop() {
  timeClient.update();

  Serial.println(timeClient.getHours());
  Serial.println(timeClient.getMinutes());

  delay(1000);
}

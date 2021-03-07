#include <stdio.h>
#include <DS1302.h>

namespace {
  const int kCePin   = 7;  // Chip Enable // RST
  const int kIoPin   = 6;  // Input/Output // DAT
  const int kSclkPin = 5;  // Serial Clock // CLK
  DS1302 rtc(kCePin, kIoPin, kSclkPin);
  
  String dayAsString(const Time::Day day) {
    switch (day) {
      case Time::kSunday: return "Sunday";
      case Time::kMonday: return "Monday";
      case Time::kTuesday: return "Tuesday";
      case Time::kWednesday: return "Wednesday";
      case Time::kThursday: return "Thursday";
      case Time::kFriday: return "Friday";
      case Time::kSaturday: return "Saturday";
    }
    return "(unknown day)";
  }

  void printTime() {
    Time t = rtc.time();
//    const String day = dayAsString(t.day);
//    char buf[50];
//    snprintf(buf, sizeof(buf), "%s %04d-%02d-%02d %02d:%02d:%02d",
//             day.c_str(),
//             t.yr, t.mon, t.date,
//             t.hr, t.min, t.sec);
//    Serial.println(buf);
    Serial.println(t.day);
    Serial.println(t.yr);
    Serial.println(t.mon);
    Serial.println(t.date);
    Serial.println(t.hr);
    Serial.println(t.min);
    Serial.println(t.sec);
    Serial.println("========================");
  }
}

void setup() {
  Serial.begin(9600);
  Time t(2021, 3, 7, 22, 33, 00, Time::kSunday);
  set_time(t);
}

void loop() {
  printTime();
  delay(1000);
}

void set_time(Time t){
  rtc.writeProtect(false);
  rtc.halt(false);
  rtc.time(t);
}

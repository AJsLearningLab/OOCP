#include "Adafruit_Thermal.h"
#include "SoftwareSerial.h"
#include "Wire.h"
#include "RTClib.h"

#define TX_PIN 1
#define RX_PIN 3
#define btnPin1 5

SoftwareSerial mySerial(RX_PIN, TX_PIN);
Adafruit_Thermal printer(&mySerial);

RTC_DS3231 rtc;

int lastButtonState = HIGH; // Last known state of the button

void setup() {
  pinMode(4, OUTPUT);
  digitalWrite(4, LOW);
  pinMode(btnPin1, INPUT_PULLUP);

  mySerial.begin(9600);
  printer.begin();

  // Adjust the heating time (in microseconds) and interval (in microseconds)
  printer.setTimes(80, 10); // Default heatTime is 200, and heatInterval is 50

  if (!rtc.begin()) {
    printer.println("Couldn't find RTC");
    while (1);
  }

  DateTime now = rtc.now();
}

void loop() {
  DateTime now = rtc.now();
  int buttonState = digitalRead(btnPin1);

  if (buttonState != lastButtonState) {
    if (buttonState == LOW) {
      printer.feed(3); // Add a line feed
      printer.setSize('L');
      printer.justify('C');
      printer.println(F("EXIT-PASS"));
      printer.setSize('M');
      printer.justify('L');
      printer.print(F("Date: "));
      printer.print(now.day(), DEC);
      printer.print("/");
      printer.print(now.month(), DEC);

      char buffer[25];
      uint8_t min, hour;
      min = now.minute();
      hour = now.hour();
      printer.justify('L');
      sprintf(buffer, " Left at: %02u:%02u", hour, min);
      printer.println(buffer);
      printer.println(F("Valid 10 minutes."));
      printer.println(F("Thank you,"));
      printer.println(F("MR. PATRICK"));
      printer.feed(3); // Add a line feed
    }
    delay(50); // Add a short delay to debounce
  }

  lastButtonState = buttonState; // Update the last button state
}

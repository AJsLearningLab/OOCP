// Include necessary libraries for the thermal printer, serial communication, I2C communication, and the real-time clock (RTC)
#include "Adafruit_Thermal.h"
#include "SoftwareSerial.h"
#include "Wire.h"
#include "RTClib.h"

// Define pin connections for the thermal printer and button
#define TX_PIN 1
#define RX_PIN 3
#define btnPin1 5

// Create a SoftwareSerial object for communication with the thermal printer
SoftwareSerial mySerial(RX_PIN, TX_PIN);
// Create an Adafruit_Thermal object for controlling the thermal printer
Adafruit_Thermal printer(&mySerial);

// Create an RTC_DS3231 object for interfacing with the real-time clock module
RTC_DS3231 rtc;

// Initialize the last known button state to HIGH
int lastButtonState = HIGH;

// Setup function for configuring the hardware and initializing the printer and RTC
void setup() {
  pinMode(4, OUTPUT); // Set pin 4 as output
  digitalWrite(4, LOW); // Set pin 4 to low
  pinMode(btnPin1, INPUT_PULLUP); // Set btnPin1 (5) as an input with internal pullup resistor

  mySerial.begin(9600); // Start communication with the thermal printer at 9600 baud
  printer.begin(); // Initialize the thermal printer

  // Adjust the heating time (in microseconds) and interval (in microseconds)
  printer.setTimes(80, 10); // Default heatTime is 200, and heatInterval is 50

  // Check if the RTC module is available and initialized
  if (!rtc.begin()) {
    printer.println("Couldn't find RTC"); // Print error message if RTC is not found
    while (1); // Halt execution if RTC is not found
  }

  DateTime now = rtc.now(); // Get the current date and time from the RTC
}

// Main loop function that checks for button presses and prints the required information
void loop() {
  DateTime now = rtc.now(); // Get the current date and time from the RTC
  int buttonState = digitalRead(btnPin1); // Read the state of the button

  // Check if the button state has changed
  if (buttonState != lastButtonState) {
    // Check if the button is pressed (LOW state)
    if (buttonState == LOW) {
      printer.feed(3); // Add a line feed
      printer.setSize('L'); // Set the printer font size to large
      printer.justify('C'); // Center-align the text
      printer.println(F("EXIT-PASS")); // Print "EXIT-PASS"
      printer.setSize('M'); // Set the printer font size to medium
      printer.justify('L'); // Left-align the text
      printer.print(F("Date: ")); // Print "Date: "
      printer.print(now.day(), DEC); // Print the current day
      printer.print("/"); // Print "/"
      printer.print(now.month(), DEC); // Print the current month

      // Create a buffer to store the formatted time string
      char buffer[25];
      uint8_t min, hour;
      min = now.minute(); // Get the current minute
      hour = now.hour(); // Get the current hour
      printer.justify('L'); // Left-align the text
      sprintf(buffer, " Left at: %02u:%02u", hour, min); // Format the time string
      printer.println(buffer); // Print the time string
      printer.println(F("Valid 10 minutes.")); // Print "Valid 10 minutes."
      printer.println(F("Thank you,")); // Print "Thank you,"
      printer.println(F("MR. PATRICK")); // Print "MR. PATRICK"
      printer.feed(3); // Add a line feed to provide space between the printed text and the edge of the paper
    }
    delay(50); // Add a short delay (50 ms) to debounce the button to prevent false triggers
  }

  // Update the last button state with the current button state for the next iteration
  lastButtonState = buttonState;
}

# Exit Pass Printer

This project is an Arduino-based solution to print exit passes for students using a thermal printer and a real-time clock module. The system prints a pass containing the teacher's name, date, and time of exit, along with a validity period of 10 minutes.

## Features

- Prints exit passes with a single button press
- Utilizes a thermal printer for easy, low-cost printing
- Displays the date and time of exit on the pass
- Sets a validity period for the pass

## Hardware Requirements

- Arduino Nano or compatible board https://www.aliexpress.com/item/4000903444456.html?spm=a2g0o.order_list.order_list_main.5.79e41802RhLJ3d
- Thermal Printer with TTL interface https://www.aliexpress.com/item/32676222159.html?spm=a2g0o.order_list.order_list_main.567.79e41802RhLJ3d
- DS3231 Real-Time Clock (RTC) module https://www.aliexpress.com/item/32833136577.html?spm=a2g0o.productlist.main.1.5657755bKG8rpu&algo_pvid=05c4badc-dae3-4160-857f-38f3541599e4&algo_exp_id=05c4badc-dae3-4160-857f-38f3541599e4-0&pdp_npi=3%40dis%21AUD%212.59%212.59%21%21%21%21%21%40211be10916811607982508093d074a%2110000011431877724%21sea%21AU%21712299132&curPageLogUid=30xvz4SixwnI
- Momentary push button https://www.aliexpress.com/item/1005003628044406.html?spm=a2g0o.order_list.order_list_main.347.79e41802RhLJ3d
- Jumper wires and breadboard

## Software Dependencies

- [Adafruit_Thermal](https://github.com/adafruit/Adafruit-Thermal-Printer-Library) library
- [SoftwareSerial](https://www.arduino.cc/en/Reference/softwareSerial) library
- [Wire](https://www.arduino.cc/en/Reference/Wire) library
- [RTClib](https://github.com/adafruit/RTClib) library

## Circuit Diagram

Here's a simple textual description of the connections:

Arduino Uno <-> DS3231 RTC Module:

5V -> VCC
GND -> GND
A4 (SDA) -> SDA
A5 (SCL) -> SCL
Arduino Uno <-> Adafruit Thermal Printer:

Pin 1 (TX) -> RX
Pin 3 (RX) -> TX
GND -> GND
5V -> VCC
Pin 4 -> DTR
Arduino Uno <-> Momentary Push Button:

Pin 5 -> One leg of the button
GND -> The other leg of the button (use a 10kΩ resistor to connect the button leg to GND)

Make sure to use the appropriate power supply for your thermal printer. Some thermal printers may require a separate power supply with a higher current rating.

## Installation

1. Download and install the [Arduino IDE](https://www.arduino.cc/en/software).
2. Install the required libraries:
   - Go to `Sketch` -> `Include Library` -> `Manage Libraries`.
   - Search and install the following libraries:
     - Adafruit_Thermal
     - RTClib
3. Clone this repository or download the source code.
4. Open the source code in the Arduino IDE.
5. Connect your Arduino board to your computer.
6. Select the appropriate board and port in the Arduino IDE.
7. Upload the code to your Arduino board.

## Usage

- Press the button to print an exit pass.
- The exit pass will contain the teacher's name, date, and time of exit, along with a validity period of 10 minutes.

## Customization

You can customize the code to include additional information or change the format of the printed pass. Modify the relevant sections of the code to fit your requirements.

## License

This project is released under the MIT License. See [LICENSE](LICENSE) for more details.

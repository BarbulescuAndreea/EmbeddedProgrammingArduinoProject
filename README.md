This project constructs a Smart Locker system that utilizes a Bluetooth connection for unlocking via a mobile phone. The system includes an Arduino UNO microcontroller board connected to various components such as an LCD screen, LED, buzzer, electronic lock (solenoid), and a Bluetooth module (JDY-24M). Users can unlock the locker using a mobile app to send commands via Bluetooth to the Arduino. The system displays messages on the LCD screen based on the commands received, indicating whether the locker is opening, closing, or if there was an incorrect password entered. Additionally, it incorporates features such as timeout alarms for inactivity and feedback mechanisms like LED indicators and buzzer alerts. The project demonstrates the integration of hardware components and software functionalities to create a practical and customizable access control system.

Components needed

To run this code, you will need the following components:

An Arduino board (e.g., Arduino Uno)
A Bluetooth module (e.g., HC-05)
An LCD screen (e.g., LCD 16x2)
A LED
A buzzer
An electronic lock relay
Used libraries

The code uses two libraries:

LiquidCrystal.h: This library allows control of the LCD screen.
SoftwareSerial.h: This library allows communication through the Bluetooth module.
Pins and connections

The code defines the following connections between hardware components and Arduino pins:

Arduino Pin 2 is connected to the RS (Register Select) pin of the LCD screen.
Arduino Pin 3 is connected to the E (Enable) pin of the LCD screen.
Arduino Pin 4 is connected to the DB4 pin of the LCD screen.
Arduino Pin 5 is connected to the DB5 pin of the LCD screen.
Arduino Pin 6 is connected to the DB6 pin of the LCD screen.
Arduino Pin 7 is connected to the DB7 pin of the LCD screen.
Arduino Pin 8 is connected to the buzzer pin.
Arduino Pin 10 is connected to the RX (Receiver) pin of the Bluetooth module.
Arduino Pin 11 is connected to the TX (Transmitter) pin of the Bluetooth module.
Arduino Pin 13 is connected to the LED pin.
Arduino Pin A5 is connected to the electronic lock relay pin.
Initialization and configuration

In the setup() function, the following operations are performed:

The LED pin is set as an output using pinMode(ledPin, OUTPUT).
The LCD screen is initialized using lcd.begin(16, 2), specifying the number of columns (16) and rows (2).
The relay pin is set as an output, and the initial state of the electronic lock is set to LOW using pinMode(lockPin, OUTPUT) and digitalWrite(lockPin, LOW).
The buzzer pin is set as an output using pinMode(buzzerPin, OUTPUT).
Serial communication used for USB debugging is initialized at a baud rate of 9600 bits per second using Serial.begin(9600).
Serial communication with the Bluetooth module is initialized at a baud rate of 9600 bits per second using BTSerial.begin(9600).
A delay of 3 seconds is added to allow the Bluetooth module to initialize using delay(3000).
Main loop

The loop() function runs in a continuous loop and checks the Bluetooth connection status and received passwords. There are two major scenarios within the loop:

Checking for inactivity time:
It checks if a certain amount of time has passed (2 minutes in this case) since the last activity.
If the inactivity time has expired, a message is displayed on the LCD screen, and the buzzer is activated to alert the user.
After a certain period of time, the message is cleared from the LCD screen, and the buzzer is deactivated.
This check is performed to protect the system in case the user does not send any password for a long period of time.
Checking received passwords through Bluetooth:
It checks if there is data available through the Bluetooth module using BTSerial.available().
If data is available, it reads the sent password and stores it in the password variable.
If the password is correct (in this example, the correct password is "1777"), a message to open the locker is displayed on the LCD screen, and the electronic lock relay is activated for a period of time.
After a certain period of time, the locker automatically closes, a closing message is displayed on the LCD screen, and the electronic lock relay is deactivated.
If the password is incorrect, an error message is displayed on the LCD screen, and the buzzer is activated to alert the user.
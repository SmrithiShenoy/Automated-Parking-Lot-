# Car Parking System using Arduino Uno

Features:
- Detects cars in parking slots using IR sensors
- Measures car distance at the entrance using an ultrasonic sensor
- Opens gate using a servo motor when a slot is available
- Displays real-time slot status on a 16x2 LCD
- Outputs system status to Serial Monitor

Components:
- Arduino UNO
- 16x2 LCD with I2C
- 2 IR sensors
- Ultrasonic sensor 
- Servo motor 
- Jumper wires and breadboard

Connections:
- LCD uses 6 digital pins (RS, E, D4–D7)
- IR sensors and ultrasonic sensor connect to digital inputs
- Servo motor connects to a PWM-capable digital pin
- LCD contrast controlled using a potentiometer or resistor
- Backlight powered via 5V with a current-limiting resistor

Usage:
1. Connect components as described in the code comments.
2. Upload the Arduino sketch.
3. Power the board and observe the LCD and Serial Monitor.
4. The gate will open automatically when a car approaches and a slot is free.

License:
This project is released under the MIT License.

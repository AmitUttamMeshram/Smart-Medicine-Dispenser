# Smart Medicine Dispenser

A smart medicine dispenser built using *ESP32* that helps dispense medicines at scheduled times.  
This project uses an *RTC module* for real-time scheduling, *servo motors* for dispensing, an *I2C LCD* for display, an *HX711 load cell module* for weight checking, an *IR sensor* for medicine pickup detection, and a *buzzer* for alerts.

## Features

- Real-time medicine dispensing using *DS3231 RTC*
- *16x2 I2C LCD* to display system status and time
- *Servo motors* to control medicine compartments
- *HX711 + load cell* to monitor medicine weight
- *IR sensor* to detect whether medicine is picked up
- *Buzzer alert* for reminders
- Built and tested in *Wokwi simulator*

## Components Used

- ESP32
- DS3231 RTC module
- 16x2 I2C LCD
- HX711 load cell amplifier
- Load cell
- 3 Servo motors
- IR sensor
- Buzzer
- Jumper wires

## Circuit Overview

The ESP32 acts as the main controller and connects to:

- *LCD* via I2C
- **RTC DS323

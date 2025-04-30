# Pedestrian Light Control System

A simple pedestrian crossing light system implemented using embedded C on a microcontroller. The system simulates traffic and pedestrian lights, allowing safe pedestrian crossing using timed LED signaling.

## 🚦 Project Overview

This project simulates a pedestrian crossing system typically seen at traffic intersections. It includes:
- Red, Yellow, Green traffic lights for vehicles
- Red and Green pedestrian lights
- A pedestrian push button
- Timed light control logic ensuring safety and traffic flow

## 🛠️ Hardware Used

- Microcontroller: Texas Instruments MSP432P401R
- LEDs: 2x Red, 1x Yellow, 2x Green
- Push Button: 1x (Pedestrian Request)
- Breadboard and jumper wires
- Resistors 
- USB cable

## ⚙️ Software Requirements

- Embedded C or C++
- Microcontroller-specific libraries or drivers

## ⏱️ System Behavior

1. **Default State:**
   - Vehicle light: Green
   - Pedestrian light: Red

2. **When Pedestrian Button is Pressed:**
   - Vehicle Green → Yellow → Red
   - Pedestrian Red → Green
   - After 5-10 seconds (adjustable), pedestrian light turns Red again
   - Vehicle light returns to Green

3. **Debouncing & Safety:**
   - Button input is debounced in software

# Wokwi Calculator Project

A simple calculator simulation built in Wokwi using Arduino-style code.  
The project uses a keypad for input, an LCD for display, and separate modules for port handling, keypad scanning, LCD control, and arithmetic operations.

## Wokwi Project

Project Link: https://wokwi.com/projects/367157975952347137

## Main Files

- `sketch.ino` - Main program flow
- `diagram.json` - Wokwi circuit connection file
- `port.h / port.ino` - Port initialization and control
- `lcd.h / lcd.ino` - LCD display functions
- `keypad.h / keypad.ino` - Keypad input handling
- `operations.h / operations.ino` - Calculator operation logic

## Working Flow

1. Initialize ports and LCD.
2. Display welcome message.
3. Read input from keypad.
4. Split the entered expression.
5. Convert input characters into numbers.
6. Perform the selected arithmetic operation.
7. Display the result on LCD.

## Supported Operations

```text
Addition
Subtraction
Multiplication
Division
```

## How to Run

1. Open the Wokwi project link.
2. Start the simulation.
3. Use the keypad to enter the calculation.
4. View the result on the LCD.

## Note

This project is useful for learning keypad interfacing, LCD control, modular Arduino programming, and basic calculator logic in embedded systems.

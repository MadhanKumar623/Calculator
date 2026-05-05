# Calculator Projects

This repository contains two calculator implementations built for different learning purposes.

## 1. C Big Integer Calculator

A console-based calculator written in C for performing arithmetic on very large non-negative integers using string-based logic instead of built-in integer types.

### Features

- Supports addition, subtraction, multiplication, and division
- Handles large numbers such as 50-digit inputs
- Uses long-division logic for faster large-number division
- Useful for learning string handling, arithmetic algorithms, and C memory management

### Run

```bash
gcc -std=c99 -Wall -Wextra -Wpedantic big_integer_calculator_long_division.c -o calc
./calc
```

---

## 2. Wokwi Embedded Calculator

An embedded calculator simulation built in Wokwi using Arduino-style code using Register Level Programming.

### Features

- Keypad-based input
- LCD-based output
- Modular files for keypad, LCD, port handling, and operations
- Useful for learning embedded C, peripheral interfacing, and calculator logic

### Wokwi Project

https://wokwi.com/projects/367157975952347137

---

## Purpose

Both projects demonstrate calculator logic in two different environments:

- **C Calculator**: focuses on large-number arithmetic and algorithm implementation
- **Wokwi Calculator**: focuses on embedded-system simulation with keypad and LCD interfacing

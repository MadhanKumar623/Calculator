# Big Integer Calculator

A simple C-based calculator for performing arithmetic on very large positive integers using strings instead of built-in integer types.

## Versions Covered

- **Initial Code**: Basic big-integer calculator supporting addition, subtraction, multiplication, and division using string-based logic.
- **Latest Code**: Improved version with safer input handling, bug fixes, and faster long-division logic.

## Supported Operations

```text
+
-
*
/
```

Example input:

```text
Calc>12345678901234567890 + 98765432109876543210
Calc>100 / 50
Calc>12345 / 12
```

## Key Improvements in Latest Code

- Handles large numbers such as 50-digit inputs.
- Fixes unsafe input handling.
- Removes leading zeros correctly.
- Improves comparison and subtraction reliability.
- Replaces slow repeated-subtraction division with long division.

## Build

```bash
gcc -std=c99 -Wall -Wextra -Wpedantic big_integer_calculator_long_division.c -o calc
```

## Run

```bash
./calc
```

Type:

```text
Exit
```

to close the calculator.

## Note

This calculator is intended for non-negative integer arithmetic only.

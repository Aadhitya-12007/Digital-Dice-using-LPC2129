# Modular Digital Dice using LPC2129

![Language](https://img.shields.io/badge/Language-C-blue.svg)
![Hardware](https://img.shields.io/badge/Hardware-LPC2129_ARM7-orange.svg)
![Display](https://img.shields.io/badge/Display-16x2_LCD_with_CGRAM-brightgreen.svg)

A bare-metal, two-player digital dice game built on the **NXP LPC2129 (ARM7)** microcontroller. This project goes beyond basic text output by utilizing **Custom Character Generation (CGRAM)** to draw physical dice faces directly on a standard 16x2 Alphanumeric LCD.

It relies on Hardware Timers for pseudo-random number generation and the Vectored Interrupt Controller (VIC) to handle instantaneous player inputs.

## Key Features

* **Custom LCD Graphics:** Utilizes the HD44780's CGRAM to map and print real graphical dice faces (1 to 6 dots) on the LCD.
* **Hardware RNG:** Leverages the fast-running Timer 0 counter (`T0TC`) modulo 6 to generate a truly unpredictable pseudo-random dice roll.
* **Interrupt-Driven:** Uses External Interrupts (`EINT0` and `EINT1`) via the VIC for instant, non-blocking player inputs.
* **Modular Architecture:** The codebase is split into 5 distinct source/header files, demonstrating professional embedded software design principles.

## File Structure

This repository is organized into a clean, modular 5-file architecture (excluding this README) to separate hardware abstraction from application logic:

| File Name | Description |
| :--- | :--- |
| 📄 **`main.c`** | Contains the core application loop, Interrupt Service Routines (ISRs) for Players 1 & 2, and the CGRAM lookup tables for drawing the dice faces. |
| 📄 **`LCD_functions.c`** | The abstraction layer for the display. Handles LCD initialization, sending commands, writing raw data, and printing strings. |
| 📄 **`delay.c`** | Contains precise, hardware timer-based (Timer 0) delay functions used for LCD timing and debouncing. |
| 📄 **`UART_config.c`** | Handles UART initialization and configuration for serial debugging, logging, or future extensions. |
| 📄 **`Setup.h`** | The central header file linking the modules together. Contains necessary macros, port definitions, and function prototypes. |

## Hardware Setup & Wiring

* **Microcontroller:** LPC2129 (ARM7TDMI-S)
* **Display:** 16x2 HD44780 Compatible LCD
* **Player Inputs:** * **Player 1 Button:** Connected to `EINT0` (External Interrupt 0)
  * **Player 2 Button:** Connected to `EINT1` (External Interrupt 1)

*Note: Ensure the push buttons are properly pulled up/down based on your specific hardware configuration. The code sets `EXTPOLAR = 0x00` (Active Low).*

## How It Works?

1. On startup, the MCU initializes the LCD, configures the UART, sets up the fast-running Hardware Timer (RNG), and maps the External Interrupts.
2. The LCD displays the headers `P1:` and `P2:` waiting for user input.
3. When a player presses their respective button, the hardware triggers an interrupt.
4. Inside the ISR, the system captures the exact current microsecond value of the running timer (`T0TC`), performs a modulo 6 operation, and adds 1 to determine the dice value (1-6).
5. The main loop detects the flag set by the ISR, prints the numerical value, and calls the `CGRAM_print` function to draw the corresponding dotted dice face on the screen.

## Contributing

Contributions, issues, and feature requests are welcome! If you want to port this to another ARM architecture or add features like win-tracking via EEPROM, feel free to submit a pull request.

# ATmega32 MCU Drivers

## Overview

This repository hosts a collection of drivers for the ATmega32 microcontroller unit (MCU). These drivers are designed to simplify the process of interfacing various peripherals and components with the ATmega32 MCU, allowing developers to focus more on application logic rather than low-level hardware interaction.

## Supported Peripherals

The following peripherals are currently supported by the drivers in this repository:

1. **GPIO (General Purpose Input/Output)**

    - Provides functions for configuring and controlling GPIO pins.

2. **UART (Universal Asynchronous Receiver-Transmitter)**

    - Offers functions for UART communication, including initialization, transmission, and reception.

3. **SPI (Serial Peripheral Interface)**

    - Facilitates SPI communication with other devices using master or slave mode.

4. **Timers**

    - Provides timer functionality for various applications, including delay generation, PWM (Pulse Width Modulation), and timer interrupts.

5. **ADC (Analog-to-Digital Converter)**

    - Enables analog-to-digital conversion of input signals.

6. **Watchdog Timer**
    - Provides a mechanism for system reset in case of software or hardware failure by periodically resetting the microcontroller unless the software refreshes it.

## Getting Started

To get started using the drivers in your project, follow these steps:

1. **Clone the Repository**

2. **Include Headers:**

    - Copy the inc directory into your project's include path.
    - Include the necessary header files in your source files using #include "header.h".

3. **Link Source Files:**

    - Copy the src directory into your project's source directory.
    - Add the source files to your project's build system.

4. **Usage:**

    - Refer to the documentation and examples provided in the repository to understand how to use each driver.

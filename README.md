# Arduino Embedded Project - Spirit Phone

## Table of Contents

- [Overview](#overview)
- [Skills Demonstrated](#skills-demonstrated)
- [The Sculpture](#the-sculpture)
- [Components](#components)
- [Circuit Diagram](#circuit-diagram)

## Overview

This project showcases an embedded system using Arduino, which integrates hardware components to perform specific tasks for an Art sculpture in collaboration with [Regan Henley](https://www.reganhenley.com/). Specifically, the system reads sensor data to determine if the phone is on or off the hook. If the phone is off the hook, the microcontroller triggers a relay to power an AM/FM radio that plays through a speaker in the listening piece. If the phone is on the hook, the radio is turned off and the microcontroller triggers a relay to power a bell trembler. The bell ring pattern is defined by the ThreeRingBell function. The interval between rings is randomly generated between a set minimum and maximum number of seconds.

## Skills Demonstrated

- **C++ Programming:** The core logic is written in C++ using the Arduino framework, leveraging built-in functions and libraries for hardware communication.
- **Hardware Integration:** This project involves controlling and interacting with physical components:
  - A magnetic sensor.
  - A relay power on/off the radio.
  - A relay to power on/off the bell trembler.
  - A LED to indicate power status, and maintain a minimum current draw to keep a typical battery bank from shutting off.
- **Real-Time Processing:** The project handles real-time inputs and outputs, while storing data and instructions with limited memory and processing power.
- **Electrical Engineering:** Understanding and implementing circuit design, soldering, and power management.

## The Sculpture

![Spirit Phone](/assests/gallery.png)

![Inside](/assests/guts.png)

## Components

- **[Arduino Nano Every (Single Board)](https://www.amazon.com/gp/product/B07VX7MX27/ref=ppx_yo_dt_b_search_asin_image?ie=UTF8&th=1)**: The microcontroller board that runs the embedded code.
- **[HiLetgo NANO Expansion Board](https://www.amazon.com/gp/product/B073JGV87F/ref=ppx_yo_dt_b_search_asin_title?ie=UTF8&psc=1)**: Makes connecting to the Arduino Nano pins easier.
- **[4 Channel 5V Relay Module](https://www.amazon.com/gp/product/B08PP8HXVD/ref=ppx_yo_dt_b_search_asin_title?ie=UTF8&psc=1)**: To control the power to the radio and bell trembler.
- **[Magnetic Reed Switch (Normally Closed)](https://www.amazon.com/gp/product/B094XLXTYQ/ref=ppx_yo_dt_b_search_asin_image?ie=UTF8&psc=1)**: To detect if the phone is on or off the hook.
- **[Long Lead 5mm LED](https://www.amazon.com/gp/product/B0B5VG7QNY/ref=ppx_yo_dt_b_search_asin_title?ie=UTF8&psc=1)**: To indicate the power status of the system and maintain a minimum current draw.
- **[22 ohm Resistor](https://www.amazon.com/gp/product/B08FHPJ5G8/ref=ppx_yo_dt_b_search_asin_image?ie=UTF8&th=1)**: To limit the current to the LED.
- **[Bell Trembler](https://www.walmart.com/ip/SunSunrise-Electrical-Trembler-Bell-Model-Variety-Accessories-Hands-on-Activities-Educational-Tool-Science-Experiments-Aids-Kids/1287371649)**: Produces the bell ring sound.
- **[AM/FM Radio](https://www.amazon.com/gp/product/B07YH8V2KS/ref=ppx_yo_dt_b_search_asin_title?ie=UTF8&th=1)**: Bare bones radio, easily reconfigured for this project.
- **[Battery Banks](https://www.amazon.com/gp/product/B09QCXR8D4/ref=ppx_yo_dt_b_search_asin_title?ie=UTF8&th=1)**: To power the system and fit in a small space.

## Circuit Diagram

![Circuit Diagram](/assests/schematic.png)  
I'll be providing a more professional schematic soon. Keep in mind I'm self-taught in electronics.

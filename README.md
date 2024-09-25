# ATmega4808 Lab Exercises

Welcome to the ATmega4808 Lab Exercises repository! This repository contains a collection of lab exercises designed to help you learn and experiment with the ATmega4808 microcontroller using Microchip Studio. Each lab exercise covers different aspects of using the ATmega4808, from basic I/O operations to more advanced topics like ADC and timers.

## Table of Contents
  
- [Lab 1: Traffic lights](https://github.com/GrigorisTzortzakis/Atmega4808-lab-excersices/tree/main/Lab%201/Traffic%20lights)
- [Lab 2: ADC robotic sweeper](https://github.com/GrigorisTzortzakis/Atmega4808-lab-excersices/tree/main/Lab%202/Adc%20robotic%20sweeper)
- [Lab 3: Fan control](https://github.com/GrigorisTzortzakis/Atmega4808-lab-excersices/tree/main/Lab%203/Fan%20control)
- [Lab 4: Greenhouse](https://github.com/GrigorisTzortzakis/Atmega4808-lab-excersices/tree/main/Lab%204/Green%20house)

## Quick Setup

To run the lab exercises in this repository, follow these steps:

1. **Install Microchip Studio**  
   - Download it from [here](https://www.microchip.com/mplab/microchip-studio) and follow the installation prompts.

2. **Install MPLAB XC8 C Compiler**  
   - During installation, ensure **AVR** is selected as the target architecture.

3. **Create a New Project**  
   - In Microchip Studio, go to **File → New → Project** and select **GCC C Executable Project**.
   - Choose **ATmega4808** as your microcontroller.

4. **Import Code**  
   - Copy the code from this repository into your new project folder.

5. **Simulate and Debug**  
   - Set **Simulator** as the debugger in **Project Properties**.
   - Each time press f11 (step into) so each line is run by microchips studio.
   - Place breakpoints at each ISR by left clicking on the empty space next to it (a red dot should appear next to it).
   - Run the project using **Debug → Start Debugging**..
   - See the results of the registers changing by clicking Debug->Windows->I/O.
   - A red field means the value of the register just changed, blue means the value is 1 and no color means it is 0.
  
## Solutions

**For each lab, you can see the solutions here:**

- [Lab 1](https://github.com/GrigorisTzortzakis/Atmega4808-lab-excersices/tree/main/Lab%201/Traffic%20lights/Solutions)
- [Lab 2](https://github.com/GrigorisTzortzakis/Atmega4808-lab-excersices/tree/main/Lab%202/Adc%20robotic%20sweeper/Solutions)
- [Lab 3](https://github.com/GrigorisTzortzakis/Atmega4808-lab-excersices/tree/main/Lab%203/Fan%20control/Solutions)
- [Lab 4](https://github.com/GrigorisTzortzakis/Atmega4808-lab-excersices/tree/main/Lab%204/Green%20house/Solutions)

The format of the pictures is as follows:
- **1, 2, 3** refers to images for **Question 1**.
- For the next question, the first number represents the picture, followed by the number of the question.  
  For example, **3, 2** means picture 3 of question 2.


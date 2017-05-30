# Smart Window
For my 6.115 Final Project, I made a "Smart Window" that could automatically adjust its transparency or opacity based on user preferences -- imagine Flux or Transition Lenses for your window. The basic principle was to change the polarization angle between two polarized films to simulate different levels of opacity and transparency.

## User Modes
- <b>Manual mode</b>: user manually adjusts brightness levels
- <b>Automated mode</b>: user locks in desired brightness level; system automatically detects ambient light levels and adjusts window to maintain desired brightness level
- <b>Timed mode</b>: user inputs different desired brightness for different times of the day; system automatically adjusts brightness according to time of day, adjusting as needed with changing ambient light

## Hardware
- <b>Amulet</b>: used for user input, including selecting user mode and brightness level. Connected directly to PSoC over Rx/Tx lines. 
- <b>PSoC</b>: used for maintaining state machine and computing polarization angle. Inputs were Amulet and photoresistors; outputs were serial port connected to 8051. 
- <b>8051</b>: used to control servo motor via 8255 and LM293 chips.  Received PWM duty cycle over serial port from PSoC. PWM duty cycle controlled the position of the servo motor, which in turned changed the polarization angle of the window.  

## Software
- <b>Amulet files</b>: HTML file used for Amulet interface
- <b>8051 code</b>: 8051 assembly code for receiving PWM duty cycle over serial and sending PWM to 8255 chip. 
- <b>PSoC code</b>: C code for maintaining the state machine and updating the PWM duty cycle based on user inputs and photoresistor readings. 
- <b>Lasercutting files</b>: Corel designs for making the hardware setup. Some may not have been the final versions because I forgot to save them.

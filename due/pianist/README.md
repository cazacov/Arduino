# My Arduino Projects #

## Pianist ##
Pianist is a robot playing piano built from the old inkjet printer.

<img src="blob/master/_img/pianist.jpg?raw=true" alt="Robot playing piano" width="600" height="400"/>

Here is the old inkjet printer HP 1220 that I got donated from a friend:
<img src="https://github.com/cazacov/Arduino/blob/master/_img/deskjet1200c.jpg?raw=true" alt="Robot playing piano" width="600" height="400"/>

The first step was to remove unnecessary parts, leaving only the motorized frame with the printing head and encoder.
<img src="https://github.com/cazacov/Arduino/blob/master/_img/back.jpg?raw=true" alt="Robot playing piano" width="600" height="400"/>

Ink cartridges where removed and replaced with servo motors and fingers made from LEGO.
<img src="https://github.com/cazacov/Arduino/blob/master/_img/robohand.jpg?raw=true" alt="Robot playing piano" width="600" height="400"/>

All electronics mounted on the moving carriage was removed as well, leaving only the encoder sensor.
<img src="https://github.com/cazacov/Arduino/blob/master/_img/encoder.jpg?raw=true" alt="Robot playing piano" width="600" height="400"/>

Magnet on the bottom of the carriage is detected by a Hall sensor. That's how the robot knows where is the right-most position of the mechanical hand.

<img src="https://github.com/cazacov/Arduino/blob/master/_img/hall_sensor.jpg?raw=true" alt="Robot playing piano" width="600" height="400"/>

The carriage is moved by the DC motor. It's not a stepper motor, so some programming was required for exact positioning of the hand. A common PID controller was not precise enough and needed two/three correction runs to match the desired position. That's why after start the robot makes calibration movements and measures real deceleration speed of the carriage. Then this table is used for braking force calculation to stop the moving carriage exactly at the desired point.

<img src="https://github.com/cazacov/Arduino/blob/master/_img/motor_front.jpg?raw=true" alt="Robot playing piano" width="600" height="400"/>

<img src="https://github.com/cazacov/Arduino/blob/master/_img/motor_rear.jpg?raw=true" alt="Robot playing piano" width="600" height="400"/>

Arduino DUE microcontroller is the "brain" of the robot. DFRduino L298P shield is used to control the motor.

<img src="https://github.com/cazacov/Arduino/blob/master/_img/arduino_due.jpg?raw=true" alt="Robot playing piano" width="600" height="400"/>

For debugging purposes it's possible to control the microcomputer using a common PS/2 mouse. It was surprisingly easy to read mouse position and button state from the Arduino code.

16x2 text display is used as "poor man's debugger" to display technical information.

<img src="https://github.com/cazacov/Arduino/blob/master/_img/debugger.jpg?raw=true" alt="Robot playing piano" width="600" height="400"/>

Calculation of carriage speed and predicting its braking distance requires reading the X-coordinate from the encoder exactly 1000 times pro second. The reading code is attached to interrupt of one of the hardware timers built in into Arduino DUE. The easiest way to check the frequency and stability of interrupt calls was to flip signal on of the digital outputs and check it using an oscilloscope.

<img src="https://github.com/cazacov/Arduino/blob/master/_img/oscilloscope.jpg?raw=true" alt="Robot playing piano" width="600" height="400"/>









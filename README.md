# Gimbal
This device is a pan/tilt gimbal system that uses a herringbone gear power transmission. Actuation is provided by two NEMA 17-13 stepper motors driven by A4988 modules. 
The motion can be controlled by a joystick for which up/down controls the tilt and left/right controls the pan. 
A laser pointer is attached to provide a visual indicator for gimbal movement. In the future, it would be interesting to add a camera to allow computer vision tracking.
A 12V, 2A power adapter is used for the stepper motors, and power from the USB connection to a computer powers the Arduino board.

The system is Arduino-based and uses mainly 3D-printed parts that were modeled in CAD on Onshape.

![gimbal](https://github.com/kedsuzuki/Gimbal/assets/66259138/0bf965e0-66bd-4de3-a618-461d115ea433)
Fig 1. 2-axis Gimbal

![gimbal_circuit](https://github.com/kedsuzuki/Gimbal/assets/66259138/89bebbc7-38af-4c5f-83a9-f3457eec70b6)
Fig 2. Gimbal circuit schematic

## Hardware
* NEMA17-13 stepper motors
* Joystick
* A4988 drivers
* 12V 2.5A power adapter
* Arduino Mega
* 100uF electrolytic capacitors
* Joystick
* Radial ball bearing
* Thrust bearing
* M3 screws
* Jumper wires

## Resource Links
* AccelStepper Library: [https://github.com/adafruit/AccelStepper/blob/master/AccelStepper.h](url)
* AccelStepper extra info: [https://hackaday.io/project/183279-accelstepper-the-missing-manual/details](url)
* Gimbal system example: [http://www.trevorshp.com/creations/timelapse_panning.htm](url)

# NFC Readability tester

## Description
This hardware/software moves an NFC inlay (or an NFC Ring) over a mobile phone and locates where the NFC Antenna sweet spot is.  The co-ordinates are then stored in a database (in the format x,y,successOrFail[bool]) and can be used to identify how well a specific target device (such as a cell phone or tablet) will function with an NFC Ring.

## What problems does this solve?
Q. Does my [Insert one of a 3000 NFC handsets here] work with the NFC Ring?
A. We will be able to visually show which point each ring will work with the NFC Ring on the specific device.
Q. Where is the sweet spot on my phone?
A. See previous Answer.
Q. Where do I hold the NFC Ring to on my phone.
A. See previous, previous Answer.

## Requirements
* Laser cutter
* Arduino 
* 50x m6 nuts and bolts (Various thread sizes) (see pictures)
* Various cables (see pictures)
* Breadboard
* 2x stepper motors - 4218S-04
* 2x stepper motor controllers - http://www.schmalzhaus.com/EasyDriver/ v4.3+
* Threaded rod
* ATX PSU
* 2x Switch
* Arduino Ethernet Shield

## Instructions
* Laser cut the hardware using the files in "laser-cutting"
* Connect all the arduino stuff up and the motors. (See pictures for reference)
* Load up the source, change some variables (See top of source).
* Install NFC Ring App on device, select Scan QR Code.  Scan a QR Code that has http://nfcring.com/NFC-Sweet-Spot-Test encoded (You can encode this at http://nfcring.com/app).  Follow the on screen instructions.
* Power up the Hardware

## License
Apache 2

## Can I purchase one of these bad mofos pre-built?
For just $800 you can have one of these tools sat on your desk, drop john@mclear.co.uk an email if you want one.

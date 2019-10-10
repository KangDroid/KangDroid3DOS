KangDroid 3D Printer Firmware for RepRap 3D Printer / Raspberry-Pi
==================================================================

What is it?
------------
This is a firmware-like program based on Raspbery Pi. Currently, RepRap Marlin firmware uses HW base as Arduino - 2560, 1280, due, etc..<br/>
But this project, it will use Raspberry Pi as its base. There are pretty much more things to go, like Temperature Contorl and PWM Control, but in wip now.<br/>
This whole project is WIP, which means it could cause faulty result with unexpected error. Please report if any.

HW Specification for now(Currently focusing on)
-----------------------------------------------
M/B Base: Raspberry Pi 3(BCM2835 - Important)<br/>
Ramps: Normal RepRap Ramps 1.4(Mostly, any Ramps shield would be same. Check Pinmap once again if you are not using ramps 1.4)<br/>
The Printer: Self-Build COREXY RepRap Printer.(With TMC2208 Steppter)<br/>
ETC: Jumper wires, breadboard, etc..

PinMap
-------
Please refer to this link: https://reprap.org/wiki/File:RAMPS1.4schematic.png for more detailed wiring.

There are two ways to wire your printer with Raspberry pi.
1. Whether you edit source code in include/pins.h
2. OR you follow default setting.

In first case, you might want to wire your printer beautifully than me.(Cuz im working lazy :) )
For the second case, you might want to reference this;
(Warning: Raspberry pin number is based on wiringPI, not BCM GPIO NUMBERING!)

```
Ramps 1.4 PIN - Raspberry Pi PIN(wiringPi)

// External
Make sure you are putting 12V power supply to Ramps.(Normal way we set up ramps)

// Vin(TO RAMPS)/GND
5V(5V@1, 5V@2) - Any Raspberry 5V Pin
GND(GND@3, GND@4) - Any Raspberry GND Pin
# Make sure you are NOT PUTTING VOLTAGE IN RASPBERRY. YOU NEED TO PUT VOLTAGE ON RAMPS & MAKE SURE YOU ARE NOT SHORTING ANYTHING
# OTHERWISE YOU WILL LIKELY TO BREAK YOUR RPi


// Motors
X-STEP(A0) - 21
X-DIR(A1) - 23
Y-DIR(A7) - 30
Y-STEP(A6) - 22
Z-STEP(D46) - 5
Z_DIR(D48) - 4
X/Y/Z EN(D38, A2, A8) - 6

// Endstop
X-MIN(D3) - 3
Y-MIN(D14) - 0
Z-MIN(D18) - 2
```

Current Stepper Driver && steps_per_mm(SPM)
--------------------------------------
* Currently, I set up my printer with TMC2208. So Someone who are using A4988 or DRV might need to change Motor line wiring.(Test it first)

This program defines SPM like this;
```
X = 50
Y = 50
Z = 250
E = 1000
```

It is declared in pins.h (in include folder)

Disclaimer before build
------------
1. This program uses ROOT Permission due to BCM2835 CPU System Timer function(With Memory Mapping).
2. This program uses at LEAST 2 CPU Thread while moving motor && Load about 100% - so if you need fan, use it(im not using it for now tho)
3. This program is STILL Unstable - Cannot guarantee what will happen. <br/> Since we do not have any Heating function for now, it wouldn't cause catastrophy but still.

How to build?
-------------
1. Ensure you installed wiringPi Library and GCC/G++ on Raspberry Pi.<br/>
```
$ sudo apt-get install wiringpi gcc
```
2. Clone this project somewhere you want.(for me, I am using /home/pi)
```
$ cd ~/
$ git clone https://github.com/KangDroid/KangDroid3DOS -b wip_corexy
```
3. cd to project and build!
```
$ cd KangDroid3DOS (or cd /home/pi/KangDroid3DOS)
$ make clean && make -j4
```
4. RUN(MUST INCLUDE SUDO COMMAND. ROOT PERMISSION IS NEEDED TO RUN THIS PROJECT)
```
$ sudo ./app.out
```

Supported GCode Commands
-------------------------
1. G28(Excl. X, Y, Z Arguement)
2. G1(Incl.All Arguments like F, X, Y Z, E)
3. M18
4. M114
5. M119

EESchema Schematic File Version 2
LIBS:power
LIBS:device
LIBS:transistors
LIBS:conn
LIBS:linear
LIBS:regul
LIBS:74xx
LIBS:cmos4000
LIBS:adc-dac
LIBS:memory
LIBS:xilinx
LIBS:microcontrollers
LIBS:dsp
LIBS:microchip
LIBS:analog_switches
LIBS:motorola
LIBS:texas
LIBS:intel
LIBS:audio
LIBS:interface
LIBS:digital-audio
LIBS:philips
LIBS:display
LIBS:cypress
LIBS:siliconi
LIBS:opto
LIBS:atmel
LIBS:contrib
LIBS:valves
LIBS:LDD1500H
EELAYER 25 0
EELAYER END
$Descr A4 11693 8268
encoding utf-8
Sheet 1 1
Title ""
Date ""
Rev ""
Comp ""
Comment1 ""
Comment2 ""
Comment3 ""
Comment4 ""
$EndDescr
$Comp
L AM2302 U?
U 1 1 5AC2DA54
P 1400 1750
F 0 "U?" H 1150 2650 60  0000 C CNN
F 1 "AM2302" H 1150 2650 60  0000 C CNN
F 2 "" H 1150 2650 60  0000 C CNN
F 3 "" H 1150 2650 60  0000 C CNN
	1    1400 1750
	1    0    0    -1  
$EndComp
$Comp
L +5V #PWR?
U 1 1 5AC2DBA5
P 1400 800
F 0 "#PWR?" H 1400 650 50  0001 C CNN
F 1 "+5V" H 1400 940 50  0000 C CNN
F 2 "" H 1400 800 50  0000 C CNN
F 3 "" H 1400 800 50  0000 C CNN
	1    1400 800 
	1    0    0    -1  
$EndComp
$Comp
L GND #PWR?
U 1 1 5AC2DBBB
P 1400 1700
F 0 "#PWR?" H 1400 1450 50  0001 C CNN
F 1 "GND" H 1400 1550 50  0000 C CNN
F 2 "" H 1400 1700 50  0000 C CNN
F 3 "" H 1400 1700 50  0000 C CNN
	1    1400 1700
	1    0    0    -1  
$EndComp
Text HLabel 2450 1250 2    60   Output ~ 0
AM2302Out
Text Label 1900 1250 0    60   ~ 0
AM2302Out
Wire Wire Line
	1850 1250 2450 1250
Wire Wire Line
	1400 1650 1400 1700
Wire Wire Line
	1400 850  1400 800 
$EndSCHEMATC

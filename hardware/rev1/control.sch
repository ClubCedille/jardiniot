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
LIBS:ESP8266
LIBS:arduino
LIBS:control-cache
EELAYER 25 0
EELAYER END
$Descr A4 11693 8268
encoding utf-8
Sheet 1 1
Title "jardinIO circuit"
Date "2018-04-18"
Rev "0"
Comp "Cedille"
Comment1 ""
Comment2 ""
Comment3 ""
Comment4 ""
$EndDescr
$Comp
L Arduino_Uno_Shield XA3001
U 1 1 5AA1EDD2
P 2750 2000
F 0 "XA3001" V 2850 2000 60  0000 C CNN
F 1 "Arduino_Uno_Shield" V 2650 2000 60  0000 C CNN
F 2 "" H 4550 5750 60  0001 C CNN
F 3 "" H 4550 5750 60  0001 C CNN
	1    2750 2000
	1    0    0    -1  
$EndComp
$Comp
L GND #PWR01
U 1 1 5AA88684
P 750 2850
F 0 "#PWR01" H 750 2600 50  0001 C CNN
F 1 "GND" H 750 2700 50  0000 C CNN
F 2 "" H 750 2850 50  0000 C CNN
F 3 "" H 750 2850 50  0000 C CNN
	1    750  2850
	1    0    0    -1  
$EndComp
$Comp
L +3.3V #PWR02
U 1 1 5AA88986
P 1350 2450
F 0 "#PWR02" H 1350 2300 50  0001 C CNN
F 1 "+3.3V" H 1350 2590 50  0000 C CNN
F 2 "" H 1350 2450 50  0000 C CNN
F 3 "" H 1350 2450 50  0000 C CNN
	1    1350 2450
	1    0    0    -1  
$EndComp
$Comp
L +5V #PWR03
U 1 1 5AA8899E
P 1150 2450
F 0 "#PWR03" H 1150 2300 50  0001 C CNN
F 1 "+5V" H 1150 2590 50  0000 C CNN
F 2 "" H 1150 2450 50  0000 C CNN
F 3 "" H 1150 2450 50  0000 C CNN
	1    1150 2450
	1    0    0    -1  
$EndComp
$Comp
L adafruit_E218213_breakboard U3001
U 1 1 5AB05516
P 3250 3150
F 0 "U3001" H 5200 4950 60  0000 C CNN
F 1 "adafruit_E218213_breakboard" H 5700 5350 60  0000 C CNN
F 2 "" H 5700 5350 60  0000 C CNN
F 3 "" H 5700 5350 60  0000 C CNN
	1    3250 3150
	1    0    0    -1  
$EndComp
$Comp
L GND #PWR04
U 1 1 5AB0561B
P 5500 2950
F 0 "#PWR04" H 5500 2700 50  0001 C CNN
F 1 "GND" H 5500 2800 50  0000 C CNN
F 2 "" H 5500 2950 50  0000 C CNN
F 3 "" H 5500 2950 50  0000 C CNN
	1    5500 2950
	1    0    0    -1  
$EndComp
$Comp
L +5V #PWR05
U 1 1 5AB056CD
P 5700 1250
F 0 "#PWR05" H 5700 1100 50  0001 C CNN
F 1 "+5V" H 5700 1390 50  0000 C CNN
F 2 "" H 5700 1250 50  0000 C CNN
F 3 "" H 5700 1250 50  0000 C CNN
	1    5700 1250
	1    0    0    -1  
$EndComp
Entry Wire Line
	4750 3300 4850 3400
Entry Wire Line
	4800 3300 4900 3400
Entry Wire Line
	4850 3300 4950 3400
Entry Wire Line
	4900 3200 5000 3300
Entry Wire Line
	4950 3200 5050 3300
Text Label 5350 3300 0    60   ~ 0
fanConn[1..2]
Text HLabel 6400 3300 2    60   Output ~ 0
fanConn[1..2]
Text HLabel 4050 750  0    60   Input ~ 0
humidityData
Text Label 4600 1250 2    60   ~ 0
fanConn1
Text Label 4550 1350 2    60   ~ 0
fanConn2
Text Label 4550 1650 2    60   ~ 0
LEDConn1
Text Label 4550 1750 2    60   ~ 0
LEDConn2
Text Label 4550 1850 2    60   ~ 0
LEDConn3
Text HLabel 6400 3400 2    60   Output ~ 0
LEDConn[1..3]
Text Label 5950 3400 2    60   ~ 0
LEDConn[1..3]
$Comp
L +12V #PWR06
U 1 1 5AD6AFCF
P 950 2450
F 0 "#PWR06" H 950 2300 50  0001 C CNN
F 1 "+12V" H 950 2590 50  0000 C CNN
F 2 "" H 950 2450 50  0000 C CNN
F 3 "" H 950 2450 50  0000 C CNN
	1    950  2450
	1    0    0    -1  
$EndComp
Wire Wire Line
	1150 2450 1150 2950
Wire Wire Line
	1150 2950 1450 2950
Wire Wire Line
	5900 2850 5900 2900
Wire Wire Line
	5900 2900 5500 2900
Wire Wire Line
	5500 2850 5500 2950
Connection ~ 5500 2900
Wire Wire Line
	5800 2850 5800 2900
Connection ~ 5800 2900
Wire Wire Line
	5700 1300 5700 1250
Wire Wire Line
	4050 1150 5050 1150
Wire Wire Line
	4050 1050 5000 1050
Wire Wire Line
	6250 3150 6250 2250
Wire Wire Line
	6250 2250 6200 2250
Wire Wire Line
	5100 2250 5050 2250
Wire Wire Line
	5050 2250 5050 1150
Wire Wire Line
	5000 1050 5000 3150
Wire Wire Line
	5000 3150 6250 3150
Wire Wire Line
	4950 1250 4950 3200
Wire Wire Line
	4050 1350 4900 1350
Wire Wire Line
	4900 1350 4900 3200
Wire Wire Line
	4050 1650 4850 1650
Wire Wire Line
	4850 1650 4850 3300
Wire Wire Line
	4050 1750 4800 1750
Wire Wire Line
	4800 1750 4800 3300
Wire Wire Line
	4050 1850 4750 1850
Wire Wire Line
	4750 1850 4750 3300
Wire Bus Line
	5000 3300 6400 3300
Wire Bus Line
	4850 3400 6400 3400
NoConn ~ 5500 1300
NoConn ~ 5600 1300
NoConn ~ 5800 1300
NoConn ~ 6200 1650
NoConn ~ 6200 1750
NoConn ~ 6200 1850
NoConn ~ 6200 1950
NoConn ~ 6200 2050
NoConn ~ 6200 2150
NoConn ~ 5100 2350
NoConn ~ 5100 2150
NoConn ~ 5100 2050
NoConn ~ 5100 1950
NoConn ~ 5100 1850
NoConn ~ 5100 1750
NoConn ~ 5100 1650
NoConn ~ 5100 1550
NoConn ~ 6200 2350
NoConn ~ 5700 2850
NoConn ~ 5600 2850
NoConn ~ 4050 1450
NoConn ~ 4050 1550
NoConn ~ 4050 1950
NoConn ~ 4050 2050
NoConn ~ 4050 2250
NoConn ~ 4050 2350
NoConn ~ 4050 2450
NoConn ~ 4050 2550
NoConn ~ 4050 2650
NoConn ~ 4050 2750
NoConn ~ 4050 2950
NoConn ~ 4050 3050
NoConn ~ 1450 2250
NoConn ~ 1450 2150
NoConn ~ 1450 2050
NoConn ~ 1450 1950
NoConn ~ 1450 1850
NoConn ~ 1450 1750
NoConn ~ 1450 1650
NoConn ~ 1450 1350
NoConn ~ 1450 1250
NoConn ~ 1450 1050
NoConn ~ 1450 950 
Wire Wire Line
	4950 1250 4050 1250
Wire Wire Line
	1450 2850 1350 2850
Wire Wire Line
	1350 2850 1350 2450
Wire Wire Line
	1450 2750 750  2750
Wire Wire Line
	750  2550 750  2850
Wire Wire Line
	1450 2650 750  2650
Connection ~ 750  2750
Wire Wire Line
	1450 2550 750  2550
Connection ~ 750  2650
Wire Wire Line
	1450 3050 950  3050
Wire Wire Line
	950  3050 950  2450
Wire Wire Line
	4050 950  4100 950 
Wire Wire Line
	4100 950  4100 750 
Wire Wire Line
	4100 750  4050 750 
$EndSCHEMATC

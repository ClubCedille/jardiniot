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
LIBS:arduino
LIBS:ESP8266
LIBS:LDD1500H
LIBS:jardinio-cache
EELAYER 25 0
EELAYER END
$Descr A4 11693 8268
encoding utf-8
Sheet 1 5
Title "jardinIO circuit"
Date "2018-04-18"
Rev "0"
Comp "Cedille"
Comment1 ""
Comment2 ""
Comment3 ""
Comment4 ""
$EndDescr
$Sheet
S 750  5050 1400 1250
U 5AA12C59
F0 "power" 60
F1 "power.sch" 60
$EndSheet
$Sheet
S 3350 850  1200 3050
U 5AA1E97C
F0 "control" 60
F1 "control.sch" 60
F2 "humidityData" I L 3350 1050 60 
F3 "LEDConn[1..3]" O R 4550 1250 60 
F4 "fanConn[1..2]" O R 4550 1150 60 
$EndSheet
$Sheet
S 900  750  1050 3250
U 5AA1E9E6
F0 "sensors" 60
F1 "sensors.sch" 60
F2 "AM2302Out" O R 1950 1150 60 
$EndSheet
$Sheet
S 6250 800  1200 3150
U 5AA1EA5F
F0 "outputs" 60
F1 "outputs.sch" 60
F2 "LEDConn[1..3]" I L 6250 1250 60 
F3 "fanConn[1..2]" I L 6250 1150 60 
$EndSheet
Wire Wire Line
	6250 1150 4550 1150
Wire Wire Line
	6250 1250 4550 1250
Wire Wire Line
	3350 1050 2650 1050
Wire Wire Line
	2650 1050 2650 1150
Wire Wire Line
	2650 1150 1950 1150
$EndSCHEMATC

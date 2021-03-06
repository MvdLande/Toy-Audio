EESchema Schematic File Version 2
LIBS:Mylib VDL
LIBS:MCU
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
LIBS:Toy-Audio-cache
EELAYER 25 0
EELAYER END
$Descr A4 11693 8268
encoding utf-8
Sheet 1 1
Title "Toy Audio V1"
Date "2016-01-06"
Rev "A"
Comp "Maurits van de Lande (maurits@vandelande.com)"
Comment1 ""
Comment2 ""
Comment3 ""
Comment4 ""
$EndDescr
Text Notes 1250 3150 0    60   ~ 0
STLink SWD Interface
Text Label 6800 2450 0    60   ~ 0
SCL1
Text Label 6800 2350 0    60   ~ 0
SDA1
$Comp
L CONN_2 J1
U 1 1 548FBD4C
P 900 5050
F 0 "J1" H 800 5250 40  0000 C CNN
F 1 "CONN_2" V 950 5050 40  0001 C CNN
F 2 "MvdL:JST-PH-2P-DUAL" H 900 5050 60  0001 C CNN
F 3 "~" H 900 5050 60  0000 C CNN
	1    900  5050
	-1   0    0    -1  
$EndComp
$Comp
L SCHOTTKY D1
U 1 1 548FBF10
P 1850 5150
F 0 "D1" V 1950 5000 60  0000 C CNN
F 1 "MBR0520LT1G" V 1750 5150 60  0000 C CNN
F 2 "MvdL:SOD-123" H 1850 5150 60  0001 C CNN
F 3 "~" H 1850 5150 60  0000 C CNN
	1    1850 5150
	0    -1   -1   0   
$EndComp
$Comp
L W25Q128FVSIG U3
U 1 1 548FE3C4
P 6250 4550
F 0 "U3" H 6250 4950 60  0000 C CNN
F 1 "W25Q32FVSIG" H 6300 4350 60  0000 C CNN
F 2 "MvdL:SOIC-8-208mil" H 6250 4550 60  0001 C CNN
F 3 "~" H 6250 4550 60  0000 C CNN
	1    6250 4550
	1    0    0    -1  
$EndComp
Text Label 5450 4300 0    60   ~ 0
nCS
Text Notes 900  4675 0    60   ~ 0
Battery Power
Text Label 1050 3750 0    60   ~ 0
SWCLK
Text Label 1050 3850 0    60   ~ 0
SWDIO
Text Label 5450 4500 0    60   ~ 0
MOSI1
Text Label 5450 4600 0    60   ~ 0
SCK1
$Comp
L XC6206P332MR U1
U 1 1 55C87310
P 3100 5100
F 0 "U1" H 3200 5150 60  0000 C CNN
F 1 "XC6206P282MR" H 3100 5450 60  0000 C CNN
F 2 "MvdL:SOT23" H 3100 5050 60  0001 C CNN
F 3 "" H 3100 5050 60  0000 C CNN
	1    3100 5100
	1    0    0    -1  
$EndComp
$Comp
L VDD #PWR10
U 1 1 55C87E0C
P 3700 4800
F 0 "#PWR10" H 3700 4650 50  0001 C CNN
F 1 "VDD" H 3700 4950 50  0000 C CNN
F 2 "" H 3700 4800 60  0000 C CNN
F 3 "" H 3700 4800 60  0000 C CNN
	1    3700 4800
	1    0    0    -1  
$EndComp
$Comp
L CC C7
U 1 1 55D300C8
P 5050 4600
F 0 "C7" H 5050 4700 40  0000 L CNN
F 1 "10u" H 5056 4515 40  0000 L CNN
F 2 "MvdL:C0603" H 5088 4450 30  0001 C CNN
F 3 "" H 5050 4600 60  0000 C CNN
	1    5050 4600
	1    0    0    -1  
$EndComp
$Comp
L VDD #PWR13
U 1 1 55D300D4
P 5050 4400
F 0 "#PWR13" H 5050 4250 50  0001 C CNN
F 1 "VDD" H 5050 4550 50  0000 C CNN
F 2 "" H 5050 4400 60  0000 C CNN
F 3 "" H 5050 4400 60  0000 C CNN
	1    5050 4400
	1    0    0    -1  
$EndComp
Text Label 5450 4400 0    60   ~ 0
MISO1
$Comp
L VCC #PWR6
U 1 1 55DE7341
P 2500 4800
F 0 "#PWR6" H 2500 4650 50  0001 C CNN
F 1 "VCC" H 2500 4950 50  0000 C CNN
F 2 "" H 2500 4800 60  0000 C CNN
F 3 "" H 2500 4800 60  0000 C CNN
	1    2500 4800
	1    0    0    -1  
$EndComp
$Comp
L VDD #PWR18
U 1 1 55DE7A85
P 6800 4200
F 0 "#PWR18" H 6800 4050 50  0001 C CNN
F 1 "VDD" H 6800 4350 50  0000 C CNN
F 2 "" H 6800 4200 60  0000 C CNN
F 3 "" H 6800 4200 60  0000 C CNN
	1    6800 4200
	1    0    0    -1  
$EndComp
$Comp
L GND #PWR3
U 1 1 55DEC140
P 1400 3950
F 0 "#PWR3" H 1400 3700 50  0001 C CNN
F 1 "GND" H 1400 3800 50  0000 C CNN
F 2 "" H 1400 3950 60  0000 C CNN
F 3 "" H 1400 3950 60  0000 C CNN
	1    1400 3950
	1    0    0    -1  
$EndComp
$Comp
L GND #PWR1
U 1 1 55DEC4CC
P 1450 5300
F 0 "#PWR1" H 1450 5050 50  0001 C CNN
F 1 "GND" H 1450 5150 50  0000 C CNN
F 2 "" H 1450 5300 60  0000 C CNN
F 3 "" H 1450 5300 60  0000 C CNN
	1    1450 5300
	1    0    0    -1  
$EndComp
$Comp
L GND #PWR7
U 1 1 55DEC5A9
P 2500 5300
F 0 "#PWR7" H 2500 5050 50  0001 C CNN
F 1 "GND" H 2500 5150 50  0000 C CNN
F 2 "" H 2500 5300 60  0000 C CNN
F 3 "" H 2500 5300 60  0000 C CNN
	1    2500 5300
	1    0    0    -1  
$EndComp
$Comp
L GND #PWR9
U 1 1 55DEC686
P 3100 5300
F 0 "#PWR9" H 3100 5050 50  0001 C CNN
F 1 "GND" H 3100 5150 50  0000 C CNN
F 2 "" H 3100 5300 60  0000 C CNN
F 3 "" H 3100 5300 60  0000 C CNN
	1    3100 5300
	1    0    0    -1  
$EndComp
$Comp
L GND #PWR11
U 1 1 55DEC763
P 3700 5300
F 0 "#PWR11" H 3700 5050 50  0001 C CNN
F 1 "GND" H 3700 5150 50  0000 C CNN
F 2 "" H 3700 5300 60  0000 C CNN
F 3 "" H 3700 5300 60  0000 C CNN
	1    3700 5300
	1    0    0    -1  
$EndComp
$Comp
L GND #PWR19
U 1 1 55DEE40F
P 6800 4800
F 0 "#PWR19" H 6800 4550 50  0001 C CNN
F 1 "GND" H 6800 4650 50  0000 C CNN
F 2 "" H 6800 4800 60  0000 C CNN
F 3 "" H 6800 4800 60  0000 C CNN
	1    6800 4800
	1    0    0    -1  
$EndComp
$Comp
L GND #PWR14
U 1 1 55DEE754
P 5050 4800
F 0 "#PWR14" H 5050 4550 50  0001 C CNN
F 1 "GND" H 5050 4650 50  0000 C CNN
F 2 "" H 5050 4800 60  0000 C CNN
F 3 "" H 5050 4800 60  0000 C CNN
	1    5050 4800
	1    0    0    -1  
$EndComp
Text Label 6800 2150 0    60   ~ 0
USART1_TX
Text Label 6800 2050 0    60   ~ 0
USART1_RX
Text Label 6800 1950 0    60   ~ 0
USART1_CK
Text Label 6800 1750 0    60   ~ 0
UART1_EN
$Comp
L GND #PWR21
U 1 1 55E01A86
P 7500 2550
F 0 "#PWR21" H 7500 2300 50  0001 C CNN
F 1 "GND" H 7500 2400 50  0000 C CNN
F 2 "" H 7500 2550 60  0000 C CNN
F 3 "" H 7500 2550 60  0000 C CNN
	1    7500 2550
	1    0    0    -1  
$EndComp
$Comp
L VDD #PWR20
U 1 1 55E01CC1
P 7400 1550
F 0 "#PWR20" H 7400 1400 50  0001 C CNN
F 1 "VDD" H 7400 1700 50  0000 C CNN
F 2 "" H 7400 1550 60  0000 C CNN
F 3 "" H 7400 1550 60  0000 C CNN
	1    7400 1550
	1    0    0    -1  
$EndComp
Text Notes 7000 2950 0    60   ~ 0
nRF24L01 interface\n+I2C
$Comp
L SPEAKER SP1
U 1 1 55EC5935
P 10000 3600
F 0 "SP1" H 9800 3900 60  0000 C CNN
F 1 "8Ohm" H 9800 3300 60  0000 C CNN
F 2 "MvdL:JST-PH-2P-DUAL" H 10000 3600 60  0001 C CNN
F 3 "~" H 10000 3600 60  0000 C CNN
	1    10000 3600
	1    0    0    -1  
$EndComp
$Comp
L Si2302DS Q1
U 1 1 55EC5956
P 9100 4050
F 0 "Q1" H 9050 3900 40  0000 R CNN
F 1 "Si2302DS" H 9100 4200 40  0000 R CNN
F 2 "MvdL:SOT23" H 8970 4152 29  0001 C CNN
F 3 "" H 9100 4050 60  0000 C CNN
	1    9100 4050
	1    0    0    -1  
$EndComp
$Comp
L GND #PWR23
U 1 1 55EC595D
P 9200 4350
F 0 "#PWR23" H 9200 4100 50  0001 C CNN
F 1 "GND" H 9200 4200 50  0000 C CNN
F 2 "" H 9200 4350 60  0000 C CNN
F 3 "" H 9200 4350 60  0000 C CNN
	1    9200 4350
	1    0    0    -1  
$EndComp
Text HLabel 8800 4100 0    60   Input ~ 0
PWM
$Comp
L RR R3
U 1 1 55EC5964
P 9200 3100
F 0 "R3" V 9280 3100 50  0000 C CNN
F 1 "d.n.p." V 9125 3100 50  0000 C CNN
F 2 "MvdL:R0603" H 9200 3100 60  0001 C CNN
F 3 "" H 9200 3100 60  0000 C CNN
	1    9200 3100
	-1   0    0    1   
$EndComp
$Comp
L CC C10
U 1 1 55EC5971
P 10350 3600
F 0 "C10" H 10350 3700 40  0000 L CNN
F 1 "d.n.p." H 10356 3515 40  0000 L CNN
F 2 "MvdL:C0603" H 10388 3450 30  0001 C CNN
F 3 "~" H 10350 3600 60  0000 C CNN
	1    10350 3600
	1    0    0    -1  
$EndComp
$Comp
L GND #PWR25
U 1 1 55EC5978
P 10350 3850
F 0 "#PWR25" H 10350 3600 50  0001 C CNN
F 1 "GND" H 10350 3700 50  0000 C CNN
F 2 "" H 10350 3850 60  0000 C CNN
F 3 "" H 10350 3850 60  0000 C CNN
	1    10350 3850
	1    0    0    -1  
$EndComp
$Comp
L CC C8
U 1 1 55EC5984
P 9200 3600
F 0 "C8" H 9200 3700 40  0000 L CNN
F 1 "d.n.p" H 9206 3515 40  0000 L CNN
F 2 "MvdL:C0603" H 9238 3450 30  0001 C CNN
F 3 "~" H 9200 3600 60  0000 C CNN
	1    9200 3600
	1    0    0    -1  
$EndComp
$Comp
L STM32F030Fx U2
U 1 1 55EC69BE
P 4000 1600
F 0 "U2" H 4850 1750 60  0000 C CNN
F 1 "STM32F030F4P6" H 4850 550 60  0000 C CNN
F 2 "MvdL:TSSOP20" H 4200 2150 60  0001 C CNN
F 3 "" H 4050 2150 60  0000 C CNN
	1    4000 1600
	1    0    0    -1  
$EndComp
Text Label 6050 2200 2    60   ~ 0
PWM
Text Label 3300 1700 0    60   ~ 0
nCS
Text Label 6050 2500 2    60   ~ 0
SCK1
Text Label 6050 2400 2    60   ~ 0
MISO1
Text Label 6050 2300 2    60   ~ 0
MOSI1
$Comp
L GND #PWR8
U 1 1 55ECAB8E
P 2900 1950
F 0 "#PWR8" H 2900 1700 50  0001 C CNN
F 1 "GND" H 2900 1800 50  0000 C CNN
F 2 "" H 2900 1950 60  0000 C CNN
F 3 "" H 2900 1950 60  0000 C CNN
	1    2900 1950
	1    0    0    -1  
$EndComp
Text Label 3300 2300 0    60   ~ 0
USART1_TX
Text Label 3300 2400 0    60   ~ 0
USART1_RX
Text Label 3300 2500 0    60   ~ 0
USART1_CK
Text Label 3300 2100 0    60   ~ 0
WKUP1
Text Label 6800 1850 0    60   ~ 0
WKUP1
Text Label 3300 2200 0    60   ~ 0
USART1_RTS
Text Label 6800 2250 0    60   ~ 0
USART1_RTS
Text Label 6050 1600 2    60   ~ 0
SWCLK
Text Label 6050 1700 2    60   ~ 0
SWDIO
Text Label 6050 1800 2    60   ~ 0
SDA1
Text Label 6050 1900 2    60   ~ 0
SCL1
Text Label 3300 1800 0    60   ~ 0
UART1_EN
$Comp
L VCC #PWR2
U 1 1 55EDF925
P 1500 3500
F 0 "#PWR2" H 1500 3350 50  0001 C CNN
F 1 "VCC" H 1500 3650 50  0000 C CNN
F 2 "" H 1500 3500 60  0000 C CNN
F 3 "" H 1500 3500 60  0000 C CNN
	1    1500 3500
	1    0    0    -1  
$EndComp
$Comp
L GND #PWR17
U 1 1 55EDFECB
P 6200 2350
F 0 "#PWR17" H 6200 2100 50  0001 C CNN
F 1 "GND" H 6200 2200 50  0000 C CNN
F 2 "" H 6200 2350 60  0000 C CNN
F 3 "" H 6200 2350 60  0000 C CNN
	1    6200 2350
	1    0    0    -1  
$EndComp
$Comp
L VDD #PWR16
U 1 1 55EDFFBE
P 6200 1750
F 0 "#PWR16" H 6200 1600 50  0001 C CNN
F 1 "VDD" H 6200 1900 50  0000 C CNN
F 2 "" H 6200 1750 60  0000 C CNN
F 3 "" H 6200 1750 60  0000 C CNN
	1    6200 1750
	1    0    0    -1  
$EndComp
$Comp
L VCC #PWR22
U 1 1 55EE2A6B
P 9200 2800
F 0 "#PWR22" H 9200 2650 50  0001 C CNN
F 1 "VCC" H 9200 2950 50  0000 C CNN
F 2 "" H 9200 2800 60  0000 C CNN
F 3 "" H 9200 2800 60  0000 C CNN
	1    9200 2800
	1    0    0    -1  
$EndComp
$Comp
L CONN_01X10 J3
U 1 1 55EE328F
P 7800 2000
F 0 "J3" H 7800 2550 50  0000 C CNN
F 1 "CONN_01X10" V 7900 2000 50  0000 C CNN
F 2 "MvdL:HDR_5x2" H 7800 2000 60  0001 C CNN
F 3 "" H 7800 2000 60  0000 C CNN
	1    7800 2000
	1    0    0    -1  
$EndComp
$Comp
L VCC #PWR24
U 1 1 55EE03DA
P 10350 3350
F 0 "#PWR24" H 10350 3200 50  0001 C CNN
F 1 "VCC" H 10350 3500 50  0000 C CNN
F 2 "" H 10350 3350 60  0000 C CNN
F 3 "" H 10350 3350 60  0000 C CNN
	1    10350 3350
	1    0    0    -1  
$EndComp
$Comp
L VDD #PWR12
U 1 1 55EE0979
P 3900 1350
F 0 "#PWR12" H 3900 1200 50  0001 C CNN
F 1 "VDD" H 3900 1500 50  0000 C CNN
F 2 "" H 3900 1350 60  0000 C CNN
F 3 "" H 3900 1350 60  0000 C CNN
	1    3900 1350
	1    0    0    -1  
$EndComp
$Comp
L CC C1
U 1 1 55EE9A00
P 2450 2000
F 0 "C1" H 2450 2100 40  0000 L CNN
F 1 "d.n.p." H 2456 1915 40  0000 L CNN
F 2 "MvdL:C0603" H 2488 1850 30  0001 C CNN
F 3 "" H 2450 2000 60  0000 C CNN
	1    2450 2000
	1    0    0    -1  
$EndComp
$Comp
L VDD #PWR4
U 1 1 55EE9A06
P 2450 1800
F 0 "#PWR4" H 2450 1650 50  0001 C CNN
F 1 "VDD" H 2450 1950 50  0000 C CNN
F 2 "" H 2450 1800 60  0000 C CNN
F 3 "" H 2450 1800 60  0000 C CNN
	1    2450 1800
	1    0    0    -1  
$EndComp
$Comp
L GND #PWR5
U 1 1 55EE9A0C
P 2450 2200
F 0 "#PWR5" H 2450 1950 50  0001 C CNN
F 1 "GND" H 2450 2050 50  0000 C CNN
F 2 "" H 2450 2200 60  0000 C CNN
F 3 "" H 2450 2200 60  0000 C CNN
	1    2450 2200
	1    0    0    -1  
$EndComp
$Comp
L CC C4
U 1 1 55EEE893
P 2500 5050
F 0 "C4" H 2500 5150 40  0000 L CNN
F 1 "10u" H 2506 4965 40  0000 L CNN
F 2 "MvdL:C0603" H 2538 4900 30  0001 C CNN
F 3 "" H 2500 5050 60  0000 C CNN
	1    2500 5050
	1    0    0    -1  
$EndComp
$Comp
L CC C6
U 1 1 55EEE9C5
P 3700 5050
F 0 "C6" H 3700 5150 40  0000 L CNN
F 1 "1u" H 3706 4965 40  0000 L CNN
F 2 "MvdL:C0603" H 3738 4900 30  0001 C CNN
F 3 "" H 3700 5050 60  0000 C CNN
	1    3700 5050
	1    0    0    -1  
$EndComp
$Comp
L CC C5
U 1 1 55EEED18
P 3150 1900
F 0 "C5" V 3200 1750 40  0000 L CNN
F 1 "d.n.p." V 3300 1850 40  0000 L CNN
F 2 "MvdL:C0603" H 3188 1750 30  0001 C CNN
F 3 "" H 3150 1900 60  0000 C CNN
	1    3150 1900
	0    1    1    0   
$EndComp
$Comp
L CONN_01X04 J2
U 1 1 55EEF165
P 1800 3700
F 0 "J2" H 1800 3950 50  0000 C CNN
F 1 "CONN_01X04" V 1900 3700 50  0000 C CNN
F 2 "" H 1800 3700 60  0000 C CNN
F 3 "" H 1800 3700 60  0000 C CNN
	1    1800 3700
	1    0    0    -1  
$EndComp
$Comp
L RR R1
U 1 1 55EF382D
P 5800 3950
F 0 "R1" V 5880 3950 50  0000 C CNN
F 1 "100k" V 5725 3950 50  0000 C CNN
F 2 "MvdL:R0603" H 5800 3950 60  0001 C CNN
F 3 "" H 5800 3950 60  0000 C CNN
	1    5800 3950
	-1   0    0    1   
$EndComp
$Comp
L VDD #PWR15
U 1 1 55EF3935
P 5800 3650
F 0 "#PWR15" H 5800 3500 50  0001 C CNN
F 1 "VDD" H 5800 3800 50  0000 C CNN
F 2 "" H 5800 3650 60  0000 C CNN
F 3 "" H 5800 3650 60  0000 C CNN
	1    5800 3650
	1    0    0    -1  
$EndComp
Text Notes 9500 4300 0    60   ~ 0
d.n.p. = do not place
Text Notes 900  4775 0    60   ~ 0
4.5V (or 3V)
Text Notes 2200 4450 0    60   ~ 0
Do not place U1 when using 3V battery power\nbypass pin 2 and 3 with a 0 Ohm resistor
Text Notes 8575 4325 0    60   ~ 0
100k
$Comp
L +BATT #PWR?
U 1 1 567B1F2E
P 1575 4950
F 0 "#PWR?" H 1575 4800 50  0001 C CNN
F 1 "+BATT" H 1575 5090 50  0000 C CNN
F 2 "" H 1575 4950 60  0000 C CNN
F 3 "" H 1575 4950 60  0000 C CNN
	1    1575 4950
	1    0    0    -1  
$EndComp
$Comp
L +BATT #PWR?
U 1 1 567B2106
P 9550 2650
F 0 "#PWR?" H 9550 2500 50  0001 C CNN
F 1 "+BATT" H 9550 2790 50  0000 C CNN
F 2 "" H 9550 2650 60  0000 C CNN
F 3 "" H 9550 2650 60  0000 C CNN
	1    9550 2650
	1    0    0    -1  
$EndComp
Text Notes 6500 2150 1    60   ~ 0
10k
Wire Wire Line
	2500 5300 2500 5200
Wire Wire Line
	1450 5300 1450 4950
Wire Wire Line
	1450 4950 1250 4950
Wire Wire Line
	1650 5150 1250 5150
Wire Wire Line
	2500 4800 2500 4900
Wire Wire Line
	6800 4500 6700 4500
Wire Wire Line
	6800 4200 6800 4500
Wire Wire Line
	6800 4300 6700 4300
Wire Wire Line
	5450 4300 5850 4300
Wire Wire Line
	5450 4400 5850 4400
Wire Wire Line
	5450 4500 5850 4500
Wire Wire Line
	5450 4600 5850 4600
Wire Wire Line
	6800 4600 6800 4800
Wire Wire Line
	6800 4600 6700 4600
Connection ~ 6800 4300
Wire Wire Line
	1050 3850 1600 3850
Wire Wire Line
	1050 3750 1600 3750
Wire Wire Line
	2200 4850 2700 4850
Connection ~ 2500 4850
Wire Wire Line
	3700 5300 3700 5200
Wire Wire Line
	3700 4800 3700 4900
Wire Wire Line
	3700 4850 3500 4850
Wire Wire Line
	3100 5150 3100 5300
Connection ~ 3700 4850
Wire Wire Line
	5050 4400 5050 4450
Wire Wire Line
	5050 4750 5050 4800
Wire Wire Line
	7500 2550 7500 1550
Wire Wire Line
	7500 1550 7600 1550
Wire Wire Line
	7600 1650 7400 1650
Wire Wire Line
	7400 1650 7400 1550
Wire Wire Line
	6800 1750 7600 1750
Wire Wire Line
	6800 1850 7600 1850
Wire Wire Line
	6800 1950 7600 1950
Wire Wire Line
	6800 2050 7600 2050
Wire Wire Line
	6800 2150 7600 2150
Wire Wire Line
	6800 2250 7600 2250
Wire Wire Line
	9200 4250 9200 4350
Wire Wire Line
	8800 4100 8950 4100
Wire Wire Line
	9200 2800 9200 2900
Wire Wire Line
	10350 3350 10350 3450
Wire Wire Line
	10350 3750 10350 3850
Wire Wire Line
	9550 3500 9650 3500
Wire Wire Line
	9550 2650 9550 3500
Wire Wire Line
	9550 3400 9200 3400
Wire Wire Line
	9200 3350 9200 3450
Wire Wire Line
	9200 3750 9200 3850
Wire Wire Line
	9200 3800 9550 3800
Wire Wire Line
	9550 3800 9550 3700
Wire Wire Line
	9550 3700 9650 3700
Wire Wire Line
	6050 2200 5700 2200
Wire Wire Line
	6050 2300 5700 2300
Wire Wire Line
	5700 2400 6050 2400
Wire Wire Line
	6050 2500 5700 2500
Wire Wire Line
	3300 1700 4000 1700
Wire Wire Line
	3300 1900 4000 1900
Wire Wire Line
	3900 1350 3900 2000
Wire Wire Line
	3900 2000 4000 2000
Wire Wire Line
	4000 1600 2900 1600
Wire Wire Line
	2900 1600 2900 1950
Wire Wire Line
	3000 1900 2900 1900
Connection ~ 2900 1900
Wire Wire Line
	4000 2100 3300 2100
Wire Wire Line
	3300 2200 4000 2200
Wire Wire Line
	4000 2300 3300 2300
Wire Wire Line
	3300 2400 4000 2400
Wire Wire Line
	4000 2500 3300 2500
Wire Wire Line
	6050 1600 5700 1600
Wire Wire Line
	5700 1700 6050 1700
Wire Wire Line
	6700 4400 6800 4400
Connection ~ 6800 4400
Wire Wire Line
	4000 1800 3300 1800
Wire Wire Line
	2050 5150 2200 5150
Wire Wire Line
	2200 5150 2200 4850
Wire Wire Line
	6050 1800 5700 1800
Wire Wire Line
	5700 1900 6050 1900
Wire Wire Line
	1500 3500 1500 3650
Wire Wire Line
	1500 3650 1600 3650
Wire Wire Line
	6200 2100 6200 2350
Wire Wire Line
	6200 2100 5700 2100
Wire Wire Line
	6200 1750 6200 2000
Wire Wire Line
	6200 2000 5700 2000
Connection ~ 9200 3400
Connection ~ 9200 3800
Wire Wire Line
	6800 2350 7600 2350
Wire Wire Line
	7600 2450 6800 2450
Wire Wire Line
	2450 1800 2450 1850
Wire Wire Line
	2450 2150 2450 2200
Wire Wire Line
	5800 3650 5800 3750
Wire Wire Line
	5800 4200 5800 4300
Connection ~ 5800 4300
Wire Wire Line
	1400 3950 1400 3550
Wire Wire Line
	1400 3550 1600 3550
Wire Notes Line
	2650 4850 2650 4600
Wire Notes Line
	2650 4600 3550 4600
Wire Notes Line
	3550 4600 3550 4850
Wire Notes Line
	8875 4100 8875 4150
Wire Notes Line
	8875 4150 8925 4175
Wire Notes Line
	8925 4175 8825 4200
Wire Notes Line
	8825 4200 8925 4225
Wire Notes Line
	8925 4225 8825 4250
Wire Notes Line
	8825 4250 8925 4275
Wire Notes Line
	8925 4275 8825 4300
Wire Notes Line
	8825 4300 8925 4325
Wire Notes Line
	8925 4325 8825 4350
Wire Notes Line
	8825 4350 8925 4375
Wire Notes Line
	8925 4375 8875 4400
Wire Notes Line
	8875 4400 8875 4425
Wire Notes Line
	8825 4425 8925 4425
Wire Notes Line
	8825 4425 8875 4475
Wire Notes Line
	8875 4475 8925 4425
Wire Wire Line
	1575 4950 1575 5150
Connection ~ 1575 5150
Connection ~ 9550 3400
Wire Notes Line
	6800 1850 6575 1850
Wire Notes Line
	6575 1775 6575 1900
Wire Notes Line
	6575 1900 6625 1925
Wire Notes Line
	6625 1925 6525 1950
Wire Notes Line
	6525 1950 6625 1975
Wire Notes Line
	6625 1975 6525 2000
Wire Notes Line
	6525 2000 6625 2025
Wire Notes Line
	6625 2025 6525 2050
Wire Notes Line
	6525 2050 6625 2075
Wire Notes Line
	6625 2075 6525 2100
Wire Notes Line
	6525 2100 6625 2125
Wire Notes Line
	6625 2125 6525 2150
Wire Notes Line
	6525 2150 6575 2175
Wire Notes Line
	6575 2175 6575 2250
Wire Notes Line
	6525 2250 6625 2250
Wire Notes Line
	6525 2250 6575 2300
Wire Notes Line
	6575 2300 6625 2250
Wire Notes Line
	6575 1775 6550 1775
Wire Notes Line
	6575 1675 6525 1800
Wire Notes Line
	6575 1550 6575 1675
$Comp
L VDD #PWR?
U 1 1 567B3B49
P 6575 1550
F 0 "#PWR?" H 6575 1400 50  0001 C CNN
F 1 "VDD" H 6575 1700 50  0000 C CNN
F 2 "" H 6575 1550 60  0000 C CNN
F 3 "" H 6575 1550 60  0000 C CNN
	1    6575 1550
	1    0    0    -1  
$EndComp
Wire Notes Line
	9050 2925 9350 3300
Wire Notes Line
	9050 3300 9350 2925
Text Notes 9550 4150 0    60   ~ 0
or 16Ohm\nor 32Ohm
$EndSCHEMATC

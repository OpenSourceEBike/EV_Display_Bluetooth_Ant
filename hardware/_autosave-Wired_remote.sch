EESchema Schematic File Version 4
EELAYER 30 0
EELAYER END
$Descr A3 16535 11693
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
Text Notes 4750 9450 0    60   ~ 0
  NOTE!!! Wire colouring and pin numbers\nmay change! Always check with a meter first.
Text GLabel 6750 8400 2    57   Output ~ 0
V.Battery
Text GLabel 6750 8500 2    57   Input ~ 0
TSDZ2_Vin
Text GLabel 6750 8800 2    57   Input ~ 0
TSDZ2_Brake_Input
Text GLabel 6750 9000 2    57   Output ~ 0
TSDZ2_Tx
Text GLabel 6750 8600 2    57   Input ~ 0
TSDZ2_Rx
NoConn ~ 6450 8900
Text GLabel 6750 10100 2    57   Output ~ 0
V.Battery
Text GLabel 6750 10300 2    57   Input ~ 0
TSDZ2_Vin
Text GLabel 6750 9900 2    57   Input ~ 0
TSDZ2_Brake_Input
Text GLabel 6750 10200 2    57   Output ~ 0
TSDZ2_Tx
Text GLabel 6750 10000 2    57   Input ~ 0
TSDZ2_Rx
Text GLabel 6325 2700 0    57   Input ~ 0
V.Battery
Text GLabel 6350 3650 0    57   Output ~ 0
TSDZ2_Rx
Text GLabel 6350 3750 0    57   Input ~ 0
TSDZ2_Tx
Text GLabel 6750 9800 2    57   Output ~ 0
TSDZ2_GND
Text GLabel 6750 8300 2    57   Output ~ 0
TSDZ2_GND
Text GLabel 6425 2075 0    57   Input ~ 0
TSDZ2_GND
Wire Wire Line
	6450 9800 6750 9800
Wire Wire Line
	6450 8300 6750 8300
Wire Wire Line
	6750 8400 6450 8400
Wire Wire Line
	6750 8500 6450 8500
Wire Wire Line
	6450 8600 6750 8600
Wire Wire Line
	6450 8800 6750 8800
Wire Wire Line
	6450 9000 6750 9000
Wire Wire Line
	6750 9900 6450 9900
Wire Wire Line
	6450 10000 6750 10000
Wire Wire Line
	6750 10100 6450 10100
Wire Wire Line
	6450 10200 6750 10200
Wire Wire Line
	6750 10300 6450 10300
Text Notes 4730 8010 0    60   ~ 0
If you have the TSDZ2 with the throttle option you will\nhave the 8-Way cable. If you don't have a throttle, you\n      are more likely to have the 6-Way cable
Wire Wire Line
	9875 3250 9675 3250
Wire Wire Line
	8275 3650 6350 3650
Wire Wire Line
	6350 3750 8275 3750
Wire Wire Line
	7950 3850 8275 3850
Text GLabel 6375 2400 0    57   Output ~ 0
TSDZ2_Vin
Wire Wire Line
	9875 1875 9875 3250
Wire Wire Line
	8100 1875 9875 1875
NoConn ~ 8275 3250
NoConn ~ 8275 3350
NoConn ~ 8275 3450
NoConn ~ 8275 3550
NoConn ~ 8275 4050
NoConn ~ 9675 3650
NoConn ~ 9675 3550
NoConn ~ 9675 3750
NoConn ~ 9675 3850
NoConn ~ 9675 3950
NoConn ~ 9675 4050
NoConn ~ 9675 4150
$Comp
L Wired_remote:8-Way_Higo-Dongle K?
U 1 1 600F98A9
P 5850 8800
F 0 "K?" H 5608 9587 60  0001 C CNN
F 1 "8 Way Higo" H 5750 9470 60  0000 C CNN
F 2 "" H 5850 8800 60  0000 C CNN
F 3 "" H 5850 8800 60  0000 C CNN
	1    5850 8800
	1    0    0    -1  
$EndComp
$Comp
L Wired_remote:6-Way_Higo-Dongle K?
U 1 1 600FCB69
P 5900 10200
F 0 "K?" H 5683 10887 60  0001 C CNN
F 1 "6 Way Higo" H 5683 10781 60  0000 C CNN
F 2 "" H 5900 10200 60  0000 C CNN
F 3 "" H 5900 10200 60  0000 C CNN
	1    5900 10200
	1    0    0    -1  
$EndComp
NoConn ~ 8275 4150
$Comp
L Wired_remote-rescue:Generic_DC-DC-Wireless_eBike-Wireless_Ebike U?
U 1 1 60103A2E
P 7600 1975
F 0 "U?" H 7600 2362 60  0001 C CNN
F 1 "Generic DC-DC (min input allowed 60V, output 5V)" H 7550 2275 60  0001 C CNN
F 2 "" H 7550 1975 60  0000 C CNN
F 3 "" H 7550 1975 60  0000 C CNN
	1    7600 1975
	1    0    0    -1  
$EndComp
Wire Wire Line
	8250 2075 8250 2125
Wire Wire Line
	8100 2075 8250 2075
$Comp
L Wired_remote-rescue:BTS4140N-Wireless_eBike-Wireless_Ebike U?
U 1 1 6007C216
P 6825 2700
F 0 "U?" H 6800 3087 60  0001 C CNN
F 1 "BTS4140N" V 6795 2700 60  0000 C CNN
F 2 "" H 6225 2750 60  0001 C CNN
F 3 "" H 6225 2750 60  0000 C CNN
	1    6825 2700
	-1   0    0    1   
$EndComp
Wire Wire Line
	7175 2600 7275 2600
Wire Wire Line
	7275 2600 7275 2400
Wire Wire Line
	7275 2400 6850 2400
NoConn ~ 7175 2700
NoConn ~ 8425 3100
NoConn ~ 9525 3100
NoConn ~ 9675 3350
Wire Wire Line
	9875 3450 9875 3500
$Comp
L Wired_remote:Nordic_nRF52840_USB_Dongle U?
U 1 1 6003704A
P 8975 3600
F 0 "U?" H 8975 3600 60  0001 C CNN
F 1 "Nordic nRF52840 USB Dongle" H 9075 4525 60  0000 C CNN
F 2 "" H 8825 3450 60  0000 C CNN
F 3 "" H 8825 3450 60  0000 C CNN
	1    8975 3600
	1    0    0    -1  
$EndComp
Text Notes 8625 2575 0    60   ~ 0
wireless board
Wire Wire Line
	7175 2800 7250 2800
$Comp
L Wired_remote-rescue:BSP296-Wireless_Ebike U?
U 1 1 6006EF16
P 7550 2800
F 0 "U?" H 7525 2413 60  0001 C CNN
F 1 "BSP296" V 7520 2800 60  0000 C CNN
F 2 "" H 6950 2850 60  0001 C CNN
F 3 "" H 6950 2850 60  0001 C CNN
	1    7550 2800
	-1   0    0    1   
$EndComp
Wire Wire Line
	7900 2700 8150 2700
Wire Wire Line
	8150 2700 8150 2750
Wire Wire Line
	7900 2900 7950 2900
NoConn ~ 7900 2800
Wire Wire Line
	7950 2900 7950 3850
Text Notes 7155 1735 0    60   ~ 0
Generic DC-DC\nmin input allowed 60V, output 5V
Wire Wire Line
	9675 3450 9875 3450
$Comp
L Wired_remote:Switch_SW_Push button_1
U 1 1 5F4A3714
P 11951 2799
F 0 "button_1" H 11951 2999 50  0000 C CNN
F 1 "UP" H 11951 3099 50  0000 C CNB
F 2 "" H 11951 2999 50  0001 C CNN
F 3 "~" H 11951 2999 50  0001 C CNN
	1    11951 2799
	1    0    0    -1  
$EndComp
Wire Wire Line
	11601 2799 11751 2799
Wire Wire Line
	11601 3299 11601 2799
Wire Wire Line
	11601 3299 11751 3299
$Comp
L Wired_remote:Switch_SW_Push button_2
U 1 1 5F4A3F33
P 11951 3299
F 0 "button_2" H 11951 3499 50  0000 C CNN
F 1 "DOWN" H 11951 3599 50  0000 C CNB
F 2 "" H 11951 3499 50  0001 C CNN
F 3 "~" H 11951 3499 50  0001 C CNN
	1    11951 3299
	1    0    0    -1  
$EndComp
Wire Notes Line
	11451 2349 12651 2349
Wire Notes Line
	12651 2349 12651 3949
Wire Notes Line
	12651 3949 11451 3949
Text Notes 11451 2299 0    79   ~ 0
850C remote keypad
NoConn ~ 8275 3950
Text GLabel 6750 8700 2    50   Output ~ 0
TSDZ2_5V
Wire Wire Line
	6450 8700 6750 8700
Wire Notes Line
	11475 7750 11475 8300
Wire Notes Line
	10675 7750 10675 8300
Text Notes 11475 7700 2    79   ~ 0
TSDZ2 Brake sensor\nconnector
Wire Notes Line
	10675 8300 11475 8300
Wire Notes Line
	10675 7750 11475 7750
Wire Wire Line
	9775 8050 10875 8050
Wire Wire Line
	10875 7950 9875 7950
$Comp
L Wired_remote:Connector_Generic_Conn_01x02 J?
U 1 1 600CF908
P 11075 8050
F 0 "J?" H 10993 7725 50  0001 C CNN
F 1 "Brake" V 11200 8000 50  0000 C CNB
F 2 "" H 11075 8050 50  0001 C CNN
F 3 "~" H 11075 8050 50  0001 C CNN
	1    11075 8050
	1    0    0    1   
$EndComp
$Comp
L Wired_remote:Connector_Generic_Conn_01x03 Brake
U 1 1 60323BC4
P 11100 9275
F 0 "Brake" V 11219 9277 50  0000 C CNB
F 1 "Brake" V 11180 9226 50  0001 L CNN
F 2 "" H 11100 9275 50  0001 C CNN
F 3 "" H 11100 9275 50  0001 C CNN
	1    11100 9275
	1    0    0    -1  
$EndComp
Wire Notes Line
	11475 9000 11475 9550
Wire Notes Line
	10675 9000 10675 9550
Text Notes 11475 8950 2    79   ~ 0
Bafang Brake sensor\nconnector
Wire Notes Line
	10675 9550 11475 9550
Wire Notes Line
	10675 9000 11475 9000
Text GLabel 9875 7950 0    57   Output ~ 0
TSDZ2_Brake_Input
Text GLabel 9775 8050 0    57   Input ~ 0
TSDZ2_GND
Text GLabel 9925 9175 0    57   Output ~ 0
TSDZ2_Brake_Input
Text GLabel 9825 9375 0    57   Input ~ 0
TSDZ2_GND
Text GLabel 9825 9275 0    50   Input ~ 0
TSDZ2_5V
Wire Wire Line
	10900 9375 9825 9375
Wire Wire Line
	10900 9175 9925 9175
Wire Wire Line
	9825 9275 10900 9275
Connection ~ 9875 1875
Wire Wire Line
	9875 1875 10350 1875
Wire Wire Line
	6850 2400 6850 1875
Wire Wire Line
	6850 1875 7100 1875
Connection ~ 6850 2400
Wire Wire Line
	6850 2400 6375 2400
Wire Wire Line
	6425 2075 7100 2075
Wire Wire Line
	6325 2700 6525 2700
Connection ~ 11601 3299
Wire Notes Line
	11451 2349 11451 3949
$Comp
L Wired_remote:Switch_SW_Push button_3
U 1 1 5F4A4B3B
P 11951 3799
F 0 "button_3" H 11951 3999 50  0000 C CNN
F 1 "POWER" H 11951 4099 50  0000 C CNB
F 2 "" H 11951 3999 50  0001 C CNN
F 3 "~" H 11951 3999 50  0001 C CNN
	1    11951 3799
	1    0    0    -1  
$EndComp
Wire Wire Line
	11601 3799 11751 3799
Wire Wire Line
	11601 3799 11601 3299
$Comp
L power:GND #PWR?
U 1 1 6166B2E4
P 9875 3500
F 0 "#PWR?" H 9875 3250 50  0001 C CNN
F 1 "GND" H 9880 3327 50  0000 C CNN
F 2 "" H 9875 3500 50  0001 C CNN
F 3 "" H 9875 3500 50  0001 C CNN
	1    9875 3500
	1    0    0    -1  
$EndComp
$Comp
L power:GND #PWR?
U 1 1 6166C2F7
P 8250 2125
F 0 "#PWR?" H 8250 1875 50  0001 C CNN
F 1 "GND" H 8255 1952 50  0000 C CNN
F 2 "" H 8250 2125 50  0001 C CNN
F 3 "" H 8250 2125 50  0001 C CNN
	1    8250 2125
	1    0    0    -1  
$EndComp
$Comp
L power:GND #PWR?
U 1 1 616740DC
P 8150 2750
F 0 "#PWR?" H 8150 2500 50  0001 C CNN
F 1 "GND" H 8155 2577 50  0000 C CNN
F 2 "" H 8150 2750 50  0001 C CNN
F 3 "" H 8150 2750 50  0001 C CNN
	1    8150 2750
	1    0    0    -1  
$EndComp
Wire Wire Line
	12150 2800 12250 2800
Wire Wire Line
	12250 2800 12250 3300
Wire Wire Line
	12250 3300 12140 3300
Wire Wire Line
	12150 3800 12325 3800
Wire Wire Line
	12325 3800 12325 3775
$EndSCHEMATC

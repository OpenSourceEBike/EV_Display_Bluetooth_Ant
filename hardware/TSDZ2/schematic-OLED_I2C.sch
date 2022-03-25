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
Text Notes 3209 4034 0    60   ~ 0
  NOTE!!! Wire colouring and pin numbers\nmay change! Always check with a meter first.
Text GLabel 5209 2984 2    57   Output ~ 0
V.Battery
Text GLabel 5209 3084 2    57   Input ~ 0
TSDZ2_Vin
Text GLabel 5209 3384 2    57   Input ~ 0
TSDZ2_Brake_Input
Text GLabel 5209 3584 2    57   Output ~ 0
TSDZ2_Tx
Text GLabel 5209 3184 2    57   Input ~ 0
TSDZ2_Rx
NoConn ~ 4909 3484
Text GLabel 5209 4684 2    57   Output ~ 0
V.Battery
Text GLabel 5209 4884 2    57   Input ~ 0
TSDZ2_Vin
Text GLabel 5209 4484 2    57   Input ~ 0
TSDZ2_Brake_Input
Text GLabel 5209 4784 2    57   Output ~ 0
TSDZ2_Tx
Text GLabel 5209 4584 2    57   Input ~ 0
TSDZ2_Rx
Text GLabel 8206 4864 0    57   Output ~ 0
TSDZ2_Rx
Text GLabel 8196 4964 0    57   Input ~ 0
TSDZ2_Tx
Text GLabel 5209 4384 2    57   Output ~ 0
TSDZ2_GND
Text GLabel 5209 2884 2    57   Output ~ 0
TSDZ2_GND
Text GLabel 8280 3284 0    57   Input ~ 0
TSDZ2_GND
Wire Wire Line
	4909 4384 5209 4384
Wire Wire Line
	4909 2884 5209 2884
Wire Wire Line
	5209 2984 4909 2984
Wire Wire Line
	5209 3084 4909 3084
Wire Wire Line
	4909 3184 5209 3184
Wire Wire Line
	4909 3384 5209 3384
Wire Wire Line
	4909 3584 5209 3584
Wire Wire Line
	5209 4484 4909 4484
Wire Wire Line
	4909 4584 5209 4584
Wire Wire Line
	5209 4684 4909 4684
Wire Wire Line
	4909 4784 5209 4784
Wire Wire Line
	5209 4884 4909 4884
Text Notes 3189 2594 0    60   ~ 0
If you have the TSDZ2 with the throttle option you will\nhave the 8-Way cable. If you don't have a throttle, you\n      are more likely to have the 6-Way cable
Text GLabel 8232 3614 0    57   Output ~ 0
TSDZ2_Vin
$Comp
L Wired_remote:8-Way_Higo-Dongle K?
U 1 1 600F98A9
P 4309 3384
F 0 "K?" H 4067 4171 60  0001 C CNN
F 1 "8 Way Higo" H 4209 4054 60  0000 C CNN
F 2 "" H 4309 3384 60  0000 C CNN
F 3 "" H 4309 3384 60  0000 C CNN
	1    4309 3384
	1    0    0    -1  
$EndComp
$Comp
L Wired_remote:6-Way_Higo-Dongle K?
U 1 1 600FCB69
P 4359 4784
F 0 "K?" H 4142 5471 60  0001 C CNN
F 1 "6 Way Higo" H 4142 5365 60  0000 C CNN
F 2 "" H 4359 4784 60  0000 C CNN
F 3 "" H 4359 4784 60  0000 C CNN
	1    4359 4784
	1    0    0    -1  
$EndComp
Wire Wire Line
	9286 3814 9381 3814
Wire Wire Line
	9381 3814 9381 3614
NoConn ~ 9286 3914
Text Notes 10731 3789 0    60   ~ 0
wireless board
Wire Wire Line
	9286 4014 9356 4014
$Comp
L Wired_remote-rescue:BSP296-Wireless_Ebike U?
U 1 1 6006EF16
P 9656 4014
F 0 "U?" H 9631 3627 60  0001 C CNN
F 1 "BSP296" V 9626 4014 60  0000 C CNN
F 2 "" H 9056 4064 60  0001 C CNN
F 3 "" H 9056 4064 60  0001 C CNN
	1    9656 4014
	-1   0    0    1   
$EndComp
Wire Wire Line
	10006 3914 10256 3914
Wire Wire Line
	10256 3914 10256 3964
Wire Wire Line
	10006 4114 10056 4114
NoConn ~ 10006 4014
Wire Wire Line
	10056 4114 10056 5064
Text Notes 8821 2959 0    60   ~ 0
Generic DC-DC\nmin input allowed 60V, output 5V
$Comp
L Wired_remote:Switch_SW_Push button_1
U 1 1 5F4A3714
P 8286 6074
F 0 "button_1" H 8286 6274 50  0000 C CNN
F 1 "UP" H 8286 6374 50  0000 C CNB
F 2 "" H 8286 6274 50  0001 C CNN
F 3 "~" H 8286 6274 50  0001 C CNN
	1    8286 6074
	1    0    0    -1  
$EndComp
$Comp
L Wired_remote:Switch_SW_Push button_2
U 1 1 5F4A3F33
P 8286 6574
F 0 "button_2" H 8286 6774 50  0000 C CNN
F 1 "DOWN" H 8286 6874 50  0000 C CNB
F 2 "" H 8286 6774 50  0001 C CNN
F 3 "~" H 8286 6774 50  0001 C CNN
	1    8286 6574
	1    0    0    -1  
$EndComp
Wire Notes Line
	7737 5623 8937 5623
Wire Notes Line
	8937 5623 8932 7350
Wire Notes Line
	8934 7361 7734 7361
Text Notes 7737 5573 0    79   ~ 0
850C remote keypad
Text GLabel 5209 3284 2    50   Output ~ 0
TSDZ2_5V
Wire Wire Line
	4909 3284 5209 3284
Wire Notes Line
	3524 6494 3524 5944
Wire Notes Line
	4324 6494 4324 5944
Text Notes 3514 5923 0    79   ~ 0
TSDZ2 Brake sensor\nconnector
Wire Notes Line
	4324 5944 3524 5944
Wire Notes Line
	4324 6494 3524 6494
$Comp
L Wired_remote:Connector_Generic_Conn_01x02 J?
U 1 1 600CF908
P 3924 6194
F 0 "J?" H 3842 5869 50  0001 C CNN
F 1 "Brake" V 4049 6144 50  0000 C CNB
F 2 "" H 3924 6194 50  0001 C CNN
F 3 "~" H 3924 6194 50  0001 C CNN
	1    3924 6194
	-1   0    0    -1  
$EndComp
$Comp
L Wired_remote:Connector_Generic_Conn_01x03 Brake
U 1 1 60323BC4
P 3899 7529
F 0 "Brake" V 4018 7531 50  0000 C CNB
F 1 "Brake" V 3979 7480 50  0001 L CNN
F 2 "" H 3899 7529 50  0001 C CNN
F 3 "" H 3899 7529 50  0001 C CNN
	1    3899 7529
	-1   0    0    1   
$EndComp
Wire Notes Line
	3524 7804 3524 7254
Wire Notes Line
	4324 7804 4324 7254
Text Notes 3364 7213 0    79   ~ 0
Bafang Brake sensor\nconnector\n(needs 5V from TSDZ2\n8 pins connector only)
Wire Notes Line
	4324 7254 3524 7254
Wire Notes Line
	4324 7804 3524 7804
Text GLabel 5214 6294 2    57   Output ~ 0
TSDZ2_Brake_Input
Text GLabel 5214 6194 2    57   Input ~ 0
TSDZ2_GND
Text GLabel 5214 7529 2    50   Input ~ 0
TSDZ2_5V
$Comp
L Wired_remote:Switch_SW_Push button_3
U 1 1 5F4A4B3B
P 8286 7074
F 0 "button_3" H 8286 7274 50  0000 C CNN
F 1 "POWER" H 8286 7374 50  0000 C CNB
F 2 "" H 8286 7274 50  0001 C CNN
F 3 "~" H 8286 7274 50  0001 C CNN
	1    8286 7074
	1    0    0    -1  
$EndComp
$Comp
L power:GND #PWR?
U 1 1 616740DC
P 10256 3964
F 0 "#PWR?" H 10256 3714 50  0001 C CNN
F 1 "GND" H 10261 3791 50  0000 C CNN
F 2 "" H 10256 3964 50  0001 C CNN
F 3 "" H 10256 3964 50  0001 C CNN
	1    10256 3964
	1    0    0    -1  
$EndComp
Text GLabel 8176 3084 0    57   Input ~ 0
V.Battery
$Comp
L Wired_remote-rescue:Generic_DC-DC-Wireless_eBike-Wireless_Ebike U?
U 1 1 60103A2E
P 9136 3184
F 0 "U?" H 9136 3571 60  0001 C CNN
F 1 "Generic DC-DC (min input allowed 60V, output 5V)" H 9086 3484 60  0001 C CNN
F 2 "" H 9086 3184 60  0000 C CNN
F 3 "" H 9086 3184 60  0000 C CNN
	1    9136 3184
	1    0    0    -1  
$EndComp
Wire Wire Line
	9636 3284 9706 3284
Wire Wire Line
	9706 3284 9706 3334
$Comp
L power:GND #PWR?
U 1 1 616B94AD
P 9706 3334
F 0 "#PWR?" H 9706 3084 50  0001 C CNN
F 1 "GND" H 9711 3161 50  0000 C CNN
F 2 "" H 9706 3334 50  0001 C CNN
F 3 "" H 9706 3334 50  0001 C CNN
	1    9706 3334
	1    0    0    -1  
$EndComp
$Comp
L Wired_remote-rescue:BTS4140N-Wireless_eBike-Wireless_Ebike U?
U 1 1 6007C216
P 8936 3914
F 0 "U?" H 8911 4301 60  0001 C CNN
F 1 "BTS4140N" V 8906 3914 60  0000 C CNN
F 2 "" H 8336 3964 60  0001 C CNN
F 3 "" H 8336 3964 60  0000 C CNN
	1    8936 3914
	-1   0    0    1   
$EndComp
Wire Wire Line
	8636 3084 8556 3084
Wire Wire Line
	8636 3284 8280 3284
Wire Wire Line
	9381 3614 8232 3614
Wire Wire Line
	8636 3914 8556 3914
Wire Wire Line
	8556 3914 8556 3084
Connection ~ 8556 3084
Wire Wire Line
	8556 3084 8176 3084
Wire Wire Line
	9636 3084 11986 3084
Wire Wire Line
	8086 6074 7956 6074
Wire Wire Line
	7956 6074 7956 6574
Wire Wire Line
	7956 6574 8086 6574
Wire Wire Line
	7956 7074 8086 7074
Connection ~ 7956 6574
NoConn ~ 10376 4664
NoConn ~ 11776 5064
Wire Wire Line
	10376 4864 8206 4864
NoConn ~ 11776 4964
NoConn ~ 11776 4864
Wire Wire Line
	8196 4964 10376 4964
Wire Wire Line
	10056 5064 10376 5064
NoConn ~ 11776 4764
NoConn ~ 10376 5164
NoConn ~ 10376 5264
NoConn ~ 10526 4314
NoConn ~ 11626 4314
Wire Wire Line
	11986 4464 11776 4464
Wire Wire Line
	9566 4464 10376 4464
Wire Wire Line
	9686 4564 10376 4564
Wire Wire Line
	9796 4764 10376 4764
Wire Wire Line
	8486 6074 8666 6074
Wire Wire Line
	9686 4564 9686 6574
Wire Wire Line
	8486 7074 8666 7074
Wire Wire Line
	8666 7074 8666 6664
Wire Wire Line
	8666 6664 9796 6664
Wire Wire Line
	9796 6664 9796 4764
Wire Wire Line
	8486 6574 9686 6574
Wire Wire Line
	9566 6454 8666 6454
Wire Wire Line
	8666 6454 8666 6074
Wire Wire Line
	9566 4464 9566 6454
Wire Notes Line
	13107 4773 14117 4773
Wire Notes Line
	14117 4773 14117 5793
Wire Notes Line
	14117 5793 13107 5793
Text Notes 13107 4723 0    79   ~ 0
OLED display I2C\n128x64
Wire Notes Line
	13107 4773 13107 5793
$Comp
L schematic-rescue:SSD1306-oled Brd?
U 1 1 616455CF
P 13616 5314
F 0 "Brd?" V 13662 5036 50  0001 R CNN
F 1 "OLED display" V 13936 5554 50  0000 R CNN
F 2 "" H 13616 5564 50  0001 C CNN
F 3 "" H 13616 5564 50  0001 C CNN
	1    13616 5314
	0    -1   -1   0   
$EndComp
$Comp
L power:GND #PWR?
U 1 1 61686357
P 12906 5534
F 0 "#PWR?" H 12906 5284 50  0001 C CNN
F 1 "GND" H 12911 5361 50  0000 C CNN
F 2 "" H 12906 5534 50  0001 C CNN
F 3 "" H 12906 5534 50  0001 C CNN
	1    12906 5534
	1    0    0    -1  
$EndComp
$Comp
L power:GND #PWR?
U 1 1 616B5CEE
P 10296 5434
F 0 "#PWR?" H 10296 5184 50  0001 C CNN
F 1 "GND" H 10301 5261 50  0000 C CNN
F 2 "" H 10296 5434 50  0001 C CNN
F 3 "" H 10296 5434 50  0001 C CNN
	1    10296 5434
	1    0    0    -1  
$EndComp
Wire Wire Line
	10376 5364 10296 5364
Wire Wire Line
	10296 5364 10296 5434
Wire Wire Line
	11776 5264 13266 5264
Wire Wire Line
	11776 5164 13266 5164
Wire Wire Line
	13266 5464 12906 5464
Wire Wire Line
	12906 5464 12906 5534
Wire Wire Line
	13266 5364 12906 5364
NoConn ~ 11776 5364
Text GLabel 5214 7429 2    57   Input ~ 0
TSDZ2_GND
Text GLabel 5214 7629 2    57   Output ~ 0
TSDZ2_Brake_Input
Wire Notes Line
	3319 5564 4799 5564
Wire Notes Line
	4799 5564 4799 7954
Wire Notes Line
	4799 7964 3309 7964
Wire Notes Line
	3309 7964 3309 5564
Text Notes 3324 5523 0    79   ~ 0
Brake sensor
Wire Wire Line
	4124 6194 5214 6194
Wire Wire Line
	4124 6294 5214 6294
Wire Wire Line
	4099 7429 5214 7429
Wire Wire Line
	4099 7529 5214 7529
Wire Wire Line
	4099 7629 5214 7629
Wire Wire Line
	10296 5364 9920 5364
Wire Wire Line
	9920 5364 9920 6760
Wire Wire Line
	9920 6760 8780 6760
Connection ~ 10296 5364
Wire Wire Line
	7956 7219 8780 7219
Wire Wire Line
	7956 6574 7956 7074
Wire Wire Line
	8780 6760 8780 7219
Connection ~ 7956 7074
Wire Wire Line
	7956 7074 7956 7219
Wire Notes Line
	7737 5628 7732 7355
Wire Wire Line
	11986 3084 11986 4464
Connection ~ 11986 4464
Wire Wire Line
	11986 4464 12906 4464
Wire Wire Line
	12906 5364 12906 4464
NoConn ~ 11776 4664
$Comp
L Wired_remote:Nordic_nRF52840_USB_Dongle U?
U 1 1 6003704A
P 11076 4814
F 0 "U?" H 11076 4814 60  0001 C CNN
F 1 "Nordic nRF52840 USB Dongle" H 11176 5739 60  0000 C CNN
F 2 "" H 10926 4664 60  0000 C CNN
F 3 "" H 10926 4664 60  0000 C CNN
	1    11076 4814
	1    0    0    -1  
$EndComp
NoConn ~ 11776 4564
$EndSCHEMATC

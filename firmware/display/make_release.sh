#!/bin/bash
echo " "
echo "Start building the release files"
echo " "
mkdir release
make clean
sleep 2
make default DISPLAY_OLED_1.3_SPI=1
cp _build/firmware_ota* release
make clean
sleep 2
make default DISPLAY_OLED_1.3_I2C=1
cp _build/firmware_ota* release
make clean
sleep 2
make default DISPLAY_OLED_0.96_SPI=1
cp _build/firmware_ota* release
make clean
sleep 2
make default DISPLAY_OLED_0.96_I2C=1
cp _build/firmware_ota* release
echo " "
echo "Done! - find files on 'release' folder"
echo " "


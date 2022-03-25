# Install script for directory: /home/cas/work/TSDZ2/ev_display_bluetooth_ant/hardware/kicad-symbols

# Set the install prefix
if(NOT DEFINED CMAKE_INSTALL_PREFIX)
  set(CMAKE_INSTALL_PREFIX "/usr/local")
endif()
string(REGEX REPLACE "/$" "" CMAKE_INSTALL_PREFIX "${CMAKE_INSTALL_PREFIX}")

# Set the install configuration name.
if(NOT DEFINED CMAKE_INSTALL_CONFIG_NAME)
  if(BUILD_TYPE)
    string(REGEX REPLACE "^[^A-Za-z0-9_]+" ""
           CMAKE_INSTALL_CONFIG_NAME "${BUILD_TYPE}")
  else()
    set(CMAKE_INSTALL_CONFIG_NAME "")
  endif()
  message(STATUS "Install configuration: \"${CMAKE_INSTALL_CONFIG_NAME}\"")
endif()

# Set the component getting installed.
if(NOT CMAKE_INSTALL_COMPONENT)
  if(COMPONENT)
    message(STATUS "Install component: \"${COMPONENT}\"")
    set(CMAKE_INSTALL_COMPONENT "${COMPONENT}")
  else()
    set(CMAKE_INSTALL_COMPONENT)
  endif()
endif()

# Install shared libraries without execute permission?
if(NOT DEFINED CMAKE_INSTALL_SO_NO_EXE)
  set(CMAKE_INSTALL_SO_NO_EXE "1")
endif()

# Is this installation the result of a crosscompile?
if(NOT DEFINED CMAKE_CROSSCOMPILING)
  set(CMAKE_CROSSCOMPILING "FALSE")
endif()

if("x${CMAKE_INSTALL_COMPONENT}x" STREQUAL "xresourcesx" OR NOT CMAKE_INSTALL_COMPONENT)
  file(INSTALL DESTINATION "${CMAKE_INSTALL_PREFIX}/share/kicad/library" TYPE FILE FILES
    "/home/cas/work/TSDZ2/ev_display_bluetooth_ant/hardware/kicad-symbols/4xxx.kicad_sym"
    "/home/cas/work/TSDZ2/ev_display_bluetooth_ant/hardware/kicad-symbols/4xxx_IEEE.kicad_sym"
    "/home/cas/work/TSDZ2/ev_display_bluetooth_ant/hardware/kicad-symbols/74xGxx.kicad_sym"
    "/home/cas/work/TSDZ2/ev_display_bluetooth_ant/hardware/kicad-symbols/74xx.kicad_sym"
    "/home/cas/work/TSDZ2/ev_display_bluetooth_ant/hardware/kicad-symbols/74xx_IEEE.kicad_sym"
    "/home/cas/work/TSDZ2/ev_display_bluetooth_ant/hardware/kicad-symbols/Amplifier_Audio.kicad_sym"
    "/home/cas/work/TSDZ2/ev_display_bluetooth_ant/hardware/kicad-symbols/Amplifier_Buffer.kicad_sym"
    "/home/cas/work/TSDZ2/ev_display_bluetooth_ant/hardware/kicad-symbols/Amplifier_Current.kicad_sym"
    "/home/cas/work/TSDZ2/ev_display_bluetooth_ant/hardware/kicad-symbols/Amplifier_Difference.kicad_sym"
    "/home/cas/work/TSDZ2/ev_display_bluetooth_ant/hardware/kicad-symbols/Amplifier_Instrumentation.kicad_sym"
    "/home/cas/work/TSDZ2/ev_display_bluetooth_ant/hardware/kicad-symbols/Amplifier_Operational.kicad_sym"
    "/home/cas/work/TSDZ2/ev_display_bluetooth_ant/hardware/kicad-symbols/Amplifier_Video.kicad_sym"
    "/home/cas/work/TSDZ2/ev_display_bluetooth_ant/hardware/kicad-symbols/Analog.kicad_sym"
    "/home/cas/work/TSDZ2/ev_display_bluetooth_ant/hardware/kicad-symbols/Analog_ADC.kicad_sym"
    "/home/cas/work/TSDZ2/ev_display_bluetooth_ant/hardware/kicad-symbols/Analog_DAC.kicad_sym"
    "/home/cas/work/TSDZ2/ev_display_bluetooth_ant/hardware/kicad-symbols/Analog_Switch.kicad_sym"
    "/home/cas/work/TSDZ2/ev_display_bluetooth_ant/hardware/kicad-symbols/Audio.kicad_sym"
    "/home/cas/work/TSDZ2/ev_display_bluetooth_ant/hardware/kicad-symbols/Battery_Management.kicad_sym"
    "/home/cas/work/TSDZ2/ev_display_bluetooth_ant/hardware/kicad-symbols/Buffer.kicad_sym"
    "/home/cas/work/TSDZ2/ev_display_bluetooth_ant/hardware/kicad-symbols/CPLD_Altera.kicad_sym"
    "/home/cas/work/TSDZ2/ev_display_bluetooth_ant/hardware/kicad-symbols/CPLD_Microchip.kicad_sym"
    "/home/cas/work/TSDZ2/ev_display_bluetooth_ant/hardware/kicad-symbols/CPLD_Xilinx.kicad_sym"
    "/home/cas/work/TSDZ2/ev_display_bluetooth_ant/hardware/kicad-symbols/CPU.kicad_sym"
    "/home/cas/work/TSDZ2/ev_display_bluetooth_ant/hardware/kicad-symbols/CPU_NXP_6800.kicad_sym"
    "/home/cas/work/TSDZ2/ev_display_bluetooth_ant/hardware/kicad-symbols/CPU_NXP_68000.kicad_sym"
    "/home/cas/work/TSDZ2/ev_display_bluetooth_ant/hardware/kicad-symbols/CPU_NXP_IMX.kicad_sym"
    "/home/cas/work/TSDZ2/ev_display_bluetooth_ant/hardware/kicad-symbols/CPU_PowerPC.kicad_sym"
    "/home/cas/work/TSDZ2/ev_display_bluetooth_ant/hardware/kicad-symbols/Comparator.kicad_sym"
    "/home/cas/work/TSDZ2/ev_display_bluetooth_ant/hardware/kicad-symbols/Connector.kicad_sym"
    "/home/cas/work/TSDZ2/ev_display_bluetooth_ant/hardware/kicad-symbols/Connector_Generic.kicad_sym"
    "/home/cas/work/TSDZ2/ev_display_bluetooth_ant/hardware/kicad-symbols/Connector_Generic_MountingPin.kicad_sym"
    "/home/cas/work/TSDZ2/ev_display_bluetooth_ant/hardware/kicad-symbols/Connector_Generic_Shielded.kicad_sym"
    "/home/cas/work/TSDZ2/ev_display_bluetooth_ant/hardware/kicad-symbols/Converter_ACDC.kicad_sym"
    "/home/cas/work/TSDZ2/ev_display_bluetooth_ant/hardware/kicad-symbols/Converter_DCDC.kicad_sym"
    "/home/cas/work/TSDZ2/ev_display_bluetooth_ant/hardware/kicad-symbols/DSP_AnalogDevices.kicad_sym"
    "/home/cas/work/TSDZ2/ev_display_bluetooth_ant/hardware/kicad-symbols/DSP_Freescale.kicad_sym"
    "/home/cas/work/TSDZ2/ev_display_bluetooth_ant/hardware/kicad-symbols/DSP_Microchip_DSPIC33.kicad_sym"
    "/home/cas/work/TSDZ2/ev_display_bluetooth_ant/hardware/kicad-symbols/DSP_Motorola.kicad_sym"
    "/home/cas/work/TSDZ2/ev_display_bluetooth_ant/hardware/kicad-symbols/DSP_Texas.kicad_sym"
    "/home/cas/work/TSDZ2/ev_display_bluetooth_ant/hardware/kicad-symbols/Device.kicad_sym"
    "/home/cas/work/TSDZ2/ev_display_bluetooth_ant/hardware/kicad-symbols/Diode.kicad_sym"
    "/home/cas/work/TSDZ2/ev_display_bluetooth_ant/hardware/kicad-symbols/Diode_Bridge.kicad_sym"
    "/home/cas/work/TSDZ2/ev_display_bluetooth_ant/hardware/kicad-symbols/Diode_Laser.kicad_sym"
    "/home/cas/work/TSDZ2/ev_display_bluetooth_ant/hardware/kicad-symbols/Display_Character.kicad_sym"
    "/home/cas/work/TSDZ2/ev_display_bluetooth_ant/hardware/kicad-symbols/Display_Graphic.kicad_sym"
    "/home/cas/work/TSDZ2/ev_display_bluetooth_ant/hardware/kicad-symbols/Driver_Display.kicad_sym"
    "/home/cas/work/TSDZ2/ev_display_bluetooth_ant/hardware/kicad-symbols/Driver_FET.kicad_sym"
    "/home/cas/work/TSDZ2/ev_display_bluetooth_ant/hardware/kicad-symbols/Driver_Haptic.kicad_sym"
    "/home/cas/work/TSDZ2/ev_display_bluetooth_ant/hardware/kicad-symbols/Driver_LED.kicad_sym"
    "/home/cas/work/TSDZ2/ev_display_bluetooth_ant/hardware/kicad-symbols/Driver_Motor.kicad_sym"
    "/home/cas/work/TSDZ2/ev_display_bluetooth_ant/hardware/kicad-symbols/Driver_Relay.kicad_sym"
    "/home/cas/work/TSDZ2/ev_display_bluetooth_ant/hardware/kicad-symbols/Driver_TEC.kicad_sym"
    "/home/cas/work/TSDZ2/ev_display_bluetooth_ant/hardware/kicad-symbols/FPGA_Lattice.kicad_sym"
    "/home/cas/work/TSDZ2/ev_display_bluetooth_ant/hardware/kicad-symbols/FPGA_Microsemi.kicad_sym"
    "/home/cas/work/TSDZ2/ev_display_bluetooth_ant/hardware/kicad-symbols/FPGA_Xilinx.kicad_sym"
    "/home/cas/work/TSDZ2/ev_display_bluetooth_ant/hardware/kicad-symbols/FPGA_Xilinx_Artix7.kicad_sym"
    "/home/cas/work/TSDZ2/ev_display_bluetooth_ant/hardware/kicad-symbols/FPGA_Xilinx_Kintex7.kicad_sym"
    "/home/cas/work/TSDZ2/ev_display_bluetooth_ant/hardware/kicad-symbols/FPGA_Xilinx_Spartan6.kicad_sym"
    "/home/cas/work/TSDZ2/ev_display_bluetooth_ant/hardware/kicad-symbols/FPGA_Xilinx_Virtex5.kicad_sym"
    "/home/cas/work/TSDZ2/ev_display_bluetooth_ant/hardware/kicad-symbols/FPGA_Xilinx_Virtex6.kicad_sym"
    "/home/cas/work/TSDZ2/ev_display_bluetooth_ant/hardware/kicad-symbols/FPGA_Xilinx_Virtex7.kicad_sym"
    "/home/cas/work/TSDZ2/ev_display_bluetooth_ant/hardware/kicad-symbols/Fiber_Optic.kicad_sym"
    "/home/cas/work/TSDZ2/ev_display_bluetooth_ant/hardware/kicad-symbols/Filter.kicad_sym"
    "/home/cas/work/TSDZ2/ev_display_bluetooth_ant/hardware/kicad-symbols/GPU.kicad_sym"
    "/home/cas/work/TSDZ2/ev_display_bluetooth_ant/hardware/kicad-symbols/Graphic.kicad_sym"
    "/home/cas/work/TSDZ2/ev_display_bluetooth_ant/hardware/kicad-symbols/Interface.kicad_sym"
    "/home/cas/work/TSDZ2/ev_display_bluetooth_ant/hardware/kicad-symbols/Interface_CAN_LIN.kicad_sym"
    "/home/cas/work/TSDZ2/ev_display_bluetooth_ant/hardware/kicad-symbols/Interface_CurrentLoop.kicad_sym"
    "/home/cas/work/TSDZ2/ev_display_bluetooth_ant/hardware/kicad-symbols/Interface_Ethernet.kicad_sym"
    "/home/cas/work/TSDZ2/ev_display_bluetooth_ant/hardware/kicad-symbols/Interface_Expansion.kicad_sym"
    "/home/cas/work/TSDZ2/ev_display_bluetooth_ant/hardware/kicad-symbols/Interface_HDMI.kicad_sym"
    "/home/cas/work/TSDZ2/ev_display_bluetooth_ant/hardware/kicad-symbols/Interface_HID.kicad_sym"
    "/home/cas/work/TSDZ2/ev_display_bluetooth_ant/hardware/kicad-symbols/Interface_LineDriver.kicad_sym"
    "/home/cas/work/TSDZ2/ev_display_bluetooth_ant/hardware/kicad-symbols/Interface_Optical.kicad_sym"
    "/home/cas/work/TSDZ2/ev_display_bluetooth_ant/hardware/kicad-symbols/Interface_Telecom.kicad_sym"
    "/home/cas/work/TSDZ2/ev_display_bluetooth_ant/hardware/kicad-symbols/Interface_UART.kicad_sym"
    "/home/cas/work/TSDZ2/ev_display_bluetooth_ant/hardware/kicad-symbols/Interface_USB.kicad_sym"
    "/home/cas/work/TSDZ2/ev_display_bluetooth_ant/hardware/kicad-symbols/Isolator.kicad_sym"
    "/home/cas/work/TSDZ2/ev_display_bluetooth_ant/hardware/kicad-symbols/Isolator_Analog.kicad_sym"
    "/home/cas/work/TSDZ2/ev_display_bluetooth_ant/hardware/kicad-symbols/Jumper.kicad_sym"
    "/home/cas/work/TSDZ2/ev_display_bluetooth_ant/hardware/kicad-symbols/LED.kicad_sym"
    "/home/cas/work/TSDZ2/ev_display_bluetooth_ant/hardware/kicad-symbols/Logic_LevelTranslator.kicad_sym"
    "/home/cas/work/TSDZ2/ev_display_bluetooth_ant/hardware/kicad-symbols/Logic_Programmable.kicad_sym"
    "/home/cas/work/TSDZ2/ev_display_bluetooth_ant/hardware/kicad-symbols/MCU_AnalogDevices.kicad_sym"
    "/home/cas/work/TSDZ2/ev_display_bluetooth_ant/hardware/kicad-symbols/MCU_Cypress.kicad_sym"
    "/home/cas/work/TSDZ2/ev_display_bluetooth_ant/hardware/kicad-symbols/MCU_Dialog.kicad_sym"
    "/home/cas/work/TSDZ2/ev_display_bluetooth_ant/hardware/kicad-symbols/MCU_Espressif.kicad_sym"
    "/home/cas/work/TSDZ2/ev_display_bluetooth_ant/hardware/kicad-symbols/MCU_Intel.kicad_sym"
    "/home/cas/work/TSDZ2/ev_display_bluetooth_ant/hardware/kicad-symbols/MCU_Microchip_8051.kicad_sym"
    "/home/cas/work/TSDZ2/ev_display_bluetooth_ant/hardware/kicad-symbols/MCU_Microchip_ATmega.kicad_sym"
    "/home/cas/work/TSDZ2/ev_display_bluetooth_ant/hardware/kicad-symbols/MCU_Microchip_ATtiny.kicad_sym"
    "/home/cas/work/TSDZ2/ev_display_bluetooth_ant/hardware/kicad-symbols/MCU_Microchip_AVR.kicad_sym"
    "/home/cas/work/TSDZ2/ev_display_bluetooth_ant/hardware/kicad-symbols/MCU_Microchip_PIC10.kicad_sym"
    "/home/cas/work/TSDZ2/ev_display_bluetooth_ant/hardware/kicad-symbols/MCU_Microchip_PIC12.kicad_sym"
    "/home/cas/work/TSDZ2/ev_display_bluetooth_ant/hardware/kicad-symbols/MCU_Microchip_PIC16.kicad_sym"
    "/home/cas/work/TSDZ2/ev_display_bluetooth_ant/hardware/kicad-symbols/MCU_Microchip_PIC18.kicad_sym"
    "/home/cas/work/TSDZ2/ev_display_bluetooth_ant/hardware/kicad-symbols/MCU_Microchip_PIC24.kicad_sym"
    "/home/cas/work/TSDZ2/ev_display_bluetooth_ant/hardware/kicad-symbols/MCU_Microchip_PIC32.kicad_sym"
    "/home/cas/work/TSDZ2/ev_display_bluetooth_ant/hardware/kicad-symbols/MCU_Microchip_SAMA.kicad_sym"
    "/home/cas/work/TSDZ2/ev_display_bluetooth_ant/hardware/kicad-symbols/MCU_Microchip_SAMD.kicad_sym"
    "/home/cas/work/TSDZ2/ev_display_bluetooth_ant/hardware/kicad-symbols/MCU_Microchip_SAME.kicad_sym"
    "/home/cas/work/TSDZ2/ev_display_bluetooth_ant/hardware/kicad-symbols/MCU_Microchip_SAML.kicad_sym"
    "/home/cas/work/TSDZ2/ev_display_bluetooth_ant/hardware/kicad-symbols/MCU_Microchip_SAMV.kicad_sym"
    "/home/cas/work/TSDZ2/ev_display_bluetooth_ant/hardware/kicad-symbols/MCU_Module.kicad_sym"
    "/home/cas/work/TSDZ2/ev_display_bluetooth_ant/hardware/kicad-symbols/MCU_NXP_ColdFire.kicad_sym"
    "/home/cas/work/TSDZ2/ev_display_bluetooth_ant/hardware/kicad-symbols/MCU_NXP_HC11.kicad_sym"
    "/home/cas/work/TSDZ2/ev_display_bluetooth_ant/hardware/kicad-symbols/MCU_NXP_HC12.kicad_sym"
    "/home/cas/work/TSDZ2/ev_display_bluetooth_ant/hardware/kicad-symbols/MCU_NXP_HCS12.kicad_sym"
    "/home/cas/work/TSDZ2/ev_display_bluetooth_ant/hardware/kicad-symbols/MCU_NXP_Kinetis.kicad_sym"
    "/home/cas/work/TSDZ2/ev_display_bluetooth_ant/hardware/kicad-symbols/MCU_NXP_LPC.kicad_sym"
    "/home/cas/work/TSDZ2/ev_display_bluetooth_ant/hardware/kicad-symbols/MCU_NXP_MAC7100.kicad_sym"
    "/home/cas/work/TSDZ2/ev_display_bluetooth_ant/hardware/kicad-symbols/MCU_NXP_MCore.kicad_sym"
    "/home/cas/work/TSDZ2/ev_display_bluetooth_ant/hardware/kicad-symbols/MCU_NXP_NTAG.kicad_sym"
    "/home/cas/work/TSDZ2/ev_display_bluetooth_ant/hardware/kicad-symbols/MCU_NXP_S08.kicad_sym"
    "/home/cas/work/TSDZ2/ev_display_bluetooth_ant/hardware/kicad-symbols/MCU_Nordic.kicad_sym"
    "/home/cas/work/TSDZ2/ev_display_bluetooth_ant/hardware/kicad-symbols/MCU_Parallax.kicad_sym"
    "/home/cas/work/TSDZ2/ev_display_bluetooth_ant/hardware/kicad-symbols/MCU_Renesas_Synergy_S1.kicad_sym"
    "/home/cas/work/TSDZ2/ev_display_bluetooth_ant/hardware/kicad-symbols/MCU_STC.kicad_sym"
    "/home/cas/work/TSDZ2/ev_display_bluetooth_ant/hardware/kicad-symbols/MCU_ST_STM32F0.kicad_sym"
    "/home/cas/work/TSDZ2/ev_display_bluetooth_ant/hardware/kicad-symbols/MCU_ST_STM32F1.kicad_sym"
    "/home/cas/work/TSDZ2/ev_display_bluetooth_ant/hardware/kicad-symbols/MCU_ST_STM32F2.kicad_sym"
    "/home/cas/work/TSDZ2/ev_display_bluetooth_ant/hardware/kicad-symbols/MCU_ST_STM32F3.kicad_sym"
    "/home/cas/work/TSDZ2/ev_display_bluetooth_ant/hardware/kicad-symbols/MCU_ST_STM32F4.kicad_sym"
    "/home/cas/work/TSDZ2/ev_display_bluetooth_ant/hardware/kicad-symbols/MCU_ST_STM32F7.kicad_sym"
    "/home/cas/work/TSDZ2/ev_display_bluetooth_ant/hardware/kicad-symbols/MCU_ST_STM32G0.kicad_sym"
    "/home/cas/work/TSDZ2/ev_display_bluetooth_ant/hardware/kicad-symbols/MCU_ST_STM32H7.kicad_sym"
    "/home/cas/work/TSDZ2/ev_display_bluetooth_ant/hardware/kicad-symbols/MCU_ST_STM32L0.kicad_sym"
    "/home/cas/work/TSDZ2/ev_display_bluetooth_ant/hardware/kicad-symbols/MCU_ST_STM32L1.kicad_sym"
    "/home/cas/work/TSDZ2/ev_display_bluetooth_ant/hardware/kicad-symbols/MCU_ST_STM32L4+.kicad_sym"
    "/home/cas/work/TSDZ2/ev_display_bluetooth_ant/hardware/kicad-symbols/MCU_ST_STM32L4.kicad_sym"
    "/home/cas/work/TSDZ2/ev_display_bluetooth_ant/hardware/kicad-symbols/MCU_ST_STM8.kicad_sym"
    "/home/cas/work/TSDZ2/ev_display_bluetooth_ant/hardware/kicad-symbols/MCU_SiFive.kicad_sym"
    "/home/cas/work/TSDZ2/ev_display_bluetooth_ant/hardware/kicad-symbols/MCU_SiliconLabs.kicad_sym"
    "/home/cas/work/TSDZ2/ev_display_bluetooth_ant/hardware/kicad-symbols/MCU_Texas.kicad_sym"
    "/home/cas/work/TSDZ2/ev_display_bluetooth_ant/hardware/kicad-symbols/MCU_Texas_MSP430.kicad_sym"
    "/home/cas/work/TSDZ2/ev_display_bluetooth_ant/hardware/kicad-symbols/MCU_Texas_SimpleLink.kicad_sym"
    "/home/cas/work/TSDZ2/ev_display_bluetooth_ant/hardware/kicad-symbols/Mechanical.kicad_sym"
    "/home/cas/work/TSDZ2/ev_display_bluetooth_ant/hardware/kicad-symbols/Memory_EEPROM.kicad_sym"
    "/home/cas/work/TSDZ2/ev_display_bluetooth_ant/hardware/kicad-symbols/Memory_EPROM.kicad_sym"
    "/home/cas/work/TSDZ2/ev_display_bluetooth_ant/hardware/kicad-symbols/Memory_Flash.kicad_sym"
    "/home/cas/work/TSDZ2/ev_display_bluetooth_ant/hardware/kicad-symbols/Memory_NVRAM.kicad_sym"
    "/home/cas/work/TSDZ2/ev_display_bluetooth_ant/hardware/kicad-symbols/Memory_RAM.kicad_sym"
    "/home/cas/work/TSDZ2/ev_display_bluetooth_ant/hardware/kicad-symbols/Memory_ROM.kicad_sym"
    "/home/cas/work/TSDZ2/ev_display_bluetooth_ant/hardware/kicad-symbols/Memory_UniqueID.kicad_sym"
    "/home/cas/work/TSDZ2/ev_display_bluetooth_ant/hardware/kicad-symbols/Motor.kicad_sym"
    "/home/cas/work/TSDZ2/ev_display_bluetooth_ant/hardware/kicad-symbols/Oscillator.kicad_sym"
    "/home/cas/work/TSDZ2/ev_display_bluetooth_ant/hardware/kicad-symbols/Potentiometer_Digital.kicad_sym"
    "/home/cas/work/TSDZ2/ev_display_bluetooth_ant/hardware/kicad-symbols/Power_Management.kicad_sym"
    "/home/cas/work/TSDZ2/ev_display_bluetooth_ant/hardware/kicad-symbols/Power_Protection.kicad_sym"
    "/home/cas/work/TSDZ2/ev_display_bluetooth_ant/hardware/kicad-symbols/Power_Supervisor.kicad_sym"
    "/home/cas/work/TSDZ2/ev_display_bluetooth_ant/hardware/kicad-symbols/RF.kicad_sym"
    "/home/cas/work/TSDZ2/ev_display_bluetooth_ant/hardware/kicad-symbols/RF_AM_FM.kicad_sym"
    "/home/cas/work/TSDZ2/ev_display_bluetooth_ant/hardware/kicad-symbols/RF_Amplifier.kicad_sym"
    "/home/cas/work/TSDZ2/ev_display_bluetooth_ant/hardware/kicad-symbols/RF_Bluetooth.kicad_sym"
    "/home/cas/work/TSDZ2/ev_display_bluetooth_ant/hardware/kicad-symbols/RF_Filter.kicad_sym"
    "/home/cas/work/TSDZ2/ev_display_bluetooth_ant/hardware/kicad-symbols/RF_GPS.kicad_sym"
    "/home/cas/work/TSDZ2/ev_display_bluetooth_ant/hardware/kicad-symbols/RF_GSM.kicad_sym"
    "/home/cas/work/TSDZ2/ev_display_bluetooth_ant/hardware/kicad-symbols/RF_Mixer.kicad_sym"
    "/home/cas/work/TSDZ2/ev_display_bluetooth_ant/hardware/kicad-symbols/RF_Module.kicad_sym"
    "/home/cas/work/TSDZ2/ev_display_bluetooth_ant/hardware/kicad-symbols/RF_NFC.kicad_sym"
    "/home/cas/work/TSDZ2/ev_display_bluetooth_ant/hardware/kicad-symbols/RF_RFID.kicad_sym"
    "/home/cas/work/TSDZ2/ev_display_bluetooth_ant/hardware/kicad-symbols/RF_Switch.kicad_sym"
    "/home/cas/work/TSDZ2/ev_display_bluetooth_ant/hardware/kicad-symbols/RF_WiFi.kicad_sym"
    "/home/cas/work/TSDZ2/ev_display_bluetooth_ant/hardware/kicad-symbols/RF_ZigBee.kicad_sym"
    "/home/cas/work/TSDZ2/ev_display_bluetooth_ant/hardware/kicad-symbols/Reference_Current.kicad_sym"
    "/home/cas/work/TSDZ2/ev_display_bluetooth_ant/hardware/kicad-symbols/Reference_Voltage.kicad_sym"
    "/home/cas/work/TSDZ2/ev_display_bluetooth_ant/hardware/kicad-symbols/Regulator_Controller.kicad_sym"
    "/home/cas/work/TSDZ2/ev_display_bluetooth_ant/hardware/kicad-symbols/Regulator_Current.kicad_sym"
    "/home/cas/work/TSDZ2/ev_display_bluetooth_ant/hardware/kicad-symbols/Regulator_Linear.kicad_sym"
    "/home/cas/work/TSDZ2/ev_display_bluetooth_ant/hardware/kicad-symbols/Regulator_SwitchedCapacitor.kicad_sym"
    "/home/cas/work/TSDZ2/ev_display_bluetooth_ant/hardware/kicad-symbols/Regulator_Switching.kicad_sym"
    "/home/cas/work/TSDZ2/ev_display_bluetooth_ant/hardware/kicad-symbols/Relay.kicad_sym"
    "/home/cas/work/TSDZ2/ev_display_bluetooth_ant/hardware/kicad-symbols/Relay_SolidState.kicad_sym"
    "/home/cas/work/TSDZ2/ev_display_bluetooth_ant/hardware/kicad-symbols/Security.kicad_sym"
    "/home/cas/work/TSDZ2/ev_display_bluetooth_ant/hardware/kicad-symbols/Sensor.kicad_sym"
    "/home/cas/work/TSDZ2/ev_display_bluetooth_ant/hardware/kicad-symbols/Sensor_Audio.kicad_sym"
    "/home/cas/work/TSDZ2/ev_display_bluetooth_ant/hardware/kicad-symbols/Sensor_Current.kicad_sym"
    "/home/cas/work/TSDZ2/ev_display_bluetooth_ant/hardware/kicad-symbols/Sensor_Distance.kicad_sym"
    "/home/cas/work/TSDZ2/ev_display_bluetooth_ant/hardware/kicad-symbols/Sensor_Gas.kicad_sym"
    "/home/cas/work/TSDZ2/ev_display_bluetooth_ant/hardware/kicad-symbols/Sensor_Humidity.kicad_sym"
    "/home/cas/work/TSDZ2/ev_display_bluetooth_ant/hardware/kicad-symbols/Sensor_Magnetic.kicad_sym"
    "/home/cas/work/TSDZ2/ev_display_bluetooth_ant/hardware/kicad-symbols/Sensor_Motion.kicad_sym"
    "/home/cas/work/TSDZ2/ev_display_bluetooth_ant/hardware/kicad-symbols/Sensor_Optical.kicad_sym"
    "/home/cas/work/TSDZ2/ev_display_bluetooth_ant/hardware/kicad-symbols/Sensor_Pressure.kicad_sym"
    "/home/cas/work/TSDZ2/ev_display_bluetooth_ant/hardware/kicad-symbols/Sensor_Proximity.kicad_sym"
    "/home/cas/work/TSDZ2/ev_display_bluetooth_ant/hardware/kicad-symbols/Sensor_Temperature.kicad_sym"
    "/home/cas/work/TSDZ2/ev_display_bluetooth_ant/hardware/kicad-symbols/Sensor_Touch.kicad_sym"
    "/home/cas/work/TSDZ2/ev_display_bluetooth_ant/hardware/kicad-symbols/Sensor_Voltage.kicad_sym"
    "/home/cas/work/TSDZ2/ev_display_bluetooth_ant/hardware/kicad-symbols/Simulation_SPICE.kicad_sym"
    "/home/cas/work/TSDZ2/ev_display_bluetooth_ant/hardware/kicad-symbols/Switch.kicad_sym"
    "/home/cas/work/TSDZ2/ev_display_bluetooth_ant/hardware/kicad-symbols/Timer.kicad_sym"
    "/home/cas/work/TSDZ2/ev_display_bluetooth_ant/hardware/kicad-symbols/Timer_PLL.kicad_sym"
    "/home/cas/work/TSDZ2/ev_display_bluetooth_ant/hardware/kicad-symbols/Timer_RTC.kicad_sym"
    "/home/cas/work/TSDZ2/ev_display_bluetooth_ant/hardware/kicad-symbols/Transformer.kicad_sym"
    "/home/cas/work/TSDZ2/ev_display_bluetooth_ant/hardware/kicad-symbols/Transistor_Array.kicad_sym"
    "/home/cas/work/TSDZ2/ev_display_bluetooth_ant/hardware/kicad-symbols/Transistor_BJT.kicad_sym"
    "/home/cas/work/TSDZ2/ev_display_bluetooth_ant/hardware/kicad-symbols/Transistor_FET.kicad_sym"
    "/home/cas/work/TSDZ2/ev_display_bluetooth_ant/hardware/kicad-symbols/Transistor_IGBT.kicad_sym"
    "/home/cas/work/TSDZ2/ev_display_bluetooth_ant/hardware/kicad-symbols/Triac_Thyristor.kicad_sym"
    "/home/cas/work/TSDZ2/ev_display_bluetooth_ant/hardware/kicad-symbols/Valve.kicad_sym"
    "/home/cas/work/TSDZ2/ev_display_bluetooth_ant/hardware/kicad-symbols/Video.kicad_sym"
    "/home/cas/work/TSDZ2/ev_display_bluetooth_ant/hardware/kicad-symbols/power.kicad_sym"
    "/home/cas/work/TSDZ2/ev_display_bluetooth_ant/hardware/kicad-symbols/pspice.kicad_sym"
    )
endif()

if("x${CMAKE_INSTALL_COMPONENT}x" STREQUAL "xresourcesx" OR NOT CMAKE_INSTALL_COMPONENT)
  file(INSTALL DESTINATION "${CMAKE_INSTALL_PREFIX}/share/kicad/template" TYPE FILE FILES "/home/cas/work/TSDZ2/ev_display_bluetooth_ant/hardware/kicad-symbols/sym-lib-table")
endif()

if(CMAKE_INSTALL_COMPONENT)
  set(CMAKE_INSTALL_MANIFEST "install_manifest_${CMAKE_INSTALL_COMPONENT}.txt")
else()
  set(CMAKE_INSTALL_MANIFEST "install_manifest.txt")
endif()

string(REPLACE ";" "\n" CMAKE_INSTALL_MANIFEST_CONTENT
       "${CMAKE_INSTALL_MANIFEST_FILES}")
file(WRITE "/home/cas/work/TSDZ2/ev_display_bluetooth_ant/hardware/kicad-symbols/${CMAKE_INSTALL_MANIFEST}"
     "${CMAKE_INSTALL_MANIFEST_CONTENT}")

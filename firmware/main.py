import board
import buttons
import display_sh1106
import ebike_board
import ebike_data
import time
import displayio
from adafruit_display_text import label
import terminalio


buttons = buttons.Buttons(
        board.IO33, # POWER
        board.IO37, # UP
        board.IO35) # DOWN

displayObject = display_sh1106.Display(
        board.IO7, # CLK pin
        board.IO9, # MOSI pin
        board.IO5, # chip select pin, not used but for some reason there is an error if chip_select is None
        board.IO12, # command pin
        board.IO11, # reset pin
        1000000) # spi clock frequency
display = displayObject.display

ebike_data = ebike_data.EBike()
ebike = ebike_board.EBikeBoard(
    board.IO18, # UART TX pin that connect to display UART RX pin
    board.IO17, # UART RX pin that connect to display UART TX pin
    ebike_data) # EBike data object to hold the EBike data

DISPLAY_WIDTH = 64  
DISPLAY_HEIGHT = 128
TEXT = "0"

def motor_power_round(motor_power):

    if motor_power < 10:
        motor_power = 0
    elif motor_power < 20:
        motor_power /= 2.5
        motor_power *= 2.5
    elif motor_power < 100:
        motor_power /= 5
        motor_power *= 5
    elif motor_power < 250:
        motor_power /= 10
        motor_power *= 10
    elif motor_power < 500:
        motor_power /= 20
        motor_power *= 20
    elif motor_power < 500:
        motor_power /= 25
        motor_power *= 25

    return int(motor_power)

assist_level_area = label.Label(terminalio.FONT, text=TEXT)
assist_level_area.anchor_point = (0.0, 0.0)
assist_level_area.anchored_position = (4, 0)
assist_level_area.scale = 2

battery_voltage_area = label.Label(terminalio.FONT, text=TEXT)
battery_voltage_area.anchor_point = (0.0, 0.0)
battery_voltage_area.anchored_position = (34, 0)
battery_voltage_area.scale = 1

label_x = 1
label_y = 22
label_y_offset = 32
label_1 = label.Label(terminalio.FONT, text=TEXT)
label_1.anchor_point = (0.0, 0.0)
label_1.anchored_position = (label_x, label_y)
label_1.scale = 2

label_y += label_y_offset
label_2 = label.Label(terminalio.FONT, text=TEXT)
label_2.anchor_point = (0.0, 0.0)
label_2.anchored_position = (label_x, label_y)
label_2.scale = 2

label_y += label_y_offset
label_3 = label.Label(terminalio.FONT, text=TEXT)
label_3.anchor_point = (0.0, 0.0)
label_3.anchored_position = (label_x, label_y)
label_3.scale = 2

text_group = displayio.Group()
text_group.append(assist_level_area)
text_group.append(battery_voltage_area)
text_group.append(label_1)
text_group.append(label_2)
text_group.append(label_3)

display.show(text_group)

assist_level = 0
assist_level_state = 0
now = time.monotonic()
assist_level_time_previous = now
display_time_previous = now

battery_voltage_previous = 9999
motor_power_previous = 9999
motor_temperature_sensor_x10_previous = 9999
vesc_temperature_x10_previous = 9999

while True:
    now = time.monotonic()
    if (now - display_time_previous) > 1.0:
        display_time_previous = now

        if battery_voltage_previous != ebike_data.battery_voltage:
            battery_voltage_previous = ebike_data.battery_voltage
            battery_voltage_area.text = str(f"{ebike_data.battery_voltage:2.1f}v")

        if motor_power_previous != ebike_data.motor_power:
            motor_power_previous = ebike_data.motor_power
            motor_power = motor_power_round(ebike_data.motor_power)
            label_1.text = str(f"{motor_power:5}")
        
        if motor_temperature_sensor_x10_previous != ebike_data.motor_temperature_sensor_x10:
            motor_temperature_sensor_x10_previous = ebike_data.motor_temperature_sensor_x10  
            label_2.text = str(f"{(ebike_data.motor_temperature_sensor_x10 / 10.0): 2.1f}")

        if vesc_temperature_x10_previous != ebike_data.vesc_temperature_x10:
            vesc_temperature_x10_previous = ebike_data.vesc_temperature_x10  
            label_3.text = str(f"{(ebike_data.vesc_temperature_x10 / 10.0): 2.1f}")    

    ebike.process_data()

    now = time.monotonic()
    if (now - assist_level_time_previous) > 0.05:
        assist_level_time_previous = now

        # change assist level
        if assist_level_state == 1 and not buttons.up:
            assist_level_state = 0

        if assist_level_state == 2 and not buttons.down:
            assist_level_state = 0

        if assist_level < 20 and buttons.up and assist_level_state == 0:
            assist_level_state = 1
            assist_level += 1

        if assist_level > 0 and buttons.down and assist_level_state == 0:
            assist_level_state = 2
            assist_level -= 1

        ebike_data.assist_level = assist_level
        assist_level_area.text = str(assist_level)

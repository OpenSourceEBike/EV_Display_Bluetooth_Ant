import board
import buttons
import display_sh1106
import displayio
import time
from adafruit_display_text import label
from fruity_menu.menu import Menu

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

while True:
    power = "enable" if buttons.power else "disable"
    up = "enable" if buttons.up else "disable"
    down = "enable" if buttons.down else "disable"

    print( )
    print(f"POWER button: {power}")
    print(f"UP button: {up}")
    print(f"DOWN button: {down}")

    time.sleep(1)

# SPDX-FileCopyrightText: 2021 ladyada for Adafruit Industries
# SPDX-License-Identifier: MIT

"""
This test will initialize the display using displayio and draw a solid white
background, a smaller black rectangle, and some white text.
"""
import time
import board
import busio
import displayio
import terminalio
from adafruit_display_text import label
import adafruit_displayio_sh1106

displayio.release_displays()

spi = busio.SPI(
    board.IO7, # CLK pin
    board.IO9, # MOSI pin
    None) # MISO pin, not need to drive this display

display_bus = displayio.FourWire(spi,
                                 command = board.IO12,
                                 reset = board.IO11,
                                 chip_select = board.IO5,
                                 baudrate = 1000000)

WIDTH = 132
HEIGHT = 64
BORDER = 5

display = adafruit_displayio_sh1106.SH1106(display_bus, width=WIDTH, height=HEIGHT)

# Make the display context
splash = displayio.Group()
display.show(splash)

color_bitmap = displayio.Bitmap(WIDTH, HEIGHT, 1)
color_palette = displayio.Palette(1)
color_palette[0] = 0xFFFFFF  # White

bg_sprite = displayio.TileGrid(color_bitmap, pixel_shader=color_palette, x=0, y=0)
splash.append(bg_sprite)

# Draw a smaller inner rectangle
inner_bitmap = displayio.Bitmap(WIDTH - BORDER * 2, HEIGHT - BORDER * 2, 1)
inner_palette = displayio.Palette(1)
inner_palette[0] = 0x000000  # Black
inner_sprite = displayio.TileGrid(
    inner_bitmap, pixel_shader=inner_palette, x=BORDER, y=BORDER
)
splash.append(inner_sprite)

# Draw a label
text = "Hello World!"
text_area = label.Label(
    terminalio.FONT, text=text, color=0xFFFFFF, x=28, y=HEIGHT // 2 - 1
)
splash.append(text_area)

counter = 0

while True:

    # Draw a label
    text = f"{counter}"
    splash.remove(text_area)
    text_area = label.Label(
        terminalio.FONT, text=text, color=0xFFFFFF, x=28, y=HEIGHT // 2 - 1
    )
    splash.append(text_area)

    counter += 1
    print(f"test {counter}")
    time.sleep(1)
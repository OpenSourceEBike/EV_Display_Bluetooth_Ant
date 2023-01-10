import board
import display_sh1106
import terminalio
from adafruit_display_text import label

displayObject = display_sh1106.Display(
    board.IO7, # CLK pin
    board.IO9, # MOSI pin
    board.IO5, # chip select pin, not used but for some reason there is an error if chip_select is None
    board.IO12, # command pin
    board.IO11, # reset pin
    1000000) # spi clock frequency
display = displayObject.display

# Set text, font, and color
text = "HELLO"
font = terminalio.FONT
color = 0xFFFFFF

# Create the text label
text_area = label.Label(font, text=text, color=color)

# Set the location
text_area.x = 2
text_area.y = int(text_area.height / 2)

# Show it
display.show(text_area)

# Loop forever so you can enjoy your image
while True:
    pass
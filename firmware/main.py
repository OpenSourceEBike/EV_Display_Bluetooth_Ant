import board
import display_sh1106
import displayio
import time
from adafruit_display_text import label
from fruity_menu.menu import Menu

displayObject = display_sh1106.Display(
    board.IO7, # CLK pin
    board.IO9, # MOSI pin
    board.IO5, # chip select pin, not used but for some reason there is an error if chip_select is None
    board.IO12, # command pin
    board.IO11, # reset pin
    1000000) # spi clock frequency
display = displayObject.display

def test1():
    print("test 1")

def test2():
    print("test 2")

def test3():
    print("test 3")

menu = Menu(display, 64, 132, title='Menu', )
menu.add_action_button('one', action = test1)

menu_2 = Menu(display, 64, 132, title='M 2', )
menu_2.add_action_button('ONE 1', action = test1)

menu.add_action_button('two', action = test2)
menu.add_action_button('3', action = test3)
menu.add_submenu_button('sub one', menu_2)

menu.add_value_button("t", 10, None, None, 1, 0, 100)


# Loop forever so you can enjoy your image
while True:
    menu.scroll(1)
    menu.click()
    menu.show_menu()
    time.sleep(1)

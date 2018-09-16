#!/usr/bin/env python3.6

from comm import SoombaBot
import contextlib
import platform
from time import sleep
import keyboard

def main():
    with contextlib.closing(SoombaBot()) as soomba_bot:
        while True:
            if keyboard.is_pressed('w'):
                soomba_bot.execute('up')
            elif keyboard.is_pressed('s'):
                soomba_bot.execute('down')
            elif keyboard.is_pressed('a'):
                soomba_bot.execute('left')
            elif keyboard.is_pressed('d'):
                soomba_bot.execute('right')
            sleep(0.05)

if __name__ == '__main__':
    if platform.system() == 'Windows':
        # this is necessary (albeit proactive) because on Windows, if
        # there was an error, it would immediately exit and we would
        # have no way of debugging.
        import atexit
        atexit.register(lambda: input('Press enter to exit\n'))
    main()

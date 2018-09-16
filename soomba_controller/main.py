#!/usr/bin/env python2.7

from comm import SoombaBot
import contextlib
import platform
from time import sleep
import curses
import cv2
import sys
from random import randint

def main(screen):
    with contextlib.closing(SoombaBot()) as soomba_bot:
        sleep(5)
        while True:
            key = screen.getkey()
            if key == 'w': 
                soomba_bot.execute('up')
            elif key == 's': 
                soomba_bot.execute('down')
            elif key == 'a': 
                soomba_bot.execute('left')
            elif key == 'd': 
                soomba_bot.execute('right')
            else:
                print("o")
                if randint(0, 20) == 7:
                    soomba_bot.execute('right')
                elif randint(0, 20) == 7:
                    soomba_bot.execute('left')
                elif randint(0, 100) == 7:
                    for i in range(3):
                        soomba_bot.execute('left')
                elif randint(0, 100) == 7:
                    for i in range(3):
                        soomba_bot.execute('right')
                elif randint(0, 50) == 7:
                    soomba_bot.execute('down')
                else:
                    soomba_bot.execute('up')

if __name__ == '__main__':
    if platform.system() == 'Windows':
        # this is necessary (albeit proactive) because on Windows, if
        # there was an error, it would immediately exit and we would
        # have no way of debugging.
        import atexit
        atexit.register(lambda: input('Press enter to exit\n'))

    curses.wrapper(main)

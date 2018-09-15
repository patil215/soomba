#!/usr/bin/env python3.6

from comm import SoombaBot
import contextlib
import platform

def main():
    with contextlib.closing(SoombaBot()) as soomba_bot:
        soomba_bot.execute('left')
        soomba_bot.execute('poop')

if __name__ == '__main__':
    if platform.system() == 'Windows':
        # this is necessary (albeit proactive) because on Windows, if
        # there was an error, it would immediately exit and we would
        # have no way of debugging.
        import atexit
        atexit.register(lambda: input('Press enter to exit\n'))
    main()

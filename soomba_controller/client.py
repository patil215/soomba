#!/usr/bin/env python3.6

import keyboard
import requests
from time import sleep
HOST = "http://192.168.43.254:5000"
def send(command):
    print("waddup")
    requests.get(HOST+"?command=" + command)

def main():
    while True:
        if keyboard.is_pressed('w'):
            send('up')
            sleep(.2)
        elif keyboard.is_pressed('s'):
            send('down')
            sleep(.2)
        elif keyboard.is_pressed('a'):
            send('left')
            sleep(.2)
        elif keyboard.is_pressed('d'):
            send('right')
            sleep(.2)
        sleep(0.05)

if __name__ == '__main__':
    main()

#!/usr/bin/env python3.6

import keyboard
import requests
HOST = "http://192.168.1.34/"
def send(command):
    requests.get(HOST+"?command=" + command)
def main():
    while True:
        if keyboard.is_pressed('w'):
            send('up')
        elif keyboard.is_pressed('s'):
            send('down')
        elif keyboard.is_pressed('a'):
            send('left')
        elif keyboard.is_pressed('d'):
            send('right')
        sleep(0.05)

if __name__ == '__main__':
    main()

#!/usr/bin/env python3.6

from comm import SoombaBot
import contextlib
import platform
from time import sleep
import curses
import cv2
import sys


#import keyboard

def main(screen):
    cascPath = "haarcascade_frontalface_default.xml"
    faceCascade = cv2.CascadeClassifier(cascPath)
    font=cv2.FONT_HERSHEY_SIMPLEX
    video_capture = cv2.VideoCapture(0)

    ret, frame = video_capture.read()
    gray = cv2.cvtColor(frame, cv2.COLOR_BGR2GRAY)


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
                # CAPTURE FRAME-BY-FRAME
                ret, frame = video_capture.read()

                gray = cv2.cvtColor(frame, cv2.COLOR_BGR2GRAY)
                print(gray.shape)

                faces = faceCascade.detectMultiScale(
                    gray,
                    scaleFactor=1.1,
                    minNeighbors=5,
                    minSize=(50, 50),
                    #when the values are smallers, the face to detect can be smaller
                    flags=cv2.cv.CV_HAAR_SCALE_IMAGE

                )

                if len(faces) < 1:
                    print("didn't find any faces")
                    continue

                face = faces[0]
                x = face[0]
                w = face[2]
                print(str(x) + " " + str(w))
                center_x = x + (w / 2)
                if center_x < ((640 / 2) + 100):
                    soomba_bot.execute('right')
                elif center_x > ((640 / 2) - 100):
                    soomba_bot.execute('left')
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

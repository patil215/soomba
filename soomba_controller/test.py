# -*- coding: utf-8 -*-
import cv2
import sys
x=0
y=0

cascPath = "haarcascade_frontalface_default.xml"
faceCascade = cv2.CascadeClassifier(cascPath)
font=cv2.FONT_HERSHEY_SIMPLEX
video_capture = cv2.VideoCapture(0)
from time import sleep
from comm import SoombaBot
import contextlib

with contextlib.closing(SoombaBot()) as soomba_bot:
    sleep(5)
    while True:
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
            continue

        face = faces[0]
        x = face[0]
        w = face[2]
        print(str(x) + " " + str(w))
        center_x = x + (w / 2)
        if center_x > ((640 / 2) + 150):
            soomba_bot.execute('right')
        elif center_x < ((640 / 2) - 150):
            soomba_bot.execute('left')
        else:
            soomba_bot.execute('up')

        if cv2.waitKey(1) & 0xFF == ord('q'):
            break

    # When everything is done, release the capture
    video_capture.release()

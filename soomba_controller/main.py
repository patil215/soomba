#!/usr/bin/env python3.6

from comm import SoombaBot
import contextlib
from time import sleep
from flask import Flask, request

app = Flask(__name__)

soomba_bot = SoombaBot()
sleep(5)

@app.route("/")
def hello():
    command = request.args.get('command')
    soomba_bot.execute(command)
    return "waddup"

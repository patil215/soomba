#!/usr/bin/env python3.6

from comm import SoombaBot
import contextlib
import platform
from time import sleep
import flask
app = Flask(__name__)

@app.route("/")
def hello():
    command = request.args.get('command')
    soomba_bot.execute(command)

if __name__ == '__main__':
    main()

import re
import serial
import serial.tools.list_ports

BAUD_RATE = 9600

class SoombaBotError(RuntimeError):
    pass

class SoombaBot(object):
    def __init__(self, default_port_name=None):
        ports = list(serial.tools.list_ports.comports())

        if len(ports) == 0:
            raise RuntimeError('SoombaBot not found.')
        elif len(ports) == 1:
            port_name = ports[0][0]
        else:
            if default_port_name is not None:
                port_name = default_port_name
            else:
                for i, (port, desc, hwid) in enumerate(ports):
                    print(f'{i:> 2d} {port:<10s} {desc:10<s} {hwid:10<s}')
                choice = int(input())
                port_name = ports[choice][0]
        self._serial = serial.Serial(port_name, BAUD_RATE)

    def close(self):
        self._serial.close()

    def execute(self, command):
        self._write_line(command)
        resp = self._read_line().split(' ')
        if resp[0] == 'bad':
            raise SoombaBotError(resp[1])

    def _write_line(self, line):
        self._serial.write(line.encode('ascii') + b'\n')

    def _read_line(self):
        temp = b''
        while True:
            ch = self._serial.read()
            if ch == '\n':
                break
            else:
                temp += ch
        return tmp.decode('ascii')

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
                    print('{i} {port} {desc:} {hwid}'.format(i=i, port=port, desc=desc, hwid=hwid))
                choice = int(input())
                port_name = ports[choice][0]
        print(port_name)
        self._serial = serial.Serial(port_name, BAUD_RATE, timeout=0)

    def close(self):
        self._serial.close()

    def execute(self, command):
        self._write_line(command)
        resp = self._read_line()
        resp = resp.split(' ')
        if resp[0] == 'bad':
            #raise SoombaBotError(resp[1])
            pass

    def _write_line(self, line):
        self._serial.write(line.encode('ascii') + b'\n')

    def _read_line(self):
        line = self._serial.readline()
        return line.decode('ascii')

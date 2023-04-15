from microbit import *
import dht11
import Obloq

SSID = ''
PASSWORD = ''
IP = ''
PORT = ''
ID = 1

def ConnectWifi(SSID, PASSWORD):
  while Obloq.connectWifi(SSID,PASSWORD,10000) != True:
    display.show(".")
  display.scroll(Obloq.ifconfig())
  Obloq.httpConfig(IP,PORT)

def Upload(data):
  errno, resp = Obloq.get("input?%s" % data,10000)
  return (errno, resp)

def Init():
  uart.init(baudrate=9600, bits=8, parity=None, stop=1, tx=pin2, rx=pin1)
  ConnectWifi(SSID, PASSWORD)

if __name__ == '__main__':
  Init()
  while True:
    f = microbit.compass.get_field_strength()
    Upload('id=%d&rawdata=%d' % (ID, f))
    g = dht11.read(pin)
    Upload('id=%d&rawdata=%f' % (ID, g))
    sleep(1000)

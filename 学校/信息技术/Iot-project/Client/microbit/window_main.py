import microbit
import dht11

class Obloq(object):
  def connectWifi(self, SSID, PASSWORD, TIME):
    uart.write('AT_CWJAP="%s","%s"\r\n' % (SSID, PASSWORD))
    display.scroll("wait...")
    display.show(Image.HAPPY)
    uart.write("AT_CIPMUX=0\r\n")
    sleep(500)
    uart.write('AT+CIPSTART="TCP","0",0\r\n')
    sleep(TIME)
    if (uart.any()):
      data = str(uart.readall(), 'UTF-8')
      sleep(TIME)
    uart.write('AT+CIFSR\r\n')
    sleep(2000)
    data = 0
    if (uart.any()):
      data = str(uart.readall(), 'UTF-8')
      tmp = data.split('"', 5)
      self.ip_address = tmp[1]
      if (self.ip_addfress[0] == '1' and len(self.ip_address) > 10):
        return True
      else:
        display.show('.')
        sleep(3000)
        return False
  def ifconfig(self):
    return self.ip_address
  def httpSet(self, IP, PORT):
    uart.write('AT+CIPSTART="TCP","%s",%s\r\n' % (IP, PORT))
    sleep(6000)
    uart.write('AT+CIPMODE=1\r\n')
    sleep(500)
    uart.write('AT+CIPSEND\r\n')
    sleep(3000)
    if (uart.any()):
      self.res = str(uart.readall, 'UTF-8')
      self.res = 0
  def get(self, url, time):
    uart.write('GET /%s\r\n\r\n' % url)
    sleep(1000)
    if (uart.any()):
      res = str(uart.readall(), 'UTF-8')
      return (200, res)
    return (404, 'NOT FOUND')

Obloq = Obloq()
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

uart.init(baudrate=9600, bits=8, parity=None, stop=1, tx=pin2, rx=pin1)
ConnectWifi(SSID, PASSWORD)
microbit.compass.calibrate()

while True:
  f = microbit.compass.get_field_strength()
  flag = 1 # 0 Open 1 Close
  if (f > 10 and flag == 0):
    Obloq.post('setwindow', 'name=a1&stat=1')
  elif (f < 10 and flag == 1):
    Obloq.post('setwindow', 'name=a1&stat=0')
  sleep(1000)

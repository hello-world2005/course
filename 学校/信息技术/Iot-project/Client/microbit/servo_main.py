from microbit import *
import Servo
import Obloq

Obloq = Obloq()

sv=Servo(pin0)
while True:
  err, res = Obloq.get('cron/id=a1'))
  if (res == 'C'):
    sv.angle(0)
  else:
    sv.angle(1)
  sleep(1000)
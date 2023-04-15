from microbit import *
import Servo 

sv=Servo(pin0)
while True:
    sv.angle(0)
    sleep(1000)
    sv.angle(90)
    sleep(1000)
    sv.angle(180)
    sleep(1000)
    sv.angle(90)
    sleep(1000)
import RPi.GPIO as GPIO
from time import sleep

GPIO.setmode(GPIO.BOARD)

#Forwards/Backwards - Back motor
Motor1A = 8 #grey
Motor1B = 10 #white
Motor1E = 12 #purple

#Right/Left - Front motor
Motor2A = 7 #green
Motor2B = 5 #yellow
Motor2E = 3 #orange

#setup
GPIO.setup(Motor1A,GPIO.OUT)
GPIO.setup(Motor1B,GPIO.OUT)
GPIO.setup(Motor1E,GPIO.OUT)

#setup
GPIO.setup(Motor2A,GPIO.OUT)
GPIO.setup(Motor2B,GPIO.OUT)
GPIO.setup(Motor2E,GPIO.OUT)


def go(dir):
    if dir == '1': #forwards
        print("Going forwards")
        GPIO.output(Motor1A,GPIO.HIGH)
        GPIO.output(Motor1B,GPIO.LOW)
        GPIO.output(Motor1E,GPIO.HIGH)
    elif dir == '-1': #backwards
        print("Going backwards")
        GPIO.output(Motor1A,GPIO.LOW)
        GPIO.output(Motor1B,GPIO.HIGH)
        GPIO.output(Motor1E,GPIO.HIGH)
    elif dir == '0': #stop
        print("Stop")
        GPIO.output(Motor1E,GPIO.LOW)

def turn(dir):
    if dir == '1': #right
        print("Turn right")
        GPIO.output(Motor2A,GPIO.HIGH)
        GPIO.output(Motor2B,GPIO.LOW)
        GPIO.output(Motor2E,GPIO.HIGH)
    elif dir == '-1': #left
        print("Turn left")
        GPIO.output(Motor2A,GPIO.LOW)
        GPIO.output(Motor2B,GPIO.HIGH)
        GPIO.output(Motor2E,GPIO.HIGH)
    elif dir == '0': #straight
        print("Go straight")
        GPIO.output(Motor1E,GPIO.LOW)

GPIO.cleanup()

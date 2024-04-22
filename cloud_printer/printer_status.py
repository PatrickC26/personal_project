import RPi.GPIO as GPIO
import time
import os
import firebase

# set pins
R_PIN = 20
G_PIN = 16
B_PIN = 26
GND_PIN = 19 

# set GPIO mode
GPIO.setmode(GPIO.BCM)

# set GPIO IOs
GPIO.setup(R_PIN, GPIO.OUT)
GPIO.setup(GND_PIN, GPIO.OUT)
GPIO.setup(G_PIN, GPIO.OUT)
GPIO.setup(B_PIN, GPIO.IN, pull_up_down = GPIO.PUD_UP)

# let led turn OFF
GPIO.output(GND_PIN, GPIO.LOW)
GPIO.output(G_PIN, GPIO.LOW)
GPIO.output(R_PIN, GPIO.LOW)


# shut down method
def shutDownCheck():
    bS = GPIO.input(B_PIN)
    if (bS == False) :
        shoutDown()


def shoutDown():
    GPIO.output(R_PIN, GPIO.HIGH)
    GPIO.output(G_PIN, GPIO.LOW)
    nowtime = timeGET()
    firebasePUT("lastCheck",nowtime)
    firebasePUT("renewTime",nowtime)
    firebasePUT("on_off","off")
    firebasePUT("record/" + currentNo, firebaseGET("record/" + currentNo) + "," + nowtime)
    os.system("shutdown now -h")
    #GPIO.cleanup()
    while (True):
        time.sleep(1)

connectionType = 0 # 0 -> No // 1 -> Yes
status_light_status = 0 # 0 -> N // 1 -> Y
status_millis_1000 = time.time()
# status Light
def status_Light():
    global status_millis_1000
    global status_light_status
    #print(status_light_status)
    #print(time.time() - status_millis_1000 >1)
    if (connectionType == 1):
        GPIO.output(G_PIN, GPIO.HIGH)
        GPIO.output(R_PIN, GPIO.LOW)
    else :
        if (((time.time() - status_millis_1000) > 1) & (status_light_status == 0)):
            GPIO.output(R_PIN, GPIO.HIGH)
            GPIO.output(G_PIN, GPIO.HIGH)
            status_millis_1000 = time.time()
            status_light_status = 1
        elif (((time.time() - status_millis_1000) > 1) & (status_light_status == 1)):
            GPIO.output(R_PIN, GPIO.LOW)
            GPIO.output(G_PIN, GPIO.LOW)
            status_millis_1000 = time.time()
            status_light_status = 0

#check wifi
def wifiCheck():
    global connectionType
    try :
        nowtime = timeGET()
        if (":" in nowtime) :
            connectionType = 1
        else :
            connectionType = 0
        firebasePUT("lastCheck",nowtime)
        firebasePUT("renewTime",nowtime)
        if (firebaseGET("control") == "OFF") :
            firebasePUT("control","NA")
            shoutDown()

    except :
        connectionType = 0



currentNo = ""
init_OK = 0
# init
def init() :
    try :
        nowtime = timeGET()
        firebasePUT("lastCheck",nowtime)
        firebasePUT("renewTime",nowtime)
        firebasePUT("on_off","on")
        global currentNo
        currentNo = firebaseGET("record/currentNo")
        firebasePUT("record/currentNo", str((int)(currentNo) + 1))
        firebasePUT("record/" + currentNo,nowtime)
        global init_OK 
        init_OK = 1
    except:
        print("ERROR in init")
        

status_Light()
init()

# loop
time_1000 = 0.0
while True:
    try :
        shutDownCheck()
        status_Light()
        if (time.time() - time_1000 > 2) :
            wifiCheck()
            time_1000 = time.time()
        if (init_OK == 0) :
            init()
    except :
        print("ERROR in loop")
    


GPIO.cleanup()

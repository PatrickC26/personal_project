import paho.mqtt.client as mqtt
import json
import array
from multiprocessing import Process
from time import sleep
from datetime import datetime

amount = 30

# Don't forget to change the variables for the MQTT broker!
mqtt_broker_ip = "192.168.1.100"
location = "/home/pi/Desktop/project/"
# location = "/Users/slothsmba/Desktop/"


def on_connect(client, userdata, flags, rc):
    print("Connected!", str(rc))  # rc is the error code
    client.subscribe("#")  # Subscribe everything


def on_message(client, userdata, msg): 
    inS = str(msg.payload)  # Get everything in
    #print("Data receive")
    #print(datetime.now().time())
    print("Topic: ", msg.topic + "\tMessage: " + inS)  # Print out every message come in
    if "%" in inS:
        #client.subscribe("1")
        #client.publish(msg.topic, "OK")
        #client.subscribe("#")
        # Data Process
        dataprocess(inS)


client = mqtt.Client()
# Telling the client which functions are to be run
# on connecting, and on receiving a message
client.on_connect = on_connect
client.on_message = on_message

# 1883 is the listener port that the MQTT broker is using
client.connect(mqtt_broker_ip, 1883)


def readLog():
    with open(location + "data.json") as inputfile:
        data = json.load(inputfile)
        a = [" " for i in range(amount)]
        for i in range(0,amount):
            a[i] = data[str(chr(ord('A')+i))]
        return a

def renewLog(cC, cS):
    try:
        a = readLog()
        a[(ord(cC[0])-ord('A'))] = cS
        print(a)
        data = {'A': str(a[0]), 'B': str(a[1]), 'C': str(a[2]), 'D': str(a[3]), 'E': str(a[4]), 'F': str(a[5]),
                'G': str(a[6]), 'H': str(a[7]), 'I': str(a[8]), 'J': str(a[9]), 'K': str(a[10]), 'L': str(a[11]),
                'M': str(a[12]), 'N': str(a[13]), 'O': str(a[14]), 'P': str(a[15]), 'Q': str(a[16]), 'R': str(a[17]),
                'S': str(a[18]), 'T': str(a[19]), 'U': str(a[20]), 'V': str(a[21]), 'W': str(a[22]), 'X': str(a[23]),
                'Y': str(a[24]), 'Z': str(a[25]), '[':str(a[26]), '\\':str(a[27]), ']':str(a[28]), '^':str(a[29]) }
        with open(location + 'data.json', 'w') as outfile:
            json.dump(data, outfile)
            #print(data)
            data.clear()
    except Exception as e :
        print("EROOR in renewLog")
        print(e)
    
def dataprocess(inS):
    #print("Start data process")
    #print(datetime.now().time())
    inS = inS[2:-1]
    print(inS);
    head = inS[0]
    if (not head.isascii()):
        while not head.isascii():
            inS = inS[1:]
            head = ord(inS[0])
    else :
        if inS[-1] == '%':
            temp_a = (inS[1:-1])
        else :
            while not inS[-1] == '%':
                inS = inS[0:-1]
                temp_a = (inS[1:-1])
    print("  Value of: " + head + "  Value is: " + (temp_a))
    renewLog(head,(temp_a))
    #print("Finish data process")
    #print(datetime.now().time())
    

processlist = []
def work1():
    try :
        # Once we have told the client to connect, let the client object run itself
        client.loop_forever()
        client.disconnect()
    except :
        print("error in work 1 \n Reconnecting")
        sleep(1)
        work1()

def work2():
    while True:
        try :
            alpha = ['A']
            charA = readLog()
            # print(charA)
            if charA[26] == "1":
                #client.publish("b",'Z')
                for i in alpha:
                    outS = i + charA[ord(i)-ord('A')] + "%"
                    print("Sending data")
                    print(datetime.now().time())
                    print(outS)
                    client.subscribe("1")
                    client.publish("m",outS)
                    client.subscribe("#")
                    
                renewLog('[',"0")
                sleep(0.5)
        except :
            print("Error in work 2")
    
if __name__ == '__main__':

    processlist.append(Process(target=work1))
    processlist.append(Process(target=work2))

    for t in processlist:
        t.start()

    for t in processlist:
        t.join()



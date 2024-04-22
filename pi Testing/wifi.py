import paho.mqtt.client as mqtt
import json
import array
from multiprocessing import Process
from time import sleep
import time


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
    
def dataprocess(inS):
    global temp_a
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
    time_millis = 0;
    while True:
        try :
            
            charA = readLog()
            if charA[26] == "1":
                client.subscribe("abc")
                client.publish("m",'A' + charA[ord('A')-ord('A')] + "%")
                client.publish("k",'P' + charA[ord('P')-ord('A')] + "%")
                client.publish("d",'T' + charA[ord('T')-ord('A')] + "%")
                client.subscribe("#")
                sleep(0.2)
                renewLog('[',"0")
                
            elif(time.time() - time_millis > 5) :
                time_millis = int(time.time())
                print(time_millis)
                alpha = ['m','k','d', 'f']
                for i in alpha :
                    client.subscribe("abc")
                    client.publish(i,'Z')
                    sleep(0.2)
                    client.subscribe("#")
                
                client.publish("o",'X' + charA[ord('X')-ord('A')] + "%")
                time.sleep(0.1)
                client.publish("o",'L' + charA[ord('L')-ord('A')] + "%")
                time.sleep(0.1)
                client.publish("o",'U' + charA[ord('U')-ord('A')] + "%")
                time.sleep(0.1)
                client.publish("o",'N' + charA[ord('N')-ord('A')] + "%")
                time.sleep(0.1)
                client.publish("o",'M' + charA[ord('M')-ord('A')] + "%")
                
            else :
                sleep(0.5)
        except Exception as e:
            print("Error in work 2")
            print(e)
    
if __name__ == '__main__':

    processlist.append(Process(target=work1))
    processlist.append(Process(target=work2))

    for t in processlist:
        t.start()

    for t in processlist:
        t.join()

 
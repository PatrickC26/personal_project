import paho.mqtt.client as mqtt
import dataprocess
import time



# Don't forget to change the variables for the MQTT broker!
mqtt_broker_ip = "192.168.1.100"
# location = "/Users/slothsmba/Desktop/"


def on_connect(client, userdata, flags, rc):
    print("Connected!", str(rc))  # rc is the error code
    client.subscribe("#")  # Subscribe everything


def on_message(client, userdata, msg): 
    inS = str(msg.payload)  # Get everything in
    print("Topic: ", msg.topic + "\tMessage: " + inS)  # Print out every message come in
    if "%" in inS:
        dataprocess(inS)


client = mqtt.Client()


def init():
    client.on_connect = on_connect
    client.on_message = on_message

    client.connect(mqtt_broker_ip, 1883)

init()

def sendRequest():
    charA = dataprocess.readLog()
    if charA[26] == "1":
        client.subscribe("abc")
        client.publish("m", 'A' + charA[ord('A') - ord('A')] + "%")
        client.publish("k", 'P' + charA[ord('P') - ord('A')] + "%")
        client.publish("d", 'T' + charA[ord('T') - ord('A')] + "%")
        client.subscribe("#")
        time.sleep(0.2)
        dataprocess.renewLog('[', "0")

def sendData() :
    charA = dataprocess.readLog()
    alpha = ['m', 'k', 'd', 'f']
    for i in alpha:
        client.subscribe("abc")
        client.publish(i, 'Z')
        time.sleep(0.2)
        client.subscribe("#")

    client.publish("o", 'X' + charA[ord('X') - ord('A')] + "%")
    time.sleep(0.1)
    client.publish("o", 'L' + charA[ord('L') - ord('A')] + "%")
    time.sleep(0.1)
    client.publish("o", 'U' + charA[ord('U') - ord('A')] + "%")
    time.sleep(0.1)
    client.publish("o", 'N' + charA[ord('N') - ord('A')] + "%")
    time.sleep(0.1)
    client.publish("o", 'M' + charA[ord('M') - ord('A')] + "%")


# Once we have told the client to connect, let the client object run itself
client.loop_forever()
client.disconnect()

 
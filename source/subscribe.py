import paho.mqtt.client as paho
from paho import mqtt
import time
import random

broker = "localhost"
port = 1883
topic = "my/topic"
client_id = f'python-mqtt-{random.randint(0, 1000)}'

def on_connect(client, userdata, flags, rc, properties=None):
    print("CONNACK received with code %s." % rc)
    client.subscribe(topic, qos=1)

def on_message(client, userdata, msg):
    print(f"Received `{msg.payload.decode()}` from `{msg.topic}` topic")

client = paho.Client(client_id=client_id, userdata=None, protocol=paho.MQTTv5)
client.on_connect = on_connect
client.on_message = on_message
client.connect(broker, port)
client.loop_forever()

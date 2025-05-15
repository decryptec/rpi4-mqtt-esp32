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

def on_publish(client, userdata, mid, properties=None):
    print("Published: MID " + str(mid))

client = paho.Client(client_id=client_id, userdata=None, protocol=paho.MQTTv5)
client.on_connect = on_connect
client.on_publish = on_publish
client.connect(broker, port)
client.loop_start()

try:
    while True:
        message = f"Hello MQTT! - {time.strftime('%Y-%m-%d %H:%M:%S')}"
        result = client.publish(topic, message, qos=1)
        status = result[0]
        if status == paho.MQTT_ERR_SUCCESS:
            print(f"Sent `{message}` to topic `{topic}`")
        else:
            print(f"Failed to send message to topic {topic}")
        time.sleep(5)
except KeyboardInterrupt:
    print("Disconnecting...")
finally:
    client.disconnect()
    client.loop_stop()
    print("Disconnected.")

from flask import Flask, jsonify, request, render_template, url_for
import paho.mqtt.client as paho
from paho import mqtt
import random

#MQTT broker
broker = "localhost"
port = 1883
client_id = f'Raspi 4 MQTT Broker - {random.randint(0,1000)}'

# Topics
status_t = "fan/status"
output_t = "fan/output"
temp_t = "sensors/temp"

# Web UI
app = Flask(__name__, static_folder="static", template_folder="templates")

# Sensor data
fan_status = "ON"
current_fan_output = 1200
set_fan_output = 1500
current_temp = 35.5

def on_connect(client, userdata, flags, rc, properties=None):
    print("CONNACK received with code %s." % rc)
    client.subscribe(temp_t, qos=1)

def on_publish(client, userdata, mid, properties=None):
    print("Published: MID " + str(mid))
    
def on_message(client, userdata, msg):
    global current_temp
    try:
        if not msg.payload:
            print(f"Warning: Received empty message on topic {msg.temp_t}")
            return
        
        current_temp = int(msg.payload.decode())
        print(f"Received `{msg.payload.decode()}` from `{msg.temp_t}` topic")
    except Exception as err:
        print(f"Error processessing temp_t message: {err}")
    
client = paho.Client(client_id=client_id, userdata=None, protocol=paho.MQTTv5)
client.on_connect = on_connect
client.on_publish = on_publish
client.on_message = on_message
client.connect(broker, port)
client.loop_start()

# Web UI
@app.route("/")
def home():
    return render_template("dashboard.html")

@app.route("/data")
def get_data():
    # Debug: Print data before returning JSON
    print(f"Sending Data: Fan Status: {fan_status}, Current Fan Output: {current_fan_output}, Set Fan Output: {set_fan_output}, Temp: {current_temp}")
    
    return jsonify({
        "fan_status": str(fan_status),  
        "current_fan_output": int(current_fan_output) if isinstance(current_fan_output, (int, float)) else 0,
        "set_fan_output": int(set_fan_output) if isinstance(set_fan_output, (int, float)) else 0,
        "current_temp": float(current_temp)  
    })

@app.route("/fan_toggle", methods=["POST"])
def toggle_fan():
    global fan_status
    try:
        fan_status = "OFF" if fan_status == "ON" else "ON"
        print(f"Fan toggled! Current status: {fan_status}")
        
        result = client.publish(status_t, fan_status, qos=1)
        if result[0] == paho.MQTT_ERR_SUCCESS:
            print(f"Sent `{fan_status}` to topic `{status_t}`")
        else:
            print(f"Failed to send toggle msg to topic {status_t}")
        
        return jsonify({"message": "Fan status updated!", "fan_status": fan_status})
    except Exception as err:
        print(f"Error: {err}")
        return jsonify({"message": "Error toggling fan"}), 500

@app.route("/set_fan_output", methods=["POST"])
def set_fan_output():
    global set_fan_output
    data = request.json  

    if "rpm" in data and isinstance(data["rpm"], int):
        set_fan_output = max(0, min(data["rpm"], 100))  

        result = client.publish(output_t, set_fan_output, qos=1)
        if result[0] == paho.MQTT_ERR_SUCCESS:
            print(f"Sent `{set_fan_output}` to topic `{output_t}`")
        else:
            print(f"Failed to send fan output msg to topic {output_t}")
        
        print(f"Fan Output Updated: {set_fan_output}")
        
        return jsonify({"message": "Fan output updated!", "set_fan_output": set_fan_output})
    else:
        return jsonify({"message": "Invalid input"}), 400

if __name__ == "__main__":
    try:
        
        app.run(debug=True)
    except KeyboardInterrupt:
        print("Disconnecting")
    finally:
        client.disconnect()
        client.loop_stop()
        print("Disconnected.")
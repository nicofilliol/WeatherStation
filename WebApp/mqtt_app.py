from header import *
import json
from datetime import datetime
import paho.mqtt.client as mqtt

# Define event callbacks
def on_connect(client, userdata, flags, rc):
    print("rc: " + str(rc))

def on_publish(client, obj, mid):
    print("mid: " + str(mid))

def on_subscribe(client, obj, mid, granted_qos):
    print("Subscribed: " + str(mid) + " " + str(granted_qos))

def on_log(client, obj, level, string):
    print(string)

def on_message(client, obj, msg):
    global new_data_flag

    print(msg.topic + " " + str(msg.qos) + " " + str(msg.payload))

    data = dict(
        topic=msg.topic,
        payload=msg.payload.decode()
    )
    payload = json.loads(data["payload"])

    # Add data to queue

    now = datetime.now()
    timestamp = now.strftime("%H:%M:%S")

    temperature_queue.append((timestamp, payload["temperature"]))
    humidity_queue.append((timestamp, payload["humidity"]))
    water_queue.append((timestamp, payload["water"]))
    light_queue.append((timestamp, payload["light"]))
    pressure_queue.append((timestamp, payload["pressure"]))

    new_data_flag.set_state(True)

def init_mqtt():
    mqttc = mqtt.Client()
    # Assign event callbacks
    mqttc.on_message = on_message
    mqttc.on_connect = on_connect
    mqttc.on_publish = on_publish
    mqttc.on_subscribe = on_subscribe

    # Uncomment to enable debug messages
    #mqttc.on_log = on_log

    # Setup MQTT Client
    mqtt_details = {
        "hostname" : "broker.hivemq.com",
        "port" : 1883,
        "username" : "",
        "password" : "",
        "subscribe_topic" : "ethz/weather_station",
        "publish_topic" : "ethz/weather_station/publish"
    }

    # Connect
    mqttc.username_pw_set(mqtt_details["username"], mqtt_details["password"])
    mqttc.connect(mqtt_details["hostname"], int(mqtt_details["port"]))

    # Start subscribe, with QoS level 0
    mqttc.subscribe(mqtt_details["subscribe_topic"], 0)

    # Publish a message
    mqttc.publish(mqtt_details["publish_topic"], "my message")

    # Continue the network loop, exit when an error occurs
    mqttc.loop_start()
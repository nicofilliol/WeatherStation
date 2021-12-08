from header import *
from flask_mqtt import MQTT_LOG_ERR
import json
from datetime import datetime
import requests

@mqtt.on_connect()
def handle_connect(client, userdata, flags, rc):
    print(f"Subscribed to topic {SUBSCRIPTION_TOPIC}")
    mqtt.subscribe(SUBSCRIPTION_TOPIC)


@mqtt.on_message()
def handle_mqtt_message(client, userdata, message):
    global new_data_flag

    data = dict(
        topic=message.topic,
        payload=message.payload.decode()
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

@mqtt.on_log()
def handle_logging(client, userdata, level, buf):
    if level == MQTT_LOG_ERR:
        print('Error: {}'.format(buf))
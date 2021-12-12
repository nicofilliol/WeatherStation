from flask import Flask, render_template
from flask_mqtt import Mqtt
from collections import deque
import configparser
import os
import urllib   

# Helper class for flag
class Ready_Flag():
    def __init__(self, initial_state=False):
        self.state = initial_state

    def ready(self):
        return self.state

    def toggle_state(self):
        self.state = not self.state
    
    def set_state(self, state):
        self.state = state

# Global variables
humidity_queue = deque(maxlen=500)
temperature_queue = deque(maxlen=500)
water_queue = deque(maxlen=500)
light_queue = deque(maxlen=500)
pressure_queue = deque(maxlen=500)
new_data_flag = Ready_Flag(False)

# Setup Flask and MQTT Client
if os.path.isfile("WebApp/mqtt.config"):
    config = configparser.ConfigParser()
    config.read('WebApp/mqtt.config')
    mqtt_details = dict(config.items('MQTT'))
else: # File does not exist, check environment variables
    url_str = os.environ.get('CLOUDMQTT_URL')
    url = urllib.parse.urlparse(url_str)


    mqtt_details = {
        "ip_address" : url.hostname,
        "port" : url.port,
        "username" : url.username,
        "password" : url.password,
        "subscribe_topic" : os.environ.get('SUB_TOPIC'),
        "publish_topic" : os.environ.get('PUB_TOPIC')
    }

app = Flask(__name__)
app.config['DEBUG'] = True
app.config['MQTT_BROKER_URL'] = mqtt_details['ip_address']
app.config['MQTT_BROKER_PORT'] = int(mqtt_details['port'])  # default port for non-tls connection
app.config['MQTT_USERNAME'] = mqtt_details['username']  # set the username here if you need authentication for the broker
app.config['MQTT_PASSWORD'] = mqtt_details['password']   # set the password here if the broker demands authentication
app.config['MQTT_KEEPALIVE'] = 5  # set the time interval for sending a ping to the broker to 5 seconds
app.config['MQTT_TLS_ENABLED'] = False  # set TLS to disabled for testing purposes

# Defines
SUBSCRIPTION_TOPIC = mqtt_details['subscribe_topic']
PUBLISH_TOPIC = mqtt_details['publish_topic']

mqtt = Mqtt()
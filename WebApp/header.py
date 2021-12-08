from flask import Flask, render_template
from flask_mqtt import Mqtt
from collections import deque

# Defines
SUBSCRIPTION_TOPIC = "ethz/weather_station"

# Global variables
humidity_queue = deque(maxlen=500)
temperature_queue = deque(maxlen=500)
water_queue = deque(maxlen=500)
light_queue = deque(maxlen=500)
pressure_queue = deque(maxlen=500)
new_data_flag = False

app = Flask(__name__)
app.config["DEBUG"] = True
app.config['MQTT_BROKER_URL'] = 'broker.hivemq.com' 
app.config['MQTT_BROKER_PORT'] = 1883  # default port for non-tls connection
app.config['MQTT_USERNAME'] = ''  # set the username here if you need authentication for the broker
app.config['MQTT_PASSWORD'] = ''  # set the password here if the broker demands authentication
app.config['MQTT_KEEPALIVE'] = 5  # set the time interval for sending a ping to the broker to 5 seconds
app.config['MQTT_TLS_ENABLED'] = False  # set TLS to disabled for testing purposes

mqtt = Mqtt()
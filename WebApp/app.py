from flask import render_template, request, Response
from header import *
from mqtt_app import *
import json
import time
import pytz

def get_message():
    """Block until new data is available"""
    global new_data_flag

    while not new_data_flag.ready():
        time.sleep(0.1)

    # Fetch data entries from last 24h
    timezone = pytz.timezone("Europe/Zurich")
    time_24_hours_ago = datetime.now(timezone) - timedelta(days=1)
    db_data = WeatherEntry.query.filter(WeatherEntry.timestamp >= time_24_hours_ago).order_by(WeatherEntry.timestamp).all()

    timestamps = []
    temperature = []
    humidity = []
    pressure = []
    light = []
    water = []

    for entry in db_data:
        timestamps.append(entry.timestamp.strftime("%H:%M:%S"))
        temperature.append(entry.temperature)
        humidity.append(entry.humidity)
        pressure.append(entry.pressure)
        light.append(entry.light)
        if entry.water:
            water.append("Rain")
        else:
            water.append("No Rain")

    # New data avalaible
    data = {
            "temperature": {
                "time" : timestamps,
                "data" : temperature
            } ,
            "humidity": {
                "time" : timestamps,
                "data" : humidity
            } ,
            "water": {
                "time" : timestamps,
                "data" : water
            } ,
            "light": {
                "time" : timestamps,
                "data" : light
            }, 
            "pressure": {
                "time" : timestamps,
                "data" : pressure
            }
        }
    
    json_data = json.dumps(data)
    new_data_flag.set_state(False)
    return json_data


@app.route("/", methods=["GET", "POST"])
def home():
    new_data_flag.set_state(True) # force to load data
    return render_template("index.html")

@app.route("/stream")
def stream():
    def eventStream():
        while True:
            # wait for source data to be available, then push it
            yield f"data: {get_message()}\n\n"
    return Response(eventStream(), mimetype="text/event-stream")


init_mqtt()
print("Initialized MQTT...")

if __name__ == '__main__':
    app.run(debug=True)
from flask import render_template, request, Response
from header import *
import mqtt_app
import json
import time

def get_message():
    """Block until new data is available"""
    global new_data_flag

    while not new_data_flag:
        time.sleep(0.1)

    # New data avalaible
    data = {
            "temperature": {
                "time" : [sample[0] for sample in temperature_queue],
                "data" : [sample[1] for sample in temperature_queue]
            } ,
            "humidity": {
                "time" : [sample[0] for sample in humidity_queue],
                "data" : [sample[1] for sample in humidity_queue]
            } ,
            "water": {
                "time" : [sample[0] for sample in water_queue],
                "data" : [sample[1] for sample in water_queue]
            } ,
            "light": {
                "time" : [sample[0] for sample in light_queue],
                "data" : [sample[1] for sample in light_queue]
            }, 
            "pressure": {
                "time" : [sample[0] for sample in pressure_queue],
                "data" : [sample[1] for sample in pressure_queue]
            }
        }
    
    json_data = json.dumps(data)
    new_data_flag = False
    return json_data


@app.route("/", methods=["GET", "POST"])
def home():
    data_temperature = list(temperature_queue)
    data_humidity = list(humidity_queue)
    data_pressure = list(pressure_queue)

    labels_t = [row[0] for row in data_temperature]
    temperature = [row[1] for row in data_temperature]
    humidity = [row[1] for row in data_humidity]

    labels_p = [row[0] for row in data_pressure]
    pressure = [row[1] for row in data_pressure]

    return render_template("graph.html", labels_t=labels_t, temperature=temperature, humidity=humidity, labels_p=labels_p, pressure=pressure)

@app.route("/demo")
def demoGraph():
    data_pressure = [
        ("11:00",12),
        ("12:00",12.2),
        ("13:00",14),
        ("14:00",14),
        ("15:00",13.6),
        ("16:00",13.1),
        ("17:00",12.9),
        ("18:00",14.8),
        ("19:00",14.2)
    ]

    labels = [row[0] for row in data_pressure]
    pressure = [row[1] for row in data_pressure]
    
    return render_template("index.html", labels=labels, pressure=pressure)


@app.route("/stream")
def stream():
    def eventStream():
        while True:
            # wait for source data to be available, then push it
            yield get_message()
    return Response(eventStream(), mimetype="text/event-stream")

if __name__ == '__main__':
    mqtt.init_app(app)
    print("Initialized MQTT...")
    app.run(debug=True)
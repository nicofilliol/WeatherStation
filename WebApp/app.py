from flask import render_template, request, Response
from header import *
from mqtt_app import *
import json
import time

init_mqtt()
print("Initialized MQTT...")

def get_message():
    """Block until new data is available"""
    global new_data_flag

    while not new_data_flag.ready():
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
    new_data_flag.set_state(False)
    return json_data


@app.route("/", methods=["GET", "POST"])
def home():
    data_temperature = list(temperature_queue)
    data_humidity = list(humidity_queue)
    data_pressure = list(pressure_queue)
    data_light = list(light_queue)
    data_water = list(water_queue)

    labels_t = [row[0] for row in data_temperature]
    temperature = [row[1] for row in data_temperature]
    humidity = [row[1] for row in data_humidity]

    labels_p = [row[0] for row in data_pressure]
    pressure = [row[1] for row in data_pressure]

    labels_l = [row[0] for row in data_light]
    light = [row[1] for row in data_light]

    labels_w = [row[0] for row in data_water]
    water = [row[1] for row in data_water]

    if len(temperature)>0:
        t_now = temperature[-1]
    else:
        t_now = ""
    if len(pressure)>0:
        p_now = pressure[-1]
    else:
        p_now = ""

    return render_template("graph.html", temperature_now=t_now, pressure_now=p_now, labels_t=labels_t, temperature=temperature, humidity=humidity, labels_p=labels_p, pressure=pressure, labels_l=labels_l, light=light, labels_w=labels_w, water=water)

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
            yield f"data: {get_message()}\n\n"
    return Response(eventStream(), mimetype="text/event-stream")

if __name__ == '__main__':
    app.run(debug=True)
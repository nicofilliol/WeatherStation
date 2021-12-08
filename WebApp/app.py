from flask import render_template, request
from header import *
import mqtt_app

@app.route("/")
def home():
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

@app.route("/line", methods=["GET", "POST"])
def line():
    data_temperature = list(temperature_queue)
    data_humidity = list(humidity_queue)
    data_pressure = list(pressure_queue)

    labels_t = [row[0] for row in data_temperature]
    temperature = [row[1] for row in data_temperature]
    humidity = [row[1] for row in data_humidity]

    labels_p = [row[0] for row in data_pressure]
    pressure = [row[1] for row in data_pressure]

    return render_template("graph.html", labels_t=labels_t, temperature=temperature, humidity=humidity, labels_p=labels_p, pressure=pressure)

if __name__ == '__main__':
    mqtt.init_app(app)
    print("Initialized MQTT...")
    app.run(host="localhost", port=8000, debug=True)
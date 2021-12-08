from flask import render_template
from header import app, mqtt, SUBSCRIPTION_TOPIC
import mqtt_app




@app.route("/")
def home():
    data = [
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
    labels = [row[0] for row in data]
    values = [row[1] for row in data]

    return render_template("index.html", labels=labels, values=values)

@app.route("/line")
def line():
    data = [
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
    labels = [row[0] for row in data]
    values = [row[1] for row in data]

    return render_template("graph.html", labels=labels, values=values)


if __name__ == '__main__':
    mqtt.init_app(app)
    print("Initialized MQTT...")
    app.run(host="localhost", port=8000, debug=True)
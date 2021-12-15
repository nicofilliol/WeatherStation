from flask import Flask, render_template
from flask_migrate import Migrate
from flask_sqlalchemy import SQLAlchemy
from collections import deque

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

app = Flask(__name__)
app.config['SQLALCHEMY_DATABASE_URI'] = "postgresql://pqnahgsbofqgcs:80af876909e1925704bf3fa789efc843e1df8fba918da328638603d1ef84b6f9@ec2-34-193-235-32.compute-1.amazonaws.com:5432/d2ber8r7uje736" #os.environ.get("DATABASE_URL")
app.config['SQLALCHEMY_TRACK_MODIFICATIONS'] = False
app.config['SECRET_KEY'] = "123udsajfkajrow2iui2ou4o2joewfje"

db = SQLAlchemy(app) ## Create DB object
migrate = Migrate(app,db) ## Create migration object

from models import WeatherEntry
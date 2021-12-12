from flask import Flask, render_template
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

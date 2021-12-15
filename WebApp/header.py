from flask import Flask, render_template
from flask_migrate import Migrate
from flask_sqlalchemy import SQLAlchemy
import os

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
new_data_flag = Ready_Flag(True)

app = Flask(__name__)
database_url = "***REMOVED***"#os.environ.get("DATABASE_URL")
database_url= database_url.replace("postgres", "postgresql", 1)
app.config['SQLALCHEMY_DATABASE_URI'] = database_url
app.config['SQLALCHEMY_TRACK_MODIFICATIONS'] = False

db = SQLAlchemy(app) ## Create DB object
migrate = Migrate(app,db) ## Create migration object

from models import WeatherEntry
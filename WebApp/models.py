from header import db

class WeatherEntry(db.Model):
    __tablename__ = "weatherstation"

    id = db.Column(db.Integer, primary_key = True)
    timestamp = db.Column(db.DateTime())
    temperature = db.Column(db.Float())
    humidity = db.Column(db.Float())
    pressure = db.Column(db.Float())
    light = db.Column(db.Float())
    water = db.Column(db.Boolean())
    
    def __repr__(self):
        return f'<ID: {self.id}, Temperature: {self.temperature}, Humidity: {self.humidity}, Pressure: {self.pressure}, Light: {self.light}, Water: {self.water}>'
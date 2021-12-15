const eventSource = new EventSource("/stream");

eventSource.onmessage = function(event) {
    const event_data = JSON.parse(event.data);
    console.log(event_data)
    // Update graphs with new data

    // Temperature & Humidity
    lineChart_temp.data.labels = event_data.temperature.time;
    lineChart_temp.data.datasets[0].data = event_data.temperature.data;
    lineChart_temp.data.datasets[1].data = event_data.humidity.data;
    lineChart_temp.update();

    // Water
    lineChart_water.data.labels = event_data.water.time;
    lineChart_water.data.datasets[0].data = event_data.water.data;
    lineChart_water.update();

    // Light
    lineChart_light.data.labels = event_data.light.time;
    lineChart_light.data.datasets[0].data = event_data.light.data;
    lineChart_light.update();

    // Pressure
    lineChart_pressure.data.labels = event_data.pressure.time;
    lineChart_pressure.data.datasets[0].data = event_data.pressure.data;
    lineChart_pressure.update();


    // Live temperature data
    var time = parseFloat(event_data.pressure.time.slice(-1)[0])
    var temp = parseFloat(event_data.temperature.data.slice(-1)[0])
    // var pressure = parseFloat(event_data.pressure.data.slice(-1)[0])
    var light = parseFloat(event_data.light.data.slice(-1)[0])
    var water = event_data.water.data.slice(-1)[0]
    console.log("parseFloat(Time): " + time)

    // day
    if(8.0 < time < 20.00){
        // no rain
        if(water == "No Rain"){
            if(light > 0.4){
                // bright, day, no rain
                var img = "static/pictures/clear-day.svg"
            }
            else{
                // dark/dull, day, no rain
                var img = "static/pictures/partly-cloudy-day.svg"
            }
        }
        // rain
        else {
            // warm
            if(temp > 0){
                if(light > 0.4){
                    // bright, day, rain, warm
                    var img = "static/pictures/partly-cloudy-day-rain.svg"
                }
                else{
                    // dark/dull, day, rain, warm
                    var img = "static/pictures/rain.svg"
                }
            }
            // cold
            else{
                if(light > 0.4){
                    // bright, day, rain, cold
                    var img = "static/pictures/partly-cloudy-day-snow.svg"
                }
                else{
                    // dark/dull, day, rain, cold
                    var img = "static/pictures/snow.svg"
                }
            }
        }
    }
    // night
    else{
        if(water == 0){
            // no rain, night
            var img = "static/pictures/clear-night.svg"
        }
        // rain
        else{
            if(temp > 0){
                // warm, night, rain
                var img = "static/pictures/partly-cloudy-night-rain.svg"
            }
            else{
                // cold, night, rain
                var img = "static/pictures/partly-cloudy-night-snow.svg"
            }
        }
    }

    // reload weather icon and live temperature
    if(document.getElementById("temp_now_img").src != img){ // prevent jumps in animated image
        document.getElementById("temp_now_img").src = img;
    }
    document.getElementById("temp_now").innerHTML = temp + "°C";
};
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
    const temp = event_data.temperature.data.slice(-1)[0]
    const pressure = event_data.pressure.data.slice(-1)[0]
    const light = event_data.light.data.slice(-1)[0]
    const water = event_data.water.data.slice(-1)[0]

    // no rain
    //TODO: fill if/else to choose img
    if(water == "0"){
        var img = "static/pictures/clear-day.svg"
    }
    // rain
    else{
        var img = "static/pictures/rain.svg"
    }

    // reload image and temperature
    if(document.getElementById("temp_now_img").src != img){ // prevent jumps in animated image
        document.getElementById("temp_now_img").src = img;
    }
    document.getElementById("temp_now").innerHTML = temp + "°C";
};
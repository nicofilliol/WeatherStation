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
};
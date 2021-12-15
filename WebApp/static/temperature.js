var lineChart_temp;

function init_temp(labels, temperature, humidity) {
    const ctx1 = document.getElementById('tempChart').getContext('2d');
    lineChart_temp = new Chart(ctx1, {
        type: "line",
        data: {
            labels: labels,
            datasets: [
                {
                    label: "Temperature",
                    data: temperature,
                    fill: false,
                    borderColor: "rgb(255, 99, 132)",
                    lineTension: 0.1,
                    yAxisID: 'y'
                },
                {
                    label: "Humidity",
                    data: humidity,
                    fill: false,
                    borderColor: "rgb(54, 162, 235)",
                    lineTension: 0.1,
                    yAxisID: 'y1'
                }
            ]
        },
        options: {
            responsive: true,
            plugins: {
                legend: {
                    position: 'bottom',
                },
                title: {
                    display: true,
                    text: 'Temperature & Humidity'
                }
            },
            interaction: {
                mode: 'index',
                intersect: false
            },
            scales: {
            y: {
                type: 'linear',
                display: true,
                position: 'left',
                title: {
                    display: true,
                    text: '°C'
                }
            },
            y1: {
                type: 'linear',
                display: true,
                position: 'right',
                grid: {
                    drawOnChartArea: false
                },
                title: {
                    display: true,
                    text: '%'
                }
            }
        }
        }
    });
}


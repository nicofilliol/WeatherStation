var lineChart_pressure;

function init_pressure(labels, pressure) {
    const ctx2 = document.getElementById('pressureChart').getContext('2d');
    lineChart_pressure = new Chart(ctx2, {
        type: "line",
        data: {
            labels: labels,
            datasets: [
                {
                    label: "Pressure",
                    data: pressure,
                    fill: false,
                    borderColor: "rgb(255, 99, 132)",
                    lineTension: 0.1,
                    yAxisID: 'y'
                }
            ]
        },
        options: {
            responsive: true,
            plugins: {
                legend: {
                    display: false,
                    position: 'bottom'
                },
                title: {
                    display: true,
                    text: 'Pressure'
                }
            },
            scales: {
                y: {
                    type: 'linear',
                    display: true,
                    position: 'left',
                    title: {
                        display: true,
                        text: 'hPa'
                    }
                },
            }
        }
    });
}

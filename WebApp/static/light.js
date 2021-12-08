var lineChart_light;

function init_light(labels, light) {
    const ctx2 = document.getElementById('lightChart').getContext('2d');
    lineChart_light = new Chart(ctx2, {
        type: "line",
        data: {
            labels: labels,
            datasets: [
                {
                    label: "Light",
                    data: light,
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
                    text: 'Light'
                }
            },
            scales: {
                y: {
                    type: 'linear',
                    display: true,
                    position: 'left',
                    title: {
                        display: true,
                        text: '??'
                    }
                },
            }
        }
    });
}

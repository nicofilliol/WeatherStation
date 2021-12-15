var lineChart_water;

function init_water(labels, water) {
    const ctx2 = document.getElementById('waterChart').getContext('2d');
    lineChart_water = new Chart(ctx2, {
        type: "line",
        data: {
            labels: labels,
            datasets: [
                {
                    label: "Water",
                    data: water,
                    fill: false,
                    borderColor: "rgb(54, 162, 235)",
                    lineTension: 0.1,
                    yAxisID: 'y',
                    stepped: true
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
                    text: 'Water'
                }
            },
            scales: {
                y: {
                    type: 'linear',
                    labels: ['Rain', 'Dry'],
                    display: true,
                    position: 'left',
                    title: {
                        display: false,
                        text: 'raining?'
                    }
                },
            }
        }
    });
}

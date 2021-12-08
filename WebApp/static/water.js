function init_temp(labels, water) {
    const ctx2 = document.getElementById('waterChart').getContext('2d');
    const lineChart = new Chart(ctx2, {
        type: "line",
        data: {
            labels: labels,
            datasets: [
                {
                    label: "Water",
                    data: water,
                    fill: false,
                    borderColor: "rgb(255, 99, 132)",
                    lineTension: 0.1,
                    yAxisID: 'y'
                }
            ]
        },
        options: {
            responsive: false,
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
                    display: true,
                    position: 'left',
                    title: {
                        display: true,
                        text: 'raining?'
                    }
                },
            }
        }
    });
}

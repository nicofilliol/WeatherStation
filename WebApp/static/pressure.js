function init_temp(labels, pressure) {
    const ctx2 = document.getElementById('pressureChart').getContext('2d');
    const lineChart = new Chart(ctx2, {
        type: "line",
        data: {
            labels: labels,
            datasets: [
                {
                    label: "Pressure",
                    data: pressure,
                    fill: false,
                    borderColor: "rgb(255, 99, 132)",
                    lineTension: 0.1
                }
            ]
        },
        options: {
            responsive: false,
            plugins: {
                legend: {
                    position: 'right'
                },
                title: {
                    display: true,
                    text: 'Pressure'
                }
            }
        }
    });
}

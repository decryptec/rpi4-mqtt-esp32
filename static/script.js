function updateData() {
    fetch('/data')
        .then(response => response.json())
        .then(data => {
            document.getElementById("fan_status").innerText = data.fan_status;
            document.getElementById("current_fan_output").innerText = data.current_fan_output;
            document.getElementById("set_fan_output").innerText = data.set_fan_output;
            document.getElementById("current_temp").innerText = data.current_temp;
        });
}

function setFanOutput() {
    let inputField = document.getElementById("fan_output_input");
    let newOutput = parseInt(inputField.value);

    if (newOutput < 0) {
        newOutput = 0;
        showWarning("Value too low! Setting to 0.");
    } else if (newOutput > 100) {
        newOutput = 100;
        showWarning("Value too high! Setting to 100.");
    }

    fetch('/set_fan_output', {
        method: "POST",
        headers: {"Content-Type": "application/json"},
        body: JSON.stringify({"rpm": newOutput})
    }).then(response => response.json())
      .then(data => document.getElementById("set_fan_output").innerText = data.set_fan_output);
}

function showWarning(message) {
    let warning = document.getElementById("warning_message");
    warning.innerText = message;
    warning.style.display = "block";
    setTimeout(() => { warning.style.display = "none"; }, 3000);
}

setInterval(updateData, 2000); // Auto-update every 2 seconds

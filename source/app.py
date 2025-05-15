from flask import Flask, jsonify, request, render_template, url_for

app = Flask(__name__, static_folder="static", template_folder="templates")

# Simulated sensor data
fan_status = "ON"
current_fan_output = 1200
set_fan_output = 1500
current_temp = 35.5

@app.route("/")
def home():
    return render_template("dashboard.html")

@app.route("/data")
def get_data():
    # Debug: Print data before returning JSON
    print(f"Sending Data: Fan Status: {fan_status}, Current Fan Output: {current_fan_output}, Set Fan Output: {set_fan_output}, Temp: {current_temp}")
    
    return jsonify({
        "fan_status": str(fan_status),  
        "current_fan_output": int(current_fan_output) if isinstance(current_fan_output, (int, float)) else 0,
        "set_fan_output": int(set_fan_output) if isinstance(set_fan_output, (int, float)) else 0,
        "current_temp": float(current_temp)  
    })

@app.route("/fan_toggle", methods=["POST"])
def toggle_fan():
    global fan_status
    try:
        fan_status = "OFF" if fan_status == "ON" else "ON"
        print(f"Fan toggled! Current status: {fan_status}")
        return jsonify({"message": "Fan status updated!", "fan_status": fan_status})
    except Exception as err:
        print(f"Error: {err}")
        return jsonify({"message": "Error toggling fan"}), 500

@app.route("/set_fan_output", methods=["POST"])
def set_fan_output():
    global set_fan_output
    data = request.json  

    if "rpm" in data and isinstance(data["rpm"], int):
        set_fan_output = max(0, min(data["rpm"], 100))  

        print(f"Fan Output Updated: {set_fan_output}")
        
        return jsonify({"message": "Fan output updated!", "set_fan_output": set_fan_output})
    else:
        return jsonify({"message": "Invalid input"}), 400

if __name__ == "__main__":
    app.run(debug=True)

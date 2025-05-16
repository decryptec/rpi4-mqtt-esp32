# MQTT Fan Control with ESP32 (ESP-IDF), Flask, and Custom Yocto Pi Build

This project demonstrates controlling a fan with an ESP32 using the ESP-IDF framework, a Flask web interface for control, all running on a Raspberry Pi built with a custom Yocto image.

## Overview

*   **Raspberry Pi (Yocto):** Hosts the Mosquitto MQTT broker, the Flask web interface, and the Python MQTT client, all running on a custom-built Yocto Linux distribution.
*   **MQTT Broker:** Mosquitto handles communication.
*   **ESP32 (ESP-IDF):** Controls the fan, subscribes to commands, and publishes status. Uses the ESP-IDF framework.
*   **Flask:** Web interface for controlling the fan.

## Components

*   `broker/`: Mosquitto configuration (optional).  Includes details for optimized Yocto setup.
*   `flask_interface/`: Flask web app.
*   `esp32_fan_client/`: ESP32 code using the ESP-IDF.  Will contain `CMakeLists.txt`, `sdkconfig`, and source files.
*   `python_mqtt_client/`: Python Paho MQTT client code.
*   `yocto/`: Contains Yocto build configuration files (e.g., `conf/`, custom layers, recipes).  This is a pointer to how the Yocto build was created.

## Prerequisites

*   Raspberry Pi (or similar)
*   ESP32 development board
*   Fan hardware
*   Yocto build environment (Poky) properly set up.
*   ESP-IDF environment properly set up (including toolchain)
*   Python 3 + Flask, Paho MQTT

## Run program
'flask --app app run --debug --host=0.0.0.0'

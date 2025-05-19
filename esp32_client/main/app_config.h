#ifndef APP_CONFIG_H
#define APP_CONFIG_H

#include "driver/gpio.h"

// WiFi Configuration
#define WIFI_MAX_RETRY 10

// MQTT Configuration
#define MQTT_BROKER_URI	"mqtt://<IP_ADDR>:<PORT>" // Replace this. With broker IP and Mosquitto port
#define MQTT_CLIENT_ID	"esp32-test-client"

// Subscribe topics
#define status_t	"fan/status"
#define output_t	"fan/output"

// Publish topics
#define read_t	"fan/read"
#define temp_t	"sensors/dht11/temp"
#define humidity_t	"sensors/dht11/humidity"

// GPIO
#define dht_pin GPIO_NUM_4

#endif // APP_CONFIG_H

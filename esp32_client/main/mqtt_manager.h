#ifndef MQTT_MANAGER_H
#define MQTT_MANAGER_H

#include "esp_err.h"

/**
 * @brief Starts the MQTT client.
 */
void mqtt_manager_start(void);

/**
 * @brief Publishes a message to an MQTT topic.
 * @param topic MQTT topic.
 * @param data Payload data.
 * @param len Length of data. If 0, strlen(data) is used.
 * @param qos QoS level.
 * @param retain Retain flag.
 * @return Message ID if successful, negative on error.
 */
int mqtt_manager_publish(const char *topic, const char *data, int len, int qos, int retain);

#endif // MQTT_MANAGER_H

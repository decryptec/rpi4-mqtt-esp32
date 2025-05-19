#include "mqtt_manager.h"
#include "app_config.h"
#include "fan_ctrl.h"

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "esp_system.h"
#include "esp_event.h"
#include "esp_log.h"
#include "mqtt_client.h"
#include <inttypes.h>

static const char *TAG = "MQTT_MANAGER";
static esp_mqtt_client_handle_t client = NULL;
static int last_on_duty_percentage = 80; // Default "ON" duty
static bool state = 0;

static esp_err_t mqtt_event_handler_cb(esp_mqtt_event_handle_t event) {
    esp_mqtt_client_handle_t client_local = event->client;
    int msg_id;

    switch (event->event_id) {
        case MQTT_EVENT_CONNECTED:
            ESP_LOGI(TAG, "MQTT_EVENT_CONNECTED");
            msg_id = esp_mqtt_client_subscribe(client_local, status_t, 0);
            ESP_LOGI(TAG, "Subscribed to %s, msg_id=%d", status_t, msg_id);
            msg_id = esp_mqtt_client_subscribe(client_local, output_t, 0);
            ESP_LOGI(TAG, "Subscribed to %s, msg_id=%d", output_t, msg_id);

            mqtt_manager_publish(read_t, "0", 0, 0, 0);
            mqtt_manager_publish(temp_t, "0", 0, 0, 0);
            mqtt_manager_publish(humidity_t, "0", 0, 0, 0);
            break;

        case MQTT_EVENT_DISCONNECTED:
            ESP_LOGI(TAG, "MQTT_EVENT_DISCONNECTED");
            break;

        case MQTT_EVENT_SUBSCRIBED:
            ESP_LOGI(TAG, "MQTT_EVENT_SUBSCRIBED, msg_id=%d", event->msg_id);
            break;

        case MQTT_EVENT_UNSUBSCRIBED:
            ESP_LOGI(TAG, "MQTT_EVENT_UNSUBSCRIBED, msg_id=%d", event->msg_id);
            break;

        case MQTT_EVENT_PUBLISHED:
            ESP_LOGD(TAG, "MQTT_EVENT_PUBLISHED, msg_id=%d", event->msg_id);
            break;

        case MQTT_EVENT_DATA: {
            ESP_LOGI(TAG, "MQTT_EVENT_DATA: TOPIC=%.*s, DATA=%.*s",
                     event->topic_len, event->topic, event->data_len, event->data);

            char topic_str[event->topic_len + 1];
            strncpy(topic_str, event->topic, event->topic_len);
            topic_str[event->topic_len] = '\0';

            char data_str[event->data_len + 1];
            strncpy(data_str, event->data, event->data_len);
            data_str[event->data_len] = '\0';

            if (strcmp(topic_str, status_t) == 0) {
                ESP_LOGI(TAG, "Processing %s: %s", status_t, data_str);
                if (strcmp(data_str, "ON") == 0) {
                    fan_turn_on_fade(last_on_duty_percentage);
                    char current_duty_str[5];
                    snprintf(current_duty_str, sizeof(current_duty_str), "%d", last_on_duty_percentage);
		    state = true;
                    mqtt_manager_publish(read_t, current_duty_str, 0, 0, 0);
                } else if (strcmp(data_str, "OFF") == 0) {
                    fan_turn_off_fade();
		    state = false;
                } else {
                    ESP_LOGW(TAG, "Invalid payload for %s: %s", status_t, data_str);
                }
            } else if (strcmp(topic_str, output_t) == 0) {
                ESP_LOGI(TAG, "Processing %s: %s", output_t, data_str);
                int duty_percentage = atoi(data_str);
                if (duty_percentage >= 0 && duty_percentage <= 100) {
                    last_on_duty_percentage = duty_percentage;
		    if (state){
                    fan_set_duty_fade(duty_percentage);
		    }
                    mqtt_manager_publish(read_t, data_str, 0, 0, 0);
                } else {
                    ESP_LOGW(TAG, "Invalid duty for %s: %s", output_t, data_str);
                }
            } else {
                ESP_LOGW(TAG, "Unhandled topic: %s", topic_str);
            }
            break;
        }

        case MQTT_EVENT_ERROR:
            ESP_LOGE(TAG, "MQTT_EVENT_ERROR");
            if (event->error_handle) {
                ESP_LOGE(TAG, "Last error: 0x%x, type: %d",
                         event->error_handle->esp_tls_last_esp_err, event->error_handle->error_type);
            }
            break;
        default:
            ESP_LOGI(TAG, "Other MQTT event: %d", (int)event->event_id);
            break;
    }
    return ESP_OK;
}

static void mqtt_event_handler_wrapper(void *handler_args, esp_event_base_t base, int32_t event_id, void *event_data) {
    ESP_LOGD(TAG, "Event dispatched: base=%s, id=%" PRId32, base, event_id);
    mqtt_event_handler_cb(event_data);
}

void mqtt_manager_start(void) {
    esp_mqtt_client_config_t mqtt_cfg = { .broker.address.uri = MQTT_BROKER_URI };
    if (strlen(MQTT_CLIENT_ID) > 0) {
        mqtt_cfg.credentials.client_id = MQTT_CLIENT_ID;
    }
    client = esp_mqtt_client_init(&mqtt_cfg);
    esp_mqtt_client_register_event(client, ESP_EVENT_ANY_ID, mqtt_event_handler_wrapper, NULL);
    esp_mqtt_client_start(client);
    ESP_LOGI(TAG, "MQTT client started.");
}

int mqtt_manager_publish(const char *topic, const char *data, int len, int qos, int retain) {
    if (client == NULL) {
        ESP_LOGE(TAG, "MQTT client not initialized for publish.");
        return -1;
    }
    int actual_len = (len == 0 && data != NULL) ? strlen(data) : len;
    int msg_id = esp_mqtt_client_publish(client, topic, data, actual_len, qos, retain);

    if (msg_id < 0) {
        ESP_LOGE(TAG, "Publish failed: topic %s, len %d, err %d", topic, actual_len, msg_id);
    } else {
        ESP_LOGD(TAG, "Publish sent: topic %s, len %d, msg_id %d: %s",
                 topic, actual_len, msg_id, data ? data : "NULL");
    }
    return msg_id;
}

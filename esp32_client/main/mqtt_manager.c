// File: mqtt_manager.c
#include "mqtt_manager.h"
#include "app_config.h"

#include <stdio.h>
#include <string.h>
#include "esp_system.h"
#include "esp_event.h"
#include "esp_log.h"
#include "mqtt_client.h"
#include <inttypes.h> // For PRId32

static const char *TAG = "MQTT_MANAGER";
static esp_mqtt_client_handle_t client = NULL;

static esp_err_t mqtt_event_handler_cb(esp_mqtt_event_handle_t event)
{
    esp_mqtt_client_handle_t client_local = event->client;
    int msg_id;

    switch (event->event_id) {
        case MQTT_EVENT_CONNECTED:
            ESP_LOGI(TAG, "MQTT_EVENT_CONNECTED");

            msg_id = esp_mqtt_client_subscribe(client_local, status_t, 0);
            if (msg_id < 0) {
                ESP_LOGE(TAG, "Subscription to %s failed", status_t);
            } else {
                ESP_LOGI(TAG, "Sent subscribe successful for %s, msg_id=%d", status_t, msg_id);
            }

            msg_id = esp_mqtt_client_subscribe(client_local, output_t, 0);
            if (msg_id < 0) {
                ESP_LOGE(TAG, "Subscription to %s failed", output_t);
            } else {
                ESP_LOGI(TAG, "Sent subscribe successful for %s, msg_id=%d", output_t, msg_id);
            }

            msg_id = esp_mqtt_client_publish(client_local, read_t, "0", 1, 0, 0);
            if (msg_id < 0) {
                ESP_LOGE(TAG, "Initial publish to %s failed", read_t);
            } else {
                ESP_LOGI(TAG, "Sent initial publish successful to %s, msg_id=%d", read_t, msg_id);
            }

            msg_id = esp_mqtt_client_publish(client_local, temp_t, "0", 1, 0, 0);
            if (msg_id < 0) {
                ESP_LOGE(TAG, "Initial publish to %s failed", temp_t);
            } else {
                ESP_LOGI(TAG, "Sent initial publish successful to %s, msg_id=%d", temp_t, msg_id);
            }

            msg_id = esp_mqtt_client_publish(client_local, humidity_t, "0", 1, 0, 0);
            if (msg_id < 0) {
                ESP_LOGE(TAG, "Initial publish to %s failed", humidity_t);
            } else {
                ESP_LOGI(TAG, "Sent initial publish successful to %s, msg_id=%d", humidity_t, msg_id);
            }
            break;

        case MQTT_EVENT_DISCONNECTED:
            ESP_LOGI(TAG, "MQTT_EVENT_DISCONNECTED");
            break;

        case MQTT_EVENT_SUBSCRIBED:
            ESP_LOGI(TAG, "MQTT_EVENT_SUBSCRIBED, msg_id=%d", event->msg_id);
            ESP_LOGI(TAG, "Successfully subscribed to topic associated with msg_id %d", event->msg_id);
            break;

        case MQTT_EVENT_UNSUBSCRIBED:
            ESP_LOGI(TAG, "MQTT_EVENT_UNSUBSCRIBED, msg_id=%d", event->msg_id);
            break;

        case MQTT_EVENT_PUBLISHED:
            ESP_LOGI(TAG, "MQTT_EVENT_PUBLISHED, msg_id=%d", event->msg_id);
            break;

        case MQTT_EVENT_DATA:
            ESP_LOGI(TAG, "MQTT_EVENT_DATA");
            ESP_LOGI(TAG, "TOPIC=%.*s", event->topic_len, event->topic);
            ESP_LOGI(TAG, "DATA=%.*s", event->data_len, event->data);

            if (event->topic_len == strlen(status_t) &&
                strncmp(event->topic, status_t, event->topic_len) == 0) {
                ESP_LOGI(TAG, "Received message on %s topic", status_t);
                // Add specific processing for status_t here
            } else if (event->topic_len == strlen(output_t) &&
                       strncmp(event->topic, output_t, event->topic_len) == 0) {
                ESP_LOGI(TAG, "Received message on %s topic", output_t);
                // Add specific processing for output_t here
            } else {
                ESP_LOGW(TAG, "Received message on an unhandled subscribed topic: %.*s", event->topic_len, event->topic);
            }
            break;

        case MQTT_EVENT_ERROR:
            ESP_LOGI(TAG, "MQTT_EVENT_ERROR");
            if (event->error_handle) {
                ESP_LOGE(TAG, "Last error code: 0x%x", event->error_handle->esp_tls_last_esp_err);
                ESP_LOGE(TAG, "Last stack error: 0x%x", event->error_handle->esp_tls_stack_err);
                #if ESP_IDF_VERSION >= ESP_IDF_VERSION_VAL(4, 4, 0)
                 ESP_LOGE(TAG, "Last captured errno: %d (%s)", event->error_handle->esp_transport_sock_errno,
                                                         strerror(event->error_handle->esp_transport_sock_errno));
                #endif
            }
            break;
        default:
            ESP_LOGI(TAG, "Other event id:%d", (int)event->event_id);
            break;
    }
    return ESP_OK;
}

static void mqtt_event_handler(void *handler_args, esp_event_base_t base, int32_t event_id, void *event_data) {
    ESP_LOGD(TAG, "Event dispatched: base=%s, event_id=%" PRId32, base, event_id);
    mqtt_event_handler_cb(event_data);
}

void mqtt_manager_start(void)
{
    esp_mqtt_client_config_t mqtt_cfg = {
        .broker.address.uri = MQTT_BROKER_URI,
    };
    if (strlen(MQTT_CLIENT_ID) > 0) {
        mqtt_cfg.credentials.client_id = MQTT_CLIENT_ID;
    }

    client = esp_mqtt_client_init(&mqtt_cfg);
    esp_mqtt_client_register_event(client, ESP_EVENT_ANY_ID, mqtt_event_handler, NULL);
    esp_mqtt_client_start(client);
    ESP_LOGI(TAG, "MQTT client started.");
}

int mqtt_manager_publish(const char *topic, const char *data, int len, int qos, int retain) {
    if (client == NULL) {
        ESP_LOGE(TAG, "MQTT client not initialized for publish.");
        return -1;
    }
    int msg_id = esp_mqtt_client_publish(client, topic, data, len, qos, retain);
    if (msg_id < 0) {
        ESP_LOGE(TAG, "Failed to publish message to topic %s, error code: %d", topic, msg_id);
    } else {
        ESP_LOGI(TAG, "Publish sent to topic %s, msg_id=%d", topic, msg_id);
    }
    return msg_id;
}

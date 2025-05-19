#include <stdio.h>
#include <string.h>
#include <inttypes.h>

#include "nvs_flash.h"
#include "esp_log.h"
#include "esp_system.h"
#include "driver/gpio.h"
#include "freertos/FreeRTOS.h"
#include "freertos/task.h"

#include "app_config.h"
#include "wifi_manager.h"
#include "mqtt_manager.h"
#include "dht.h"
#include "fan_ctrl.h"

static float temp_reading_global = 0.0f;
static float humidity_reading_global = 0.0f;

static const char *TAG = "APP_MAIN";

esp_err_t initialize_system_peripherals(void) {
    ESP_LOGI(TAG, "Initializing peripherals...");
    esp_err_t ret = gpio_set_pull_mode(dht_pin, GPIO_PULLUP_ONLY);
    if (ret != ESP_OK) {
        ESP_LOGE(TAG, "Failed to set DHT pin %d pull-up: %s", (int)dht_pin, esp_err_to_name(ret));
    } else {
        ESP_LOGI(TAG, "DHT Pin %d pull-up set.", (int)dht_pin);
    }

    ret = fan_pwm_init();
    if (ret != ESP_OK) {
        ESP_LOGE(TAG, "Fan PWM initialization failed: %s.", esp_err_to_name(ret));
        return ret;
    }
    ESP_LOGI(TAG, "Fan PWM initialized.");
    return ESP_OK;
}

void dht_publish_task(void *pvParameters) {
    ESP_LOGI(TAG, "DHT Publish Task started.");
    char sens_buf[16];

    while(1) {
        vTaskDelay(pdMS_TO_TICKS(5000));
        if(dht_read_float_data(DHT_TYPE_DHT11, dht_pin, &humidity_reading_global, &temp_reading_global) == ESP_OK) {
            ESP_LOGD(TAG, "DHT: Temp=%.1fC, Hum=%.1f%%", temp_reading_global, humidity_reading_global);
            snprintf(sens_buf, sizeof(sens_buf),"%.1f", humidity_reading_global);
            mqtt_manager_publish(humidity_t, sens_buf, 0, 0, 0);
            snprintf(sens_buf, sizeof(sens_buf),"%.1f", temp_reading_global);
            mqtt_manager_publish(temp_t, sens_buf, 0, 0, 0);
        } else {
            ESP_LOGE(TAG, "Failed to read DHT sensor.");
        }
    }
}

void app_main(void) {
    ESP_LOGI(TAG, "[APP] Startup..");
    ESP_LOGI(TAG, "[APP] Free memory: %" PRIu32 " bytes", esp_get_free_heap_size());
    ESP_LOGI(TAG, "[APP] IDF version: %s", esp_get_idf_version());

    esp_log_level_set("*", ESP_LOG_INFO);
    esp_log_level_set("MQTT_CLIENT", ESP_LOG_VERBOSE);
    esp_log_level_set("MQTT_MANAGER", ESP_LOG_VERBOSE);
    esp_log_level_set("WIFI_MANAGER", ESP_LOG_VERBOSE);
    esp_log_level_set(TAG, ESP_LOG_VERBOSE);
    esp_log_level_set("FAN_CTRL", ESP_LOG_VERBOSE);
    esp_log_level_set("TRANSPORT*", ESP_LOG_VERBOSE);

    esp_err_t ret = nvs_flash_init();
    if (ret == ESP_ERR_NVS_NO_FREE_PAGES || ret == ESP_ERR_NVS_NEW_VERSION_FOUND) {
      ESP_ERROR_CHECK(nvs_flash_erase());
      ret = nvs_flash_init();
    }
    ESP_ERROR_CHECK(ret);

    if (initialize_system_peripherals() != ESP_OK) {
        ESP_LOGE(TAG, "Peripheral initialization failed. Application might not function correctly.");
    }

    if (wifi_manager_init_sta() == ESP_OK) {
        ESP_LOGI(TAG, "Wi-Fi initialized and connected.");
        mqtt_manager_start();
        if (xTaskCreate(dht_publish_task, "DHT_PublishTask", 3072, NULL, tskIDLE_PRIORITY + 4, NULL) != pdPASS) {
            ESP_LOGE(TAG, "Failed to create DHT_PublishTask.");
        } else {
            ESP_LOGI(TAG, "DHT_PublishTask created successfully.");
        }
    } else {
        ESP_LOGE(TAG, "Failed to initialize Wi-Fi.");
    }

    ESP_LOGI(TAG, "app_main finished setup.");
    while(1) {
        vTaskDelay(pdMS_TO_TICKS(30000));
        ESP_LOGD(TAG, "app_main loop tick. Heap: %" PRIu32, esp_get_free_heap_size());
    }
}

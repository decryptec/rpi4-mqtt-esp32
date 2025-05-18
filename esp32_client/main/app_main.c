#include <stdio.h>
#include <string.h>
#include <inttypes.h>

#include "nvs_flash.h"
#include "esp_log.h"
#include "freertos/FreeRTOS.h"
#include "freertos/task.h"

#include "app_config.h"
#include "wifi_manager.h"
#include "mqtt_manager.h"
#include "dht.h"

float temp = 0.0 , humidity = 0.0;
int DC = 0;

static const char *TAG = "APP_MAIN";

int gpio_init(void)
{
	//DHT
	gpio_set_pull_mode(dht_pin, GPIO_PULLUP_ONLY);

	return 0;
}

void dht_publish(void *pvParameters)
{
	int msg_id;
	char sens_buf[32];
	while(1)
	{
		// Wait for the next publish interval
		vTaskDelay(pdMS_TO_TICKS(5000)); // Delay for 5 seconds
		if(dht_read_float_data(DHT_TYPE_DHT11, dht_pin, &humidity, &temp) == ESP_OK){
			snprintf(sens_buf, sizeof(sens_buf),"%.2f",humidity);
			msg_id = mqtt_manager_publish(humidity_t,sens_buf, 0, 0, 0);
			if (msg_id>=0){
				ESP_LOGI(TAG, "Humidity published: %s (msg_id: %d)", sens_buf, msg_id);
			}else{
				ESP_LOGE(TAG, "Failed to publish: %s", sens_buf);
			}

			snprintf(sens_buf, sizeof(sens_buf),"%.2f",temp);
			msg_id = mqtt_manager_publish(temp_t,sens_buf, 0, 0, 0);
			if (msg_id>=0){
				ESP_LOGI(TAG, "Temperature published: %s (msg_id: %d)", sens_buf, msg_id);
			}else{
				ESP_LOGE(TAG, "Failed to publish: %s", sens_buf);
			}
		}
	}
}
/*
void fan_subscribe(void *pvParameters){
	int msg_id;
	char buf[32];
}*/

void app_main(void)
{
	ESP_LOGI(TAG, "[APP] Startup..");
	ESP_LOGI(TAG, "[APP] Free memory: %" PRIu32 " bytes", esp_get_free_heap_size());
	ESP_LOGI(TAG, "[APP] IDF version: %s", esp_get_idf_version());

	esp_log_level_set("*", ESP_LOG_INFO);
	esp_log_level_set("MQTT_CLIENT", ESP_LOG_VERBOSE);
	esp_log_level_set("MQTT_MANAGER", ESP_LOG_VERBOSE);
	esp_log_level_set("WIFI_MANAGER", ESP_LOG_VERBOSE);
	esp_log_level_set("APP_MAIN", ESP_LOG_VERBOSE);
	esp_log_level_set("TRANSPORT*", ESP_LOG_VERBOSE); // Catches TRANSPORT_TCP, TRANSPORT_SSL, TRANSPORT

	esp_err_t ret = nvs_flash_init();
	if (ret == ESP_ERR_NVS_NO_FREE_PAGES || ret == ESP_ERR_NVS_NEW_VERSION_FOUND) {
		ESP_ERROR_CHECK(nvs_flash_erase());
		ret = nvs_flash_init();
	}
	ESP_ERROR_CHECK(ret);

	if (wifi_manager_init_sta() == ESP_OK) {
		ESP_LOGI(TAG, "Wi-Fi initialized and connected.");
		mqtt_manager_start();
		
		BaseType_t task_created = xTaskCreate(
				dht_publish,
				"DHT_Publish",
				4096,
				NULL,
				tskIDLE_PRIORITY + 5,
				NULL
				);
		if (task_created == pdPASS){
			ESP_LOGI(TAG, "DHT_Publish task created successfully.");
		}else{
			ESP_LOGE(TAG, "DHT_Publish failed to create.");
		}

	} else {
		ESP_LOGE(TAG, "Failed to initialize Wi-Fi. MQTT will not start.");
	}

	while(1){
		vTaskDelay(pdMS_TO_TICKS(10000));

		ESP_LOGD(TAG, "Main loop tick.");
	}
}

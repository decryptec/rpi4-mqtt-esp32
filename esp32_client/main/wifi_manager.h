#ifndef WIFI_MANAGER_H
#define WIFI_MANAGER_H

#include "esp_err.h"

/**
 * @brief Initializes Wi-Fi and connects to the configured AP.
 * @return ESP_OK on successful connection, ESP_FAIL otherwise.
 */
esp_err_t wifi_manager_init_sta(void);

#endif // WIFI_MANAGER_H

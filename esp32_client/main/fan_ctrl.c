#include <stdio.h>
#include "freertos/FreeRTOS.h"
#include "freertos/task.h"
#include "freertos/semphr.h"
#include "inttypes.h"
#include "driver/ledc.h"
#include "esp_err.h"
#include "esp_log.h"

#include "fan_ctrl.h" 

static const char *TAG_FAN = "FAN_CTRL";

// Internal Configuration for this module
#define FAN_CTRL_PWM_TIMER              LEDC_TIMER_0
#define FAN_CTRL_PWM_MODE               LEDC_HIGH_SPEED_MODE
#define FAN_CTRL_PWM_OUTPUT_GPIO        (18) // Example GPIO, change as needed or use app_config.h
#define FAN_CTRL_PWM_CHANNEL            LEDC_CHANNEL_0
#define FAN_CTRL_PWM_RESOLUTION_ENUM    LEDC_TIMER_13_BIT
#define FAN_CTRL_PWM_RESOLUTION_BITS    (13)
#define FAN_CTRL_PWM_FREQUENCY_HZ       (5000)
#define FAN_CTRL_PWM_FADE_TIME_MS       (1000) // Default fade time in ms

#define MAX_LEDC_DUTY_VALUE        ((1 << FAN_CTRL_PWM_RESOLUTION_BITS) - 1)

static SemaphoreHandle_t fan_fade_end_semaphore = NULL;

static uint32_t map_percentage_to_duty(int percentage) {
    if (percentage < 0) percentage = 0;
    if (percentage > 100) percentage = 100;
    return (uint32_t)(((float)percentage / 100.0f) * MAX_LEDC_DUTY_VALUE);
}

static IRAM_ATTR bool cb_fan_fade_end_event(const ledc_cb_param_t *param, void *user_arg) {
    BaseType_t taskAwoken = pdFALSE;
    if (param->event == LEDC_FADE_END_EVT) {
        SemaphoreHandle_t sem = (SemaphoreHandle_t) user_arg;
        if (sem != NULL) {
            xSemaphoreGiveFromISR(sem, &taskAwoken);
        }
    }
    return (taskAwoken == pdTRUE);
}

esp_err_t fan_pwm_init(void) {
    ESP_LOGI(TAG_FAN, "Initializing Fan PWM Control");

    ledc_timer_config_t timer_conf = {
        .speed_mode       = FAN_CTRL_PWM_MODE,
        .duty_resolution  = FAN_CTRL_PWM_RESOLUTION_ENUM,
        .timer_num        = FAN_CTRL_PWM_TIMER,
        .freq_hz          = FAN_CTRL_PWM_FREQUENCY_HZ,
        .clk_cfg          = LEDC_AUTO_CLK
    };
    esp_err_t ret = ledc_timer_config(&timer_conf);
    if (ret != ESP_OK) {
        ESP_LOGE(TAG_FAN, "ledc_timer_config failed: %s", esp_err_to_name(ret));
        return ret;
    }

    ledc_channel_config_t channel_conf = {
        .gpio_num       = FAN_CTRL_PWM_OUTPUT_GPIO,
        .speed_mode     = FAN_CTRL_PWM_MODE,
        .channel        = FAN_CTRL_PWM_CHANNEL,
        .intr_type      = LEDC_INTR_DISABLE,
        .timer_sel      = FAN_CTRL_PWM_TIMER,
        .duty           = 0,
        .hpoint         = 0
    };
    #if ESP_IDF_VERSION >= ESP_IDF_VERSION_VAL(5, 0, 0)
        channel_conf.flags.output_invert = 0;
    #endif
    ret = ledc_channel_config(&channel_conf);
    if (ret != ESP_OK) {
        ESP_LOGE(TAG_FAN, "ledc_channel_config failed: %s", esp_err_to_name(ret));
        return ret;
    }

    ret = ledc_fade_func_install(0);
    if (ret != ESP_OK) {
        ESP_LOGE(TAG_FAN, "ledc_fade_func_install failed: %s", esp_err_to_name(ret));
        return ret;
    }

    fan_fade_end_semaphore = xSemaphoreCreateBinary();
    if (fan_fade_end_semaphore == NULL) {
        ESP_LOGE(TAG_FAN, "Failed to create fan_fade_end_semaphore!");
        return ESP_FAIL;
    }

    ledc_cbs_t callbacks = {.fade_cb = cb_fan_fade_end_event};
    ret = ledc_cb_register(FAN_CTRL_PWM_MODE, FAN_CTRL_PWM_CHANNEL, &callbacks, (void *) fan_fade_end_semaphore);
    if (ret != ESP_OK) {
        ESP_LOGE(TAG_FAN, "ledc_cb_register failed: %s", esp_err_to_name(ret));
        vSemaphoreDelete(fan_fade_end_semaphore);
        fan_fade_end_semaphore = NULL;
        return ret;
    }

    ESP_LOGI(TAG_FAN, "Fan PWM Initialized Successfully");
    return ESP_OK;
}

esp_err_t fan_set_duty_fade(int duty_percentage) {
    if (fan_fade_end_semaphore == NULL) {
        ESP_LOGE(TAG_FAN, "Fan PWM not initialized");
        return ESP_ERR_INVALID_STATE;
    }
    uint32_t target_duty_raw = map_percentage_to_duty(duty_percentage);
    ESP_LOGI(TAG_FAN, "Fading fan to %d%% (raw: %" PRIu32 ")", duty_percentage, target_duty_raw);

    esp_err_t ret = ledc_set_fade_with_time(FAN_CTRL_PWM_MODE, FAN_CTRL_PWM_CHANNEL, target_duty_raw, FAN_CTRL_PWM_FADE_TIME_MS);
    if (ret != ESP_OK) return ret;

    ret = ledc_fade_start(FAN_CTRL_PWM_MODE, FAN_CTRL_PWM_CHANNEL, LEDC_FADE_NO_WAIT);
    if (ret != ESP_OK) return ret;

    if (xSemaphoreTake(fan_fade_end_semaphore, pdMS_TO_TICKS(FAN_CTRL_PWM_FADE_TIME_MS + 200)) == pdTRUE) {
        ESP_LOGI(TAG_FAN, "Fan fade to %d%% complete.", duty_percentage);
        return ESP_OK;
    } else {
        ESP_LOGW(TAG_FAN, "Fan fade to %d%% timed out. Setting duty directly.", duty_percentage);
        ledc_set_duty(FAN_CTRL_PWM_MODE, FAN_CTRL_PWM_CHANNEL, target_duty_raw);
        ledc_update_duty(FAN_CTRL_PWM_MODE, FAN_CTRL_PWM_CHANNEL);
        return ESP_ERR_TIMEOUT;
    }
}

esp_err_t fan_turn_on_fade(int duty_percentage) {
    ESP_LOGI(TAG_FAN, "Turning fan ON to %d%%", duty_percentage);
    return fan_set_duty_fade(duty_percentage);
}

esp_err_t fan_turn_off_fade(void) {
    ESP_LOGI(TAG_FAN, "Turning fan OFF");
    return fan_set_duty_fade(0);
}

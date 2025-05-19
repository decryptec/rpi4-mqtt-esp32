#ifndef FAN_CTRL_H
#define FAN_CTRL_H

#include "esp_err.h"

/**
 * @brief Initializes the PWM fan control module.
 * Must be called once before using other fan control functions.
 * @return ESP_OK on success, or an error code on failure.
 */
esp_err_t fan_pwm_init(void);

/**
 * @brief Sets the fan speed using PWM with a fade effect.
 * This function is blocking until the fade completes or times out.
 *
 * @param duty_percentage Desired duty cycle (0-100).
 * @return ESP_OK on successful fade, ESP_ERR_TIMEOUT if fade timed out,
 *         or other error code on failure.
 */
esp_err_t fan_set_duty_fade(int duty_percentage);

/**
 * @brief Turns the fan on to a specified duty cycle with a fade.
 *
 * @param duty_percentage Desired duty cycle when "on" (0-100).
 * @return ESP_OK on success, or an error code on failure.
 */
esp_err_t fan_turn_on_fade(int duty_percentage);

/**
 * @brief Turns the fan off by fading the duty cycle to 0.
 *
 * @return ESP_OK on success, or an error code on failure.
 */
esp_err_t fan_turn_off_fade(void);

#endif // FAN_CTRL_H

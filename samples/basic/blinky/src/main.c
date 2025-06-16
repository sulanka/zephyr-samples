/*
 * Copyright (c) 2016 Intel Corporation
 *
 * SPDX-License-Identifier: Apache-2.0
 */

#include <stdio.h>
#include <zephyr/kernel.h>
#include <zephyr/drivers/gpio.h>

/* 1000 msec = 1 sec */
#define SLEEP_TIME_MS   2000

/* The devicetree node identifier for the "led0" alias. */
#define LED0_NODE DT_ALIAS(led0)
#define LED_RED_NODE DT_ALIAS(ledred)

/*
 * A build error on this line means your board is unsupported.
 * See the sample documentation for information on how to fix this.
 */
static const struct gpio_dt_spec ledgreen = GPIO_DT_SPEC_GET(LED0_NODE, gpios);
static const struct gpio_dt_spec redled = GPIO_DT_SPEC_GET(LED_RED_NODE, gpios);

int main(void)
{
	int ret;
	bool led_state = true;
	bool red_led_state = true;

	if (!gpio_is_ready_dt(&ledgreen)) {
		return 0;
	}

	if (!gpio_is_ready_dt(&redled)) {
		return 0;
	}

	ret = gpio_pin_configure_dt(&ledgreen, GPIO_OUTPUT_ACTIVE);
	if (ret < 0) {
		return 0;
	}
	ret = gpio_pin_configure_dt(&redled, GPIO_OUTPUT_ACTIVE);
	if (ret < 0) {
		return 0;
	}


	while (1) {
		ret = gpio_pin_toggle_dt(&ledgreen);
		if (ret < 0) {
			return 0;
		}

		led_state = !led_state;
		printf("Green LED on dev board: %s\n", led_state ? "ON" : "OFF");

		ret = gpio_pin_toggle_dt(&redled);
		if (ret < 0) {
			return 0;
		}

		red_led_state = !red_led_state;
		printf("Red LED on dev board: %s\n", red_led_state ? "ON" : "OFF");

		k_msleep(SLEEP_TIME_MS);
	}
	return 0;
}

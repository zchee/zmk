/*
 * Copyright (c) 2020 The ZMK Contributors
 *
 * SPDX-License-Identifier: MIT
 */

#pragma once

#include <zmk/events/sensor_event.h>
#include <zmk/sensors.h>

#define ZMK_SPLIT_RUN_BEHAVIOR_DEV_LEN 9

struct sensor_event {
    uint8_t sensor_index;

    uint8_t channel_data_size;
    struct zmk_sensor_channel_data channel_data[ZMK_SENSOR_EVENT_MAX_CHANNELS];
} __packed;

struct zmk_split_run_behavior_data {
    uint8_t position;
    uint8_t state;
    uint32_t param1;
    uint32_t param2;
} __packed;

struct zmk_split_run_behavior_payload {
    struct zmk_split_run_behavior_data data;
    char behavior_dev[ZMK_SPLIT_RUN_BEHAVIOR_DEV_LEN];
} __packed;

#if IS_ENABLED(CONFIG_ZMK_RGB_UNDERGLOW)
struct zmk_split_update_led_data {
    uint8_t layer;
    uint8_t indicators;
} __packed;
#endif

#if IS_ENABLED(CONFIG_ZMK_BACKLIGHT)
struct zmk_split_update_bl_data {
    uint8_t brightness;
    bool on;
} __packed;
#endif

int zmk_split_bt_position_pressed(uint8_t position);
int zmk_split_bt_position_released(uint8_t position);
int zmk_split_bt_sensor_triggered(uint8_t sensor_index,
                                  const struct zmk_sensor_channel_data channel_data[],
                                  size_t channel_data_size);

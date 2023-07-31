
#pragma once

#include <zephyr/bluetooth/addr.h>
#include <zmk/behavior.h>
#include <zmk/rgb_underglow.h>
#include <zmk/backlight.h>

#if IS_ENABLED(CONFIG_ZMK_SPLIT_PERIPHERAL_HID_INDICATORS)
#include <zmk/hid_indicators_types.h>
#endif // IS_ENABLED(CONFIG_ZMK_SPLIT_PERIPHERAL_HID_INDICATORS)

int zmk_split_bt_invoke_behavior(uint8_t source, struct zmk_behavior_binding *binding,
                                 struct zmk_behavior_binding_event event, bool state);

#if IS_ENABLED(CONFIG_ZMK_SPLIT_PERIPHERAL_HID_INDICATORS)

int zmk_split_bt_update_hid_indicator(zmk_hid_indicators_t indicators);

#endif // IS_ENABLED(CONFIG_ZMK_SPLIT_PERIPHERAL_HID_INDICATORS)

#if IS_ENABLED(CONFIG_ZMK_SPLIT_BLE_CENTRAL_BATTERY_LEVEL_FETCHING)

int zmk_split_get_peripheral_battery_level(uint8_t source, uint8_t *level);

#endif // IS_ENABLED(CONFIG_ZMK_SPLIT_BLE_CENTRAL_BATTERY_LEVEL_FETCHING)
#if IS_ENABLED(CONFIG_ZMK_RGB_UNDERGLOW)
int zmk_split_bt_update_led(struct zmk_periph_led *periph);
#endif

#if IS_ENABLED(CONFIG_ZMK_BACKLIGHT)
int zmk_split_bt_update_bl(struct backlight_state *periph);
#endif

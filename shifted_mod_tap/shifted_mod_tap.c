// Copyright 2025 Jacob Jerrell (@jjerrell)
// SPDX-License-Identifier: GPL-3.0-or-later

#include QMK_KEYBOARD_H

ASSERT_COMMUNITY_MODULES_MIN_API_VERSION(0, 1, 0);

bool process_record_shifted_mod_tap(uint16_t keycode, keyrecord_t *record) {
    if (IS_QK_MOD_TAP(keycode)) {
        switch (keycode) {
            case KC_TILD ... KC_QUESTION:
                // Check tap.count to make sure we aren't processing a modifier
                if (record->tap.count && record->event.pressed) {
                    // Apply shift
                    register_code(KC_LSFT);
                    // Using tap_code16 we can send the uint16_t keycode parameter
                    tap_code16(keycode);
                    // Release shift
                    unregister_code(KC_LSFT);
                    // stop processing this keycode or the firmware will send the unshifted keycode also
                    return false;
                }
                // Modifier processing or not enough time elapsed to determine if it's a tap
                break;
        }
    }
    return true;
}
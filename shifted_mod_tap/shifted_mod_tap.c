// Copyright 2025 Jacob Jerrell (@jjerrell)
// SPDX-License-Identifier: GPL-3.0-or-later

#include QMK_KEYBOARD_H

ASSERT_COMMUNITY_MODULES_MIN_API_VERSION(0, 1, 0);

/**
 * @brief Main handler for mod-tap/layer-tap shifted keycode interception
 *
 * @param keycode Keycode from switch matrix
 * @param record keyrecord_t data structure
 * @return true Send keycode from matrix to host
 * @return false Stop processing and do not send to host
 */
bool process_record_shifted_mod_tap(uint16_t keycode, keyrecord_t *record) {
    switch (keycode) {
            case CTL_T(KC_HASH):
            case CTL_T(KC_CIRC):
            case ALT_T(KC_RPRN):
            case ALT_T(KC_LCBR):
            case ALT_T(KC_RCBR):
            case GUI_T(KC_RCBR):
            case GUI_T(KC_LPRN):
            case GUI_T(KC_RPRN):
#           ifdef ENABLE_RAISE_MIGRATION
                case SFT_T(KC_RABK):
#           else // !ENABLE_RAISE_MIGRATION
                case CTL_T(KC_QUES):
#           endif // ENABLE_RAISE_MIGRATION
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
    // if (IS_QK_MOD_TAP(keycode) && record->tap.count) {
    //     uint16_t unwrapped_keycode = QK_MOD_TAP_GET_TAP_KEYCODE(keycode);
    //     switch (unwrapped_keycode) {
    //         case KC_TILDE:
    //         case KC_EXCLAIM:
    //         case KC_AT:
    //         case KC_HASH:
    //         case KC_DOLLAR:
    //         case KC_PERCENT:
    //         case KC_CIRCUMFLEX:
    //         case KC_AMPERSAND:
    //         case KC_ASTERISK:
    //         case KC_LEFT_PAREN:
    //         case KC_RIGHT_PAREN:
    //         case KC_UNDERSCORE:
    //         case KC_PLUS:
    //         case KC_LEFT_CURLY_BRACE:
    //         case KC_RIGHT_CURLY_BRACE:
    //         case KC_PIPE:
    //         case KC_COLON:
    //         case KC_DOUBLE_QUOTE:
    //         case KC_LEFT_ANGLE_BRACKET:
    //         case KC_RIGHT_ANGLE_BRACKET:
    //         case KC_QUESTION:
    //             // Check tap.count to make sure we aren't processing a modifier
    //             tap_code16(unwrapped_keycode);
    //             return false;
    //             // if (record->event.pressed) {
    //             //     // Apply shift
    //             //     register_code(KC_LSFT);
    //             //     // Using tap_code16 we can send the uint16_t keycode parameter
    //             //     tap_code16(keycode);
    //             //     // Release shift
    //             //     unregister_code(KC_LSFT);
    //             //     // stop processing this keycode or the firmware will send the unshifted keycode also
    //             //     return false;
    //             // }
    //             // Modifier processing or not enough time elapsed to determine if it's a tap
    //             break;
    //     }
    // }
    return true;
}
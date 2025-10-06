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
    /*
    In C, the expression & ~MASK is used to clear specific bits in a variable while 
    leaving the other bits unchanged. The ~ operator performs a bitwise NOT, which 
    inverts all the bits of MASK, turning 1s into 0s and 0s into 1s. The & operator 
    then performs a bitwise AND between the original value and the inverted mask. 
    This operation results in the bits corresponding to the 1s in the original MASK 
    being cleared (set to 0), while all other bits remain unaffected.
    
    For example, if MASK is 0x00000040 (which has only bit 6 set), then ~MASK will 
    have all bits set except bit 6. Applying & ~MASK to a variable will clear bit 6 
    of that variable, regardless of its original state, because the AND operation 
    with a 0 in that position forces the result to 0.
    
    This technique is commonly used to ensure a specific bit is cleared, even when 
    its current value is unknown.
    */

    // The logic commented below might be useful with the above description in mind. 
    // But we likely don't want to return from here. Unless, perhaps, the logic here
    // conflicts with "unshifting" shifted keys and somoene cares.

// #ifdef NO_ACTION_ONESHOT
//     if ((get_mods() & ~MOD_MASK_SHIFT) != 0)
// #else  // NO_ACTION_ONESHOT
//     if (((get_mods() | get_oneshot_mods()) & ~MOD_MASK_SHIFT) != 0)
// #endif // NO_ACTION_ONESHOT
//     {
//         return true;
//     }

    // if (!IS_QK_MOD_TAP(keycode) && !IS_QK_LAYER_TAP(keycode)) {
    //     // Nothing for us to do here.
    //     return true;
    // }

    // switch (keycode) {
    //     case KC_TILDE:
    //     case KC_EXCLAIM:
    //     case KC_AT:
    //     case KC_HASH:
    //     case KC_DOLLAR:
    //     case KC_PERCENT:
    //     case KC_CIRCUMFLEX:
    //     case KC_AMPERSAND:
    //     case KC_ASTERISK:
    //     case KC_LEFT_PAREN:
    //     case KC_RIGHT_PAREN:
    //     case KC_UNDERSCORE:
    //     case KC_PLUS:
    //     case KC_LEFT_CURLY_BRACE:
    //     case KC_RIGHT_CURLY_BRACE:
    //     case KC_PIPE:
    //     case KC_COLON:
    //     case KC_DOUBLE_QUOTE:
    //     case KC_LEFT_ANGLE_BRACKET:
    //     case KC_RIGHT_ANGLE_BRACKET:
    //     case KC_QUESTION:
    //         // Check that tap.count has a value so we aren't processing a mod
    //         if (record->tap.count) {
    //             if (IS_QK_MOD_TAP(keycode)) {
    //                 keycode = QK_MOD_TAP_GET_TAP_KEYCODE(keycode);
    //             }
    //             if (IS_QK_LAYER_TAP(keycode)) {
    //                 keycode = QK_LAYER_TAP_GET_TAP_KEYCODE(keycode);
    //             }
    //         } else {
    //             // Must be processing a mod. Nothing for us to do about it.
    //             return true;
    //         }
            
    //         // Apply shift
    //         register_code(KC_LSFT);
    //         // Using tap_code16 we can send the uint16_t keycode parameter
    //         tap_code16(keycode);
    //         // Release shift
    //         unregister_code(KC_LSFT);
    //         // stop processing this keycode or the firmware will send the unshifted keycode also
    //         return false;
    // }

// Current, functional version
    switch (keycode) {
        case CTL_T(KC_HASH):
        case CTL_T(KC_CIRC):
        case ALT_T(KC_RPRN):
        case ALT_T(KC_LCBR):
        case ALT_T(KC_RCBR):
        case GUI_T(KC_RCBR):
        case GUI_T(KC_LPRN):
        case GUI_T(KC_RPRN):
        case SFT_T(KC_RABK):
        case CTL_T(KC_QUES):
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
    return true;
}
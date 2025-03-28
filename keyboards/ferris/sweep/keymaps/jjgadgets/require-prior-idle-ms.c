#include <stdint.h>
#include "keycodes.h"
#include QMK_KEYBOARD_H
#if __has_include("keymap.h")
#    include "keymap.h"
#endif
// ZMK's require-prior-idle-ms (from https://github.com/qmk/qmk_firmware/issues/24262#issuecomment-2301722637)
#ifndef REQUIRE_PRIOR_IDLE_MS
#define REQUIRE_PRIOR_IDLE_MS 150
#endif
// Decision macro for mod-tap keys to override
#define IS_HOMEROW_MOD_TAP(kc) (              \
    IS_QK_MOD_TAP(kc)                      && \
    QK_MOD_TAP_GET_TAP_KEYCODE(kc) >= KC_A && \
    QK_MOD_TAP_GET_TAP_KEYCODE(kc) <= KC_Z    )

// Decision macro for preceding trigger key and typing interval
#define IS_TYPING(k) ( \
    ((uint8_t)(k) <= KC_Z) && \
    (last_input_activity_elapsed() < REQUIRE_PRIOR_IDLE_MS)    )

bool pre_process_record_user(uint16_t keycode, keyrecord_t *record) {
    static bool     is_pressed[UINT8_MAX];
    static uint16_t prev_keycode;
    const  uint16_t tap_keycode = QK_MOD_TAP_GET_TAP_KEYCODE(keycode);

    if (record->event.pressed) {
        // Press the tap keycode if the tap-hold key follows the previous key swiftly
        if (IS_HOMEROW_MOD_TAP(keycode) && IS_TYPING(prev_keycode)) {
            is_pressed[tap_keycode] = true;
            record->keycode         = tap_keycode;
        }
        // Cache the keycode for subsequent tap decision
        prev_keycode = keycode;
    }

    // Release the tap keycode if pressed
    else if (is_pressed[tap_keycode]) {
        is_pressed[tap_keycode] = false;
        record->keycode         = tap_keycode;
    }

    return true;
}

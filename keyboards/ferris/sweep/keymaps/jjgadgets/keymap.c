#include QMK_KEYBOARD_H
#if __has_include("keymap.h")
#    include "keymap.h"
#endif


/* THIS FILE WAS GENERATED!
 *
 * This file was generated by qmk json2c. You may or may not want to
 * edit it directly.
 */

enum layer_names {
    _DEFAULT,
    _NUM,
    _FN,
};

const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {
    [_DEFAULT] = LAYOUT_split_3x5_2(
        KC_Q, KC_W, KC_F, KC_P, KC_G,                           KC_J, KC_L, KC_U, KC_Y, KC_COLON,
        KC_A, KC_R, KC_S, KC_T, KC_D,                           KC_H, KC_N, KC_E, KC_I, KC_O,
        KC_Z, KC_X, RALT_T(KC_C), RGUI_T(KC_V), KC_B,           KC_K, KC_M, KC_COMM, KC_DOT, KC_SLSH,
        LCTL_T(KC_ESC), LSFT_T(KC_SPC),                         MEH_T(KC_BSPC), LT(_NUM, QK_REP)
    ),
    [_NUM] = LAYOUT_split_3x5_2(
        KC_GRV, KC_1, KC_2, KC_3, KC_COMM,                      KC_BSLS, KC_HOME, KC_UP, KC_END, KC_DEL,
        KC_ENTER, KC_4, KC_5, KC_6, KC_DOT,                     KC_TAB, KC_LEFT, KC_DOWN, KC_RIGHT, KC_QUOTE,
        LT(2, KC_CAPS), KC_7, KC_8, KC_9, KC_0,                 KC_LBRC, KC_RBRC, KC_MINUS, KC_EQUAL, KC_PSCR,
        LCTL_T(TG(_NUM)), LSFT_T(KC_SPC),                       MEH_T(KC_BSPC), KC_TRNS
    ),
    [_FN] = LAYOUT_split_3x5_2(
        KC_LALT, KC_F1, KC_F2, KC_F3, KC_F10,                   KC_NO, KC_NO, KC_NO, KC_NO, LCA(KC_DEL),
        KC_LGUI, KC_F4, KC_F5, KC_F6, KC_F11,                   KC_NO, KC_NO, KC_NO, KC_NO, KC_NO,
        KC_TRNS, KC_F7, KC_F8, KC_F9, KC_F12,                   KC_NO, KC_NO, KC_NO, KC_NO, KC_NO,
        TO(_DEFAULT), KC_NO,                                    KC_NO, TO(_FN)
    )
};

// hold-tap config
bool get_hold_on_other_key_press(uint16_t keycode, keyrecord_t *record) {
    switch (keycode) {
        case LCTL_T(KC_ESC):
        case LSFT_T(KC_SPC):
        case MEH_T(KC_BSPC):
        case LT(_NUM, QK_REP):
            // Immediately select the hold action when another key is pressed.
            return true;
        default:
            // Do not select the hold action when another key is pressed.
            return false;
    }
}
bool get_permissive_hold(uint16_t keycode, keyrecord_t *record) {
    switch (keycode) {
        case LCTL_T(KC_ESC):
        case LSFT_T(KC_SPC):
        case MEH_T(KC_BSPC):
        case LT(_NUM, QK_REP):
            // Do not select the hold action when another key is tapped.
            return false;
        default:
            // Immediately select the hold action when another key is tapped.
            return true;
    }
}
uint16_t get_tapping_term(uint16_t keycode, keyrecord_t *record) {
    switch (keycode) {
        case LCTL_T(KC_ESC):
        case LSFT_T(KC_SPC):
        case MEH_T(KC_BSPC):
        case LT(_NUM, QK_REP):
            return 200;
        default:
            return 280;
    }
}
uint16_t get_quick_tap_term(uint16_t keycode, keyrecord_t *record) {
    switch (keycode) {
        case LCTL_T(KC_ESC):
        case LSFT_T(KC_SPC):
        case MEH_T(KC_BSPC):
        case LT(_NUM, QK_REP):
            return 200;
        default:
            return 175;
    }
}
const char chordal_hold_layout[MATRIX_ROWS][MATRIX_COLS] PROGMEM =
    LAYOUT(
        'L', 'L', 'L', 'L', 'L',  'R', 'R', 'R', 'R', 'R',
        'L', 'L', 'L', 'L', 'L',  'R', 'R', 'R', 'R', 'R',
        'L', 'L', 'L', 'L', 'L',  'R', 'R', 'R', 'R', 'R',
                       '*', '*',  '*', '*'
    );

// ZMK's require-prior-idle-ms (from https://github.com/qmk/qmk_firmware/issues/24262#issuecomment-2301722637)
// Decision macro for mod-tap keys to override
#define IS_HOMEROW_MOD_TAP(kc) (              \
    IS_QK_MOD_TAP(kc)                      && \
    QK_MOD_TAP_GET_TAP_KEYCODE(kc) >= KC_A && \
    QK_MOD_TAP_GET_TAP_KEYCODE(kc) <= KC_Z    )

// Decision macro for preceding trigger key and typing interval
#define IS_TYPING(k) ( \
    ((uint8_t)(k) <= KC_Z || (uint8_t)(k) == KC_SPC) && \
    (last_input_activity_elapsed() < 150)    )

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

// key overrides (mod morphs)
const key_override_t alt_tab_morph = ko_make_with_layers(MOD_BIT(KC_RALT), KC_A, LALT(KC_TAB), 1 << _DEFAULT);
const key_override_t colon_morph = ko_make_basic(MOD_MASK_SHIFT, KC_COLON, KC_SCLN);
// This globally defines all key overrides to be used
const key_override_t *key_overrides[] = {
	&alt_tab_morph,
    &colon_morph,
};

// combos
const uint16_t PROGMEM combo_enter[] = {KC_N, KC_E, KC_I, COMBO_END};
// This globally defines all combos to be used
combo_t key_combos[] = {
    COMBO(combo_enter, KC_ENTER),
};

#ifdef OTHER_KEYMAP_C
#    include OTHER_KEYMAP_C
#endif // OTHER_KEYMAP_C


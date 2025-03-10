#include <stdint.h>
#include "keycodes.h"
#include QMK_KEYBOARD_H
#if __has_include("keymap.h")
#    include "keymap.h"
#endif

enum layer_names {
    _DEFAULT,
    _NUM,
    _FN,
    _MOUSE,
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
    ),
    [_MOUSE] = LAYOUT_split_3x5_2(
        KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS,            MS_WHLU, MS_WHLL, MS_UP, MS_WHLR, TO(_DEFAULT),
        KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS,            MS_WHLD, MS_LEFT, MS_DOWN, MS_RGHT, TO(_DEFAULT),
        KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS,            MS_BTN6, MS_BTN4, MS_BTN3, MS_BTN5, MS_BTN7,
        TO(_DEFAULT), KC_TRNS,                                  MS_BTN1, MS_BTN2
    ),
};

// hold-tap config
bool HT_CASE_BOOL(uint16_t thekeycode, bool thumb, bool letters) {
    switch (thekeycode) {
        case LCTL_T(KC_ESC):
        case LSFT_T(KC_SPC):
        case MEH_T(KC_BSPC):
        case LT(_NUM, QK_REP):
            return thumb;
        default:
            return letters;
    };
};
uint16_t HT_CASE_INT(uint16_t thekeycode, uint16_t thumb, uint16_t letters) {
    switch (thekeycode) {
        case LCTL_T(KC_ESC):
        case LSFT_T(KC_SPC):
        case MEH_T(KC_BSPC):
        case LT(_NUM, QK_REP):
            return thumb;
        default:
            return letters;
    };
};
bool get_hold_on_other_key_press(uint16_t keycode, keyrecord_t *record) {
    return HT_CASE_BOOL(keycode, true, false);
};
bool get_permissive_hold(uint16_t keycode, keyrecord_t *record) {
    return HT_CASE_BOOL(keycode, true, false);
};
uint16_t get_tapping_term(uint16_t keycode, keyrecord_t *record) {
    return HT_CASE_INT(keycode, 200, 280);
};
uint16_t get_quick_tap_term(uint16_t keycode, keyrecord_t *record) {
    return HT_CASE_INT(keycode, 200, 175);
};
#include <require-prior-idle-ms.c>
#define REQUIRE_PRIOR_IDLE_MS 150
const char chordal_hold_layout[MATRIX_ROWS][MATRIX_COLS] PROGMEM =
    LAYOUT(
        'L', 'L', 'L', 'L', 'L',  'R', 'R', 'R', 'R', 'R',
        'L', 'L', 'L', 'L', 'L',  'R', 'R', 'R', 'R', 'R',
        'L', 'L', 'L', 'L', 'L',  'R', 'R', 'R', 'R', 'R',
                       '*', '*',  '*', '*'
    );


// key overrides (mod morphs)
const key_override_t alt_tab_morph = ko_make_with_layers(MOD_BIT(KC_RALT), KC_A, KC_TAB, 1 << _DEFAULT);
const key_override_t alt_tab_shift_morph = ko_make_with_layers(MOD_BIT(KC_RALT) | MOD_BIT(KC_LSFT), KC_A, KC_TAB, 1 << _DEFAULT);
const key_override_t colon_morph = ko_make_basic(MOD_MASK_SHIFT, KC_COLON, KC_SCLN);
// This globally defines all key overrides to be used
const key_override_t *key_overrides[] = {
	&alt_tab_morph,
	&alt_tab_shift_morph,
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


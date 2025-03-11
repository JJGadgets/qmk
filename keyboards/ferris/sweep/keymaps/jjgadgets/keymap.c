#include <stdint.h>
#include "action.h"
#include "keycodes.h"
#include "modifiers.h"
#include "quantum.h"
#include "quantum_keycodes.h"
#include QMK_KEYBOARD_H
#if __has_include("keymap.h")
#    include "keymap.h"
#endif

enum layer_names {
    _DEFAULT,
    _NUM,
    _FN,
    /*_MOUSE,*/
};

const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {
    [_DEFAULT] = LAYOUT_split_3x5_2(
        KC_Q, KC_W, KC_F, KC_P, KC_G,                           KC_J, KC_L, KC_U, KC_Y, KC_COLON,
        KC_A, KC_R, KC_S, KC_T, KC_D,                           KC_H, KC_N, KC_E, KC_I, KC_O,
        LT(_FN, KC_Z), KC_X, RALT_T(KC_C), RGUI_T(KC_V), KC_B,  KC_K, LGUI_T(KC_M), LALT_T(KC_COMM), RCTL_T(KC_DOT), LT(_MOUSE, KC_SLSH),
        LCTL_T(KC_ESC), LSFT_T(KC_SPC),                         MEH_T(KC_BSPC), LT(_NUM, QK_REP)
        /*LCTL_T(KC_SPC), LSFT_T(OSM(MOD_LSFT)),                  MEH_T(KC_BSPC), LT(_NUM, QK_REP)*/
        /*LCTL_T(QK_GESC), LSFT_T(OSM(MOD_LSFT)),                         MEH_T(KC_SPC), LT(_NUM, KC_BSPC)*/ // one day I'll get used to this
    ),
    [_NUM] = LAYOUT_split_3x5_2(
        KC_TILDE, KC_1, KC_2, KC_3, KC_COMM,                    KC_BSLS, LT(_NUM, KC_HOME), KC_UP, LT(_NUM, KC_END), KC_DEL,
        QK_GESC, KC_4, KC_5, KC_6, KC_DOT,                      KC_TAB, KC_LEFT, KC_DOWN, KC_RIGHT, KC_QUOTE,
        KC_ENTER, KC_7, KC_8, KC_9, KC_0,                       KC_LBRC, KC_RBRC, KC_MINUS, KC_EQUAL, KC_PSCR,
        LCTL_T(TG(_NUM)), LSFT_T(KC_SPC),                       MEH_T(KC_BSPC), KC_TRNS
    ),
    [_FN] = LAYOUT_split_3x5_2(
        KC_LALT, KC_F1, KC_F2, KC_F3, KC_F10,                   KC_NO, KC_NO, KC_NO, KC_NO, LCA(KC_DEL),
        KC_LGUI, KC_F4, KC_F5, KC_F6, KC_F11,                   KC_NO, KC_NO, KC_NO, KC_NO, KC_NO,
        KC_TRNS, KC_F7, KC_F8, KC_F9, KC_F12,                   KC_NO, KC_NO, KC_NO, KC_NO, KC_NO,
        TO(_DEFAULT), KC_NO,                                    KC_NO, TO(_FN)
    ),
    /*[_MOUSE] = LAYOUT_split_3x5_2(*/
    /*    KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS,            MS_WHLU, MS_WHLL, MS_UP, MS_WHLR, TO(_DEFAULT),*/
    /*    KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS,            MS_WHLD, MS_LEFT, MS_DOWN, MS_RGHT, TO(_DEFAULT),*/
    /*    KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS,            MS_BTN6, MS_BTN4, MS_BTN3, MS_BTN5, MS_BTN7,*/
    /*    TO(_DEFAULT), KC_TRNS,                                  MS_BTN1, MS_BTN2*/
    /*),*/
};

// custom hold-tap bindings
bool jj_tap_hold_tap_override(keyrecord_t *therecord, uint16_t tapkey) {
    if (therecord->tap.count && therecord->event.pressed) {
        tap_code16(tapkey);
        return false;
    } else {
        return true;
    }
};
bool jj_tap_hold_hold_override(keyrecord_t *therecord, uint16_t tapkey) {
/*#define tap_hold_tap_override(therecord, tapkey) ( \*/
    if (!therecord->tap.count && therecord->event.pressed) {
        tap_code16(tapkey);
        return false;
    } else {
        return true;
    }
};
bool process_record_user(uint16_t keycode, keyrecord_t *record) {
    switch (keycode) {
        case LT(_NUM, QK_REP): return jj_tap_hold_tap_override(record, QK_REP); break;
        case LCTL_T(TG(_NUM)): return jj_tap_hold_tap_override(record, TG(_NUM)); break;
        case LT(_NUM, KC_HOME): return jj_tap_hold_hold_override(record, KC_PGUP); break;
        case LT(_NUM, KC_END): return jj_tap_hold_hold_override(record, KC_PGDN); break;
    }
    return true;
};

// combos
const uint16_t PROGMEM combo_enter[] = {KC_N, KC_E, KC_I, COMBO_END};
const uint16_t PROGMEM combo_mouse[] = {KC_L, KC_U, KC_Y, COMBO_END};
const uint16_t PROGMEM combo_caps[] = {KC_SPC, KC_BSPC, COMBO_END};
// This globally defines all combos to be used
combo_t key_combos[] = {
    COMBO(combo_enter, KC_ENTER),
    COMBO(combo_mouse, TG(_MOUSE)),
    COMBO(combo_caps, QK_CAPS_WORD_TOGGLE),
};

// key overrides (mod morphs)
const key_override_t alt_tab_morph = ko_make_with_layers(MOD_BIT(KC_RALT), KC_A, RALT_T(KC_TAB), 1 << _DEFAULT);
const key_override_t alt_tab_shift_morph = ko_make_with_layers(MOD_BIT(KC_RALT) | MOD_BIT(KC_LSFT), KC_A, RALT_T(KC_TAB), 1 << _DEFAULT);
const key_override_t colon_morph = ko_make_basic(MOD_MASK_SHIFT, KC_COLON, KC_SCLN);
const key_override_t tilde_morph = ko_make_basic(MOD_MASK_SHIFT, KC_TILDE, KC_GRV);
// This globally defines all key overrides to be used
const key_override_t *key_overrides[] = {
	&alt_tab_morph,
	&alt_tab_shift_morph,
    &colon_morph,
    &tilde_morph,
};

// hold-tap config
bool HT_THUMBS_IF(uint16_t thekeycode) {
    switch (thekeycode) {
        case LCTL_T(KC_ESC):
        case LSFT_T(KC_SPC):
        case MEH_T(KC_BSPC):
        case LT(_NUM, QK_REP):
        case LCTL_T(TG(_NUM)):
            return true;
        default:
            return false;
    };
};
bool get_hold_on_other_key_press(uint16_t keycode, keyrecord_t *record) {
    if (HT_THUMBS_IF(keycode)) {return true;} else {return false;};
};
bool get_permissive_hold(uint16_t keycode, keyrecord_t *record) {
    if (HT_THUMBS_IF(keycode)) {return false;} else {return true;};
};
uint16_t get_tapping_term(uint16_t keycode, keyrecord_t *record) {
    if (HT_THUMBS_IF(keycode)) {return 200;} else {return 280;};
};
uint16_t get_quick_tap_term(uint16_t keycode, keyrecord_t *record) {
    if (keycode == LSFT_T(KC_SPC)) {return 0;} // disable auto repeat for shift space
    else if (HT_THUMBS_IF(keycode)) {return 200;} else {return 175;};
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

#ifdef OTHER_KEYMAP_C
#    include OTHER_KEYMAP_C
#endif // OTHER_KEYMAP_C

// space savings
#ifndef MAGIC_ENABLE
uint16_t keycode_config(uint16_t keycode) {
    return keycode;
}
#endif
#ifndef MAGIC_ENABLE
uint8_t mod_config(uint8_t mod) {
    return mod;
}
#endif

void keyboard_post_init_user(void) {
  debug_enable=true;
  debug_matrix=true;
  debug_keyboard=true;
  debug_mouse=true;
}

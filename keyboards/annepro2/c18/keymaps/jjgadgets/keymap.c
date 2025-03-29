#include <stdint.h>
/*#include "keycodes.h"*/
/*#include "layer_lock.h"*/
/*#include "matrix.h"*/
/*#include "process_dynamic_macro.h"*/
/*#include "quantum.h"*/
/*#include "quantum_keycodes.h"*/
/*#include "repeat_key.h"*/
#include "socd.h"
#include QMK_KEYBOARD_H

enum anne_pro_layers {
    _BASE,
    _FN1,
    _FN2,
};

#define LT_NUM_REP LT(_BASE, QK_REPEAT_KEY)

const uint16_t keymaps[][MATRIX_ROWS][MATRIX_COLS] = {
    [_BASE] = LAYOUT_60_ansi(
        LT(_BASE, KC_GRV), KC_1, KC_2, KC_3, KC_4, KC_5, KC_6, KC_7, KC_8, KC_9, KC_0, KC_MINS, KC_EQL, KC_BSPC,
        KC_TAB, SOCD_Q, SOCD_W, SOCD_F, KC_P, KC_G, KC_J, KC_L, KC_U, KC_Y, KC_SCLN, KC_LBRC, KC_RBRC, KC_BSLS,
        LT(_FN1, KC_ESC), SOCD_A, SOCD_R, SOCD_S, KC_T, KC_D, KC_H, KC_N, KC_E, KC_I, KC_O, KC_QUOT, LT(_FN2, KC_ENT),
        KC_LSFT, KC_Z, KC_X, KC_C, KC_V, KC_B, KC_K, KC_M, KC_COMM, KC_DOT, KC_SLSH, KC_UP,
        KC_LCTL, KC_LALT, KC_LGUI, KC_SPC, KC_RALT, KC_LEFT, KC_DOWN, KC_RGHT
    ),
    [_FN1] = LAYOUT_60_ansi(
        KC_CAPS, KC_F1, KC_F2, KC_F3, KC_F4, KC_F5, KC_F6, KC_F7, KC_F8, KC_F9, KC_F10, KC_F11, KC_F12, KC_DEL,
        KC_TRNS, KC_MPRV, KC_MPLY, KC_MNXT, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_PSCR, KC_HOME, KC_END, KC_TRNS,
        KC_TRNS, KC_LEFT, KC_DOWN, KC_RGHT, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_PGUP, KC_PGDN, KC_TRNS,
        KC_TRNS, KC_VOLU, KC_VOLD, KC_MUTE, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_INS, KC_DEL, KC_TRNS,
        LCTL_T(QK_LLCK), KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, MO(_FN2), KC_TRNS
    ),
    [_FN2] = LAYOUT_60_ansi(
        KC_TRNS, KC_AP2_BT1, KC_AP2_BT2, KC_AP2_BT3, KC_AP2_BT4, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_AP_RGB_MOD, KC_AP_RGB_TOG, KC_AP_RGB_VAD, KC_AP_RGB_VAI, KC_TRNS,
        KC_TRNS, KC_TRNS, KC_UP, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_PSCR, KC_HOME, KC_END, KC_TRNS,
        KC_TRNS, KC_LEFT, KC_DOWN, KC_RGHT, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_PGUP, KC_PGDN, KC_TRNS,
        KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_INS, KC_DEL, KC_TRNS,
        LCTL_T(QK_LLCK), KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS
     ),
};

// custom hold-tap bindings
bool process_record_user(uint16_t keycode, keyrecord_t *record) {
    switch (keycode) {
        case SOCD_W: jj_socd(record, KC_W, KC_R, &socd_w_down, socd_r_down); return false; break;
        case SOCD_R: jj_socd(record, KC_R, KC_W, &socd_r_down, socd_w_down); return false; break;
        case SOCD_A: jj_socd(record, KC_A, KC_S, &socd_a_down, socd_s_down); return false; break;
        case SOCD_S: jj_socd(record, KC_S, KC_A, &socd_s_down, socd_a_down); return false; break;
        case SOCD_Q: jj_socd(record, KC_Q, KC_F, &socd_q_down, socd_f_down); return false; break;
        case SOCD_F: jj_socd(record, KC_F, KC_Q, &socd_f_down, socd_q_down); return false; break;
        default: return true;
    }
};

// space savings
#ifndef MAGIC_ENABLE
uint16_t keycode_config(uint16_t keycode) {
    return keycode;
}
uint8_t mod_config(uint8_t mod) {
    return mod;
}
#endif

#ifdef CONSOLE_ENABLE
void keyboard_post_init_user(void) {
  debug_enable=true;
  debug_matrix=true;
  debug_keyboard=true;
  debug_mouse=true;
}
#endif

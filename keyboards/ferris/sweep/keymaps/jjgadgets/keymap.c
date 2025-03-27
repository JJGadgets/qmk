#include <stdint.h>
#include "action.h"
#include "action_util.h"
#include "keymap_us.h"
#include "keycodes.h"
#include "modifiers.h"
#include "process_combo.h"
#include "process_dynamic_macro.h"
#include "process_key_override.h"
#include "quantum.h"
#include "quantum_keycodes.h"
#include "repeat_key.h"
#include "socd.h"
// most includes above are auto-inserted by clangd LSP in Neovim, the below are the defaults from a fresh QMK json2c output
#include QMK_KEYBOARD_H
#if __has_include("keymap.h")
#    include "keymap.h"
#endif

enum layer_names {
    _DEFAULT,
    _NUM,
    _FN,
    _MOUSE,
    _GAME,
};

#define LT_NUM_REP LT(_NUM, QK_REPEAT_KEY)

const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {
    [_DEFAULT] = LAYOUT_split_3x5_2(
        KC_Q, KC_W, KC_F, KC_P, KC_G,                           KC_J, KC_L, KC_U, KC_Y, KC_COLON,
        KC_A, KC_R, KC_S, KC_T, KC_D,                           KC_H, KC_N, KC_E, KC_I, KC_O,
        LT(_FN, KC_Z), KC_X, RALT_T(KC_C), RGUI_T(KC_V), KC_B,  KC_K, LGUI_T(KC_M), LALT_T(KC_COMM), RCTL_T(KC_DOT), LT(_MOUSE, KC_SLASH),
        LCTL_T(KC_ESC), LSFT_T(KC_SPC),                         MEH_T(KC_BSPC), LT_NUM_REP
        /*LCTL_T(KC_SPC), LSFT_T(OSM(MOD_LSFT)),                  MEH_T(KC_BSPC), LT(_NUM, QK_REP)*/
        /*LCTL_T(QK_GESC), LSFT_T(OSM(MOD_LSFT)),                         MEH_T(KC_SPC), LT(_NUM, KC_BSPC)*/ // one day I'll get used to this
    ),
    [_NUM] = LAYOUT_split_3x5_2(
        KC_TILDE, KC_4, KC_5, KC_6, KC_COMM,                    KC_BSLS, LT(_NUM, KC_HOME), KC_UP, LT(_NUM, KC_END), KC_DEL,
        KC_0, KC_1, KC_2, KC_3, KC_DOT,                         KC_TAB, KC_LEFT, KC_DOWN, KC_RIGHT, KC_QUOTE,
        KC_ENTER, KC_7, KC_8, KC_9, KC_SLASH,                   KC_LBRC, KC_RBRC, KC_MINUS, KC_EQUAL, KC_PSCR,
        LCTL_T(QK_LLCK), LSFT_T(KC_SPC),                        MEH_T(KC_BSPC), KC_TRNS
    ),
    [_FN] = LAYOUT_split_3x5_2(
        KC_LALT, KC_F1, KC_F2, KC_F3, KC_F10,                   KC_NO, KC_NO, KC_NO, TG(_GAME), LCA(KC_DEL),
        KC_LGUI, KC_F4, KC_F5, KC_F6, KC_F11,                   KC_NO, DM_REC1, DM_REC2, KC_NO, KC_NO,
        KC_TRNS, KC_F7, KC_F8, KC_F9, KC_F12,                   KC_NO, KC_NO, KC_NO, KC_NO, DF(_DEFAULT),
        LCTL_T(QK_LLCK), KC_TRNS,                               DM_PLY2, TG(_GAME)
    ),
    [_MOUSE] = LAYOUT_split_3x5_2(
        KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS,            MS_WHLU, MS_WHLL, MS_UP, MS_WHLR, TG(_MOUSE),
        KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS,            MS_WHLD, MS_LEFT, MS_DOWN, MS_RGHT, TG(_MOUSE),
        KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS,            MS_BTN6, MS_BTN4, MS_BTN3, MS_BTN5, MS_BTN7,
        TG(_MOUSE), KC_TRNS,                                    MS_BTN1, MS_BTN2
    ),
    [_GAME] = LAYOUT_split_3x5_2(
        KC_TAB, SOCD_Q, SOCD_W, SOCD_F, KC_P,                   KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS,
        KC_G, SOCD_A, SOCD_R, SOCD_S, KC_T,                     KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS,
        KC_Z, KC_X, KC_C, KC_V, KC_B,                           KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS,
        KC_LSFT, KC_SPC,                                        KC_D, TG(_GAME)
    ),
};

// dynamic macros
bool jj_current_dynamic_macro_recording = false;
uint8_t jj_current_dynamic_macro_length = 0;
bool dynamic_macro_record_start_user(int8_t direction) {
    if (direction == 1) {
        jj_current_dynamic_macro_recording = true;
        jj_current_dynamic_macro_length = 0;
    }
    return true;
}
bool dynamic_macro_record_key_user(int8_t direction, keyrecord_t *record) {
    if (direction == 1) {
        jj_current_dynamic_macro_recording = true;
        jj_current_dynamic_macro_length += 1;
    }
    return true;
}
bool dynamic_macro_record_end_user(int8_t direction) {
    if (direction == 1) {
        jj_current_dynamic_macro_recording = false;
    }
    return true;
}

// custom hold-tap bindings
bool jj_tap_hold_override(keyrecord_t *therecord, bool tap_override, uint16_t tapkey, bool hold_override, uint16_t holdkey) {
    if (therecord->tap.count && therecord->event.pressed && tap_override) {
        tap_code16(tapkey);
        return false;
    } else if (!therecord->tap.count && therecord->event.pressed && hold_override) {
        register_code16(holdkey);
        return false;
    } else if (!therecord->tap.count && !therecord->event.pressed && hold_override) {
        unregister_code16(holdkey);
        return false;
    } else {
        return true;
    }
};
bool process_record_user(uint16_t keycode, keyrecord_t *record) {
    uint8_t mod_state;
    switch (keycode) {
        case LT(_NUM, KC_HOME): return jj_tap_hold_override(record, false, KC_NO, true, KC_PGUP); break;
        case LT(_NUM, KC_END): return jj_tap_hold_override(record, false, KC_NO, true, KC_PGDN); break;
        case LCTL_T(QK_LLCK):
            if (record->tap.count && record->event.pressed) {
                layer_lock_invert(get_highest_layer(layer_state));
                return false; break;
            }
        case LT_NUM_REP:
            mod_state = get_mods();
            if (record->tap.count && record->event.pressed) {
                if (mod_state & MOD_BIT(KC_LCTL)) {
                    del_mods(MOD_BIT(KC_LCTL));
                    repeat_key_invoke(&record->event);
                    set_mods(mod_state);
                } else if (jj_current_dynamic_macro_recording == true) {
                    dynamic_macro_stop_recording();
                } else if (jj_current_dynamic_macro_length > 1) {
                    keyrecord_t newrecord;
                    newrecord.event.pressed = false; // why on release?
                    process_dynamic_macro(QK_DYNAMIC_MACRO_PLAY_1, record);
                } else if (get_alt_repeat_key_keycode()) { // if no alt repeat, normal repeat key instead
                    alt_repeat_key_invoke(&record->event);
                    clear_keyboard(); // will keep spam tapping the alt-repeated-keycode otherwise
                } else {
                    repeat_key_invoke(&record->event);
                }
                return false; break;
            }
        case SOCD_W: jj_socd(record, KC_W, KC_R, &socd_w_down, socd_r_down); return false; break;
        case SOCD_R: jj_socd(record, KC_R, KC_W, &socd_r_down, socd_w_down); return false; break;
        case SOCD_A: jj_socd(record, KC_A, KC_S, &socd_a_down, socd_s_down); return false; break;
        case SOCD_S: jj_socd(record, KC_S, KC_A, &socd_s_down, socd_a_down); return false; break;
        case SOCD_Q: jj_socd(record, KC_Q, KC_F, &socd_q_down, socd_f_down); return false; break;
        case SOCD_F: jj_socd(record, KC_F, KC_Q, &socd_f_down, socd_q_down); return false; break;
        default: return true;
    }
};

// repeat key
bool remember_last_key_user(uint16_t keycode, keyrecord_t* record, uint8_t* remembered_mods) {
    switch (keycode) {
        case LT_NUM_REP: return false;
        default: return true;
    }
}
// alt repeat key
uint16_t get_alt_repeat_key_keycode_user(uint16_t keycode, uint8_t mods) {
    bool shifted = (mods & MOD_MASK_SHIFT);
    bool ctrled = (mods & MOD_MASK_CTRL);
    switch (keycode) {
        // shortcuts
        case KC_TAB: if (shifted) { return KC_TAB; } else { return LSFT(KC_TAB); }
        case KC_Z: if (ctrled) { return LCTL(KC_Y); }
        case KC_Y: if (ctrled) { return LCTL(KC_Z); }
        // Colemak non DH SFBs
        case KC_E: return KC_QUESTION;
        case KC_K: return KC_N;
        case KC_N: return KC_K;
        case KC_U: return KC_E;
        case KC_SLASH: if (shifted) { return KC_DOUBLE_QUOTE; }
        case KC_S: return KC_C;
        case LT_NUM_REP: return KC_NO;
        default: return KC_TRNS;
    }
}

// combos
const uint16_t PROGMEM combo_enter[] = {KC_N, KC_E, KC_I, COMBO_END};
const uint16_t PROGMEM combo_mouse_default[] = {KC_L, KC_U, KC_Y, COMBO_END};
const uint16_t PROGMEM combo_mouse_layered[] = {MS_WHLL, MS_UP, MS_WHLR, COMBO_END};
const uint16_t PROGMEM combo_caps[] = {KC_SPC, KC_BSPC, COMBO_END};
const uint16_t PROGMEM combo_caps2[] = {LSFT_T(KC_SPC), MEH_T(KC_BSPC), COMBO_END};
const uint16_t PROGMEM combo_tab[] = {KC_X, KC_C, COMBO_END};
const uint16_t PROGMEM combo_one_shot_shift_l[] = {KC_W, KC_F, COMBO_END};
const uint16_t PROGMEM combo_one_shot_shift_r[] = {KC_U, KC_Y, COMBO_END};
const uint16_t PROGMEM combo_record_dynamic_macro_1_default[] = {LT_NUM_REP, KC_Y, KC_COLON, COMBO_END};
const uint16_t PROGMEM combo_record_dynamic_macro_1_num[] = {LT_NUM_REP, LT(_NUM, KC_END), KC_DEL, COMBO_END};
// I broke the switch on the Colemak k key lol, temporary workaround
const uint16_t PROGMEM combo_tmp_k_default[] = {LGUI_T(KC_M), LALT_T(KC_COMM), COMBO_END};
const uint16_t PROGMEM combo_tmp_k_num[] = {KC_RBRC, KC_MINUS, COMBO_END};
// This globally defines all combos to be used
combo_t key_combos[] = {
    COMBO(combo_enter, KC_ENTER),
    COMBO(combo_mouse_default, TG(_MOUSE)),
    COMBO(combo_mouse_layered, TG(_MOUSE)),
    COMBO(combo_caps, QK_CAPS_WORD_TOGGLE),
    COMBO(combo_caps2, QK_CAPS_WORD_TOGGLE),
    COMBO(combo_tab, KC_TAB),
    COMBO(combo_one_shot_shift_l, OSM(MOD_LSFT)),
    COMBO(combo_one_shot_shift_r, OSM(MOD_LSFT)),
    COMBO(combo_record_dynamic_macro_1_default, DM_REC1),
    // I broke the switch on the Colemak k key lol, temporary workaround
    COMBO(combo_tmp_k_default, KC_K),
    COMBO(combo_tmp_k_num, KC_LBRC),
};

// key overrides (mod morphs)
const key_override_t alt_tab_morph = ko_make_with_layers(MOD_BIT(KC_RALT), KC_A, RALT(KC_TAB), 1 << _DEFAULT);
const key_override_t alt_tab_shift_morph = ko_make_with_layers(MOD_BIT(KC_RALT) | MOD_BIT(KC_LSFT), KC_A, LSFT(RALT(KC_TAB)), 1 << _DEFAULT);
const key_override_t colon_morph = ko_make_basic(MOD_MASK_SHIFT, KC_COLON, KC_SCLN);
const key_override_t tilde_morph = ko_make_basic(MOD_MASK_SHIFT, KC_TILDE, KC_GRV);
const key_override_t right_bracket_morph = ko_make_with_layers(MOD_MASK_SHIFT, KC_SLASH, KC_RIGHT_PAREN, 1 << _NUM);
// This globally defines all key overrides to be used
const key_override_t *key_overrides[] = {
	&alt_tab_morph,
	&alt_tab_shift_morph,
    &colon_morph,
    &tilde_morph,
    &right_bracket_morph,
};

// hold-tap config
bool HT_THUMBS_IF(uint16_t thekeycode) {
    switch (thekeycode) {
        case LCTL_T(KC_ESC):
        case LSFT_T(KC_SPC):
        case MEH_T(KC_BSPC):
        case LT_NUM_REP:
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

/*// gaming*/
/*socd_cleaner_t socd_opposing_pairs[] = {*/
/*  {{KC_W, KC_S}, SOCD_CLEANER_LAST},*/
/*  {{KC_A, KC_D}, SOCD_CLEANER_LAST},*/
/*};*/
/*layer_state_t layer_state_set_user(layer_state_t state) {*/
/*  socd_cleaner_enabled = IS_LAYER_ON_STATE(state, _GAME);*/
/*  return state;*/
/*}*/

#ifdef OTHER_KEYMAP_C
#    include OTHER_KEYMAP_C
#endif // OTHER_KEYMAP_C

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

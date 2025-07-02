#include <stdint.h>
#include "action.h"
#include "action_util.h"
#include "send_string_keycodes.h"
#ifdef CONSOLE_ENABLE
#include "debug.h"
#include "print.h"
#endif
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

enum layer_names {
    _DEFAULT,
    /*_NORDRASSIL,*/
    _NUM,
    _FN,
    #ifdef MOUSEKEY_ENABLE
    _MOUSE,
    #endif
    _GAME,
};

#ifdef SEND_STRING_ENABLE
enum macro_keycodes {
    // alt repeat key SFB/shortcut macros
    M_THE = SAFE_RANGE,
    M_ENT,
    M_NG,
    M_ND,
    M_ECAUSE,
    M_OULD,
    M_BUT,
    M_OR,
    M_OU,
    M_ICH,
    // Excel macros
    JJ_EXCEL_COPY_PASTE_SHEET,
};
#define JJ_ECPS JJ_EXCEL_COPY_PASTE_SHEET
#endif

#define JJ_THUMB_L_INNER LCTL_T(KC_ESC)
#define JJ_THUMB_L_INNER_36_TMP LCTL_T(OSM(MOD_LCTL))
#define JJ_THUMB_L_OUTER LSFT_T(KC_SPC)
#define JJ_THUMB_R_OUTER MEH_T(KC_BSPC)
#define JJ_MAGIC LT(_NUM, QK_ALT_REPEAT_KEY)

const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {
    [_DEFAULT] = LAYOUT(
        KC_Q, KC_W, KC_F, KC_P, KC_G,                           KC_J, KC_L, KC_U, KC_Y, KC_COLON,
        KC_A, KC_R, KC_S, KC_T, KC_D,                           KC_H, KC_N, KC_E, KC_I, KC_O,
        LT(_FN, KC_Z), KC_X, RALT_T(KC_C), RGUI_T(KC_V), KC_B,  KC_K, LGUI_T(KC_M), LALT_T(KC_COMM), RCTL_T(KC_DOT), KC_SLASH,
#ifdef JJ_SPLIT_36
        /*LCTL_T(KC_ESC), LSFT_T(KC_SPC), KC_NO,                  KC_NO, MEH_T(KC_BSPC), JJ_MAGIC*/
        JJ_THUMB_L_INNER_36_TMP, JJ_THUMB_L_OUTER, KC_ESC,      QK_REP, JJ_THUMB_R_OUTER, JJ_MAGIC // TODO: tmp: control/escape key is wonky, maybe needs unsoldering?
#else
        JJ_THUMB_L_INNER, JJ_THUMB_L_OUTER,                     JJ_THUMB_R_OUTER, JJ_MAGIC
#endif
        /*LCTL_T(KC_SPC), LSFT_T(OSM(MOD_LSFT)),                  MEH_T(KC_BSPC), LT(_NUM, QK_REP)*/
        /*LCTL_T(QK_GESC), LSFT_T(OSM(MOD_LSFT)),                         MEH_T(KC_SPC), LT(_NUM, KC_BSPC)*/ // one day I'll get used to this
    ),
/*    [_NORDRASSIL] = LAYOUT(*/
/*        KC_Q, KC_W, KC_F, KC_P, KC_G,                           KC_J, KC_L, KC_U, KC_Y, KC_COLON,*/
/*        KC_A, KC_R, KC_S, KC_T, KC_D,                           KC_H, KC_N, KC_E, KC_I, KC_O,*/
/*        LT(_FN, KC_Z), KC_X, RALT_T(KC_C), RGUI_T(KC_V), KC_B,  KC_K, LGUI_T(KC_M), LALT_T(KC_COMM), RCTL_T(KC_DOT), LT(_MOUSE, KC_SLASH),*/
/*#ifdef JJ_SPLIT_36*/
/*        JJ_THUMB_L_INNER_36_TMP, JJ_THUMB_L_OUTER, KC_ESC,      QK_REP, JJ_THUMB_R_OUTER, JJ_MAGIC // TODO: tmp: control/escape key is wonky, maybe needs unsoldering?*/
/*#else*/
/*        JJ_THUMB_L_INNER, JJ_THUMB_L_OUTER,                     JJ_THUMB_R_OUTER, JJ_MAGIC*/
/*#endif*/
/*    ),*/
    [_NUM] = LAYOUT(
        KC_TILDE, KC_4, KC_5, KC_6, KC_COMM,                    KC_BSLS, LT(_NUM, KC_HOME), KC_UP, LT(_NUM, KC_END), KC_DEL,
        KC_0, KC_1, KC_2, KC_3, KC_DOT,                         KC_TAB, KC_LEFT, KC_DOWN, KC_RIGHT, KC_QUOTE,
        KC_ENTER, KC_7, KC_8, KC_9, KC_SLASH,                   KC_LBRC, KC_RBRC, KC_MINUS, KC_EQUAL, KC_PSCR,
#ifdef JJ_SPLIT_36
        LCTL_T(QK_LLCK), LSFT_T(KC_SPC), KC_NO,                 KC_NO, MEH_T(KC_BSPC), KC_TRNS
#else
        LCTL_T(QK_LLCK), LSFT_T(KC_SPC),                        MEH_T(KC_BSPC), KC_TRNS
#endif
    ),
    [_FN] = LAYOUT(
        KC_LALT, KC_F1, KC_F2, KC_F3, KC_F10,                   KC_NO, KC_NO, KC_NO, TG(_GAME), LCA(KC_DEL),
        KC_LGUI, KC_F4, KC_F5, KC_F6, KC_F11,
                                                                #ifdef DYNAMIC_MACRO_ENABLE
                                                                DM_PLY1, DM_REC1, DM_RSTP, DM_REC2, DM_PLY2,
                                                                #else
                                                                KC_NO, KC_NO, KC_NO, KC_NO, KC_NO,
                                                                #endif
        KC_TRNS, KC_F7, KC_F8, KC_F9, KC_F12,
                                                                #ifdef SEND_STRING_ENABLE
                                                                KC_NO, JJ_ECPS, KC_NO, KC_NO, DF(_DEFAULT),
                                                                #else
                                                                KC_NO, KC_NO, KC_NO, KC_NO, DF(_DEFAULT),
                                                                #endif
#ifdef JJ_SPLIT_36
        LCTL_T(QK_LLCK), KC_TRNS, KC_NO,                        KC_NO, DM_PLY2, TG(_GAME)
#else
        LCTL_T(QK_LLCK), KC_TRNS,                               DM_PLY2, TG(_GAME)
#endif
    ),
    #ifdef MOUSEKEY_ENABLE
    [_MOUSE] = LAYOUT(
        KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS,            MS_WHLU, MS_WHLL, MS_UP, MS_WHLR, KC_BSPC,
        KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS,            MS_WHLD, MS_LEFT, MS_DOWN, MS_RGHT, TG(_MOUSE),
        KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS,            MS_BTN6, MS_BTN4, MS_BTN3, MS_BTN5, MS_BTN7,
#ifdef JJ_SPLIT_36
        TG(_MOUSE), KC_TRNS, KC_NO,                             KC_NO, MS_BTN1, MS_BTN2
#else
        TG(_MOUSE), KC_TRNS,                                    MS_BTN1, MS_BTN2
#endif
    ),
    #endif
    [_GAME] = LAYOUT(
        KC_TAB, SOCD_Q, SOCD_W, SOCD_F, KC_P,                   KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS,
        KC_G, SOCD_A, SOCD_R, SOCD_S, KC_T,                     KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS,
        KC_Z, KC_X, KC_C, KC_V, KC_B,                           KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS,
#ifdef JJ_SPLIT_36
        KC_LSFT, KC_SPC, KC_NO,                                 KC_NO, KC_D, TG(_GAME)
#else
        KC_LSFT, KC_SPC,                                        KC_D, TG(_GAME)
#endif
    ),
};

uint8_t mod_state;
// 2nd last key
/*keyrecord_t jj_2nd_last_record;*/
#ifdef DYNAMIC_MACRO_ENABLE
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
#endif

#ifdef REPEAT_KEY_ENABLE
// 2nd last key
/*bool pre_process_record_user(uint16_t keycode, keyrecord_t *record) {*/
/*    memcpy(&jj_2nd_last_record, record, sizeof(*record));*/
/*    jj_2nd_last_record.keycode = get_last_keycode();*/
/*    return true;*/
/*}*/
// repeat key
bool remember_last_key_user(uint16_t keycode, keyrecord_t* record, uint8_t* remembered_mods) {
    switch (keycode) {
        case JJ_MAGIC: return false;
        case QK_REPEAT_KEY: return false;
        case QK_ALT_REPEAT_KEY: return false;
        default: return true;
    }
}
// alt repeat key
uint16_t get_alt_repeat_key_keycode_user(uint16_t keycode, uint8_t mods) {
    bool shifted = (mods & MOD_MASK_SHIFT);
    bool ctrled = (mods & MOD_MASK_CTRL);
    switch (keycode) {
        // shortcuts
        case KC_TAB: if (shifted) { return KC_TAB; } else { return LSFT(KC_TAB); break; }
        case KC_Z: if (ctrled) { return LCTL(KC_Y); break; }
        case KC_Y: if (ctrled) { return LCTL(KC_Z); } else { return M_OU; } break;
        // Colemak non DH SFBs
        case KC_E: return KC_QUESTION;
        case KC_K: return KC_N;
        case KC_N: return KC_K;
        case KC_U: return KC_E;
        case KC_SLASH: if (shifted) { return KC_DOUBLE_QUOTE; }
        case KC_S: return KC_C;
        // common trigrams
        #ifdef SEND_STRING_ENABLE
        case JJ_THUMB_L_OUTER:
        case KC_SPC:
            return M_THE;
        case KC_M: return M_ENT;
        case KC_I: return M_NG;
        case KC_A: return M_ND;
        case KC_B: return M_ECAUSE;
        case KC_W: return M_OULD;
        case KC_COMMA: return M_BUT;
        case KC_F: return M_OR;
        /*case KC_Y: return M_OU;*/
        case KC_H: return M_ICH; // which
        #endif
        // disable
        case JJ_MAGIC: return KC_NO;
        case QK_REPEAT_KEY: return KC_NO;
        case QK_ALT_REPEAT_KEY: return KC_NO;
        default: return KC_TRNS;
    }
}
#endif

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
    #ifdef CONSOLE_ENABLE
    uprintf("KL: kc: 0x%04X, col: %2u, row: %2u, pressed: %u, time: %5u, int: %u, count: %u\n", keycode, record->event.key.col, record->event.key.row, record->event.pressed, record->event.time, record->tap.interrupted, record->tap.count);
    #endif
    switch (keycode) {
        case LT(_NUM, KC_HOME): return jj_tap_hold_override(record, false, KC_NO, true, KC_PGUP); break;
        case LT(_NUM, KC_END): return jj_tap_hold_override(record, false, KC_NO, true, KC_PGDN); break;
        #ifdef SOCD_ENABLE
        case SOCD_W: jj_socd(record, KC_W, KC_R, &socd_w_down, socd_r_down); return false; break;
        case SOCD_R: jj_socd(record, KC_R, KC_W, &socd_r_down, socd_w_down); return false; break;
        case SOCD_A: jj_socd(record, KC_A, KC_S, &socd_a_down, socd_s_down); return false; break;
        case SOCD_S: jj_socd(record, KC_S, KC_A, &socd_s_down, socd_a_down); return false; break;
        case SOCD_Q: jj_socd(record, KC_Q, KC_F, &socd_q_down, socd_f_down); return false; break;
        case SOCD_F: jj_socd(record, KC_F, KC_Q, &socd_f_down, socd_q_down); return false; break;
        #endif
        #ifdef SEND_STRING_ENABLE // this needs to be before alt repeat key or its layer hold won't work
        case M_THE: if (record->event.pressed) {SEND_STRING_DELAY("the ", 25); return false; break;}
        case M_ENT: if (record->event.pressed) {SEND_STRING_DELAY("ent", 25); return false; break;}
        case M_NG: if (record->event.pressed) {SEND_STRING_DELAY("ng", 25); return false; break;}
        case M_ND: if (record->event.pressed) {SEND_STRING_DELAY("nd ", 25); return false; break;}
        case M_ECAUSE: if (record->event.pressed) {SEND_STRING_DELAY("ecause ", 25); return false; break;}
        case M_OULD: if (record->event.pressed) {SEND_STRING_DELAY("ould ", 25); return false; break;}
        case M_BUT: if (record->event.pressed) {SEND_STRING_DELAY(" but ", 25); return false; break;}
        case M_OR: if (record->event.pressed) {SEND_STRING_DELAY("or ", 25); return false; break;}
        case M_OU: if (record->event.pressed) {SEND_STRING_DELAY("ou", 25); return false; break;}
        case M_ICH: if (record->event.pressed) {SEND_STRING_DELAY("ich ", 25); return false; break;}
        case JJ_EXCEL_COPY_PASTE_SHEET: if (record->event.pressed) {
            SEND_STRING_DELAY((
                SS_LCTL(SS_LSFT(SS_TAP(X_UP)))
                SS_LCTL(SS_LSFT(SS_TAP(X_LEFT)))
                SS_TAP(X_DOWN)

                SS_LCTL(SS_LSFT(SS_TAP(X_RIGHT)))
                SS_LCTL(SS_LSFT(SS_TAP(X_RIGHT)))
                SS_LCTL(SS_LSFT(SS_TAP(X_RIGHT)))
                SS_LCTL(SS_LSFT(SS_TAP(X_RIGHT)))
                SS_LCTL(SS_LSFT(SS_TAP(X_RIGHT)))
                SS_LCTL(SS_LSFT(SS_TAP(X_RIGHT)))
                SS_LCTL(SS_LSFT(SS_TAP(X_RIGHT)))
                SS_LCTL(SS_LSFT(SS_TAP(X_RIGHT)))
                SS_LCTL(SS_LSFT(SS_TAP(X_RIGHT)))
                SS_LCTL(SS_LSFT(SS_TAP(X_RIGHT)))

                SS_LCTL(SS_LSFT(SS_TAP(X_LEFT)))

                SS_LCTL(SS_LSFT(SS_TAP(X_DOWN)))
                SS_LCTL(SS_LSFT(SS_TAP(X_DOWN)))
                SS_LCTL(SS_LSFT(SS_TAP(X_DOWN)))
                SS_LCTL(SS_LSFT(SS_TAP(X_DOWN)))
                SS_LCTL(SS_LSFT(SS_TAP(X_DOWN)))
                SS_LCTL(SS_LSFT(SS_TAP(X_DOWN)))
                SS_LCTL(SS_LSFT(SS_TAP(X_DOWN)))
                SS_LCTL(SS_LSFT(SS_TAP(X_DOWN)))
                SS_LCTL(SS_LSFT(SS_TAP(X_DOWN)))
                SS_LCTL(SS_LSFT(SS_TAP(X_DOWN)))

                SS_LCTL(SS_LSFT(SS_TAP(X_UP)))
                SS_LCTL("c")
                SS_LALT(SS_TAP(X_TAB))
                SS_LCTL("v")
            ), 100); return false; break;};
        #endif
        #ifdef LAYER_LOCK_ENABLE
        case LCTL_T(QK_LLCK):
            if (record->tap.count && record->event.pressed) {
                layer_lock_invert(get_highest_layer(layer_state));
                return false; break;
            }
        #endif
        case JJ_MAGIC:
            mod_state = get_mods();
            if (record->tap.count && record->event.pressed) {
                #ifdef CONSOLE_ENABLE
                dprintf("\nmod state: %u\n", mod_state);
                dprintf("\ndynamic macro recording var: %s\n", jj_current_dynamic_macro_recording ? "true" : "false");
                dprintf("\ndynamic macro length var: %u\n", jj_current_dynamic_macro_length);
                #endif
                if (mod_state & MOD_BIT(KC_LCTL)) {
                    #ifdef CONSOLE_ENABLE
                    dprint("\nnormal repeat key condition (ctrl) reached\n");
                    #endif
                    #ifdef REPEAT_KEY_ENABLE
                    del_mods(MOD_BIT(KC_LCTL));
                    repeat_key_invoke(&record->event);
                    set_mods(mod_state);
                    #endif
                }
                #ifdef DYNAMIC_MACRO_ENABLE
                else if (mod_state & MOD_BIT(KC_LSFT)) {
                    #ifdef CONSOLE_ENABLE
                    dprint("\ndynamic macro clear condition reached\n");
                    #endif
                    record->event.pressed = false; // why on release?
                    process_dynamic_macro(QK_DYNAMIC_MACRO_PLAY_1, record);
                    record->event.pressed = true;
                    dynamic_macro_stop_recording();
                /*} else if (jj_current_dynamic_macro_recording == true) {*/
                /*    #ifdef CONSOLE_ENABLE*/
                /*    dprint("\ndynamic macro stop record condition reached\n");*/
                /*    #endif*/
                /*    dynamic_macro_stop_recording();*/
                } else if (jj_current_dynamic_macro_length > 1) {
                    #ifdef CONSOLE_ENABLE
                    dprint("\ndynamic macro stop record condition reached\n");
                    #endif
                    record->event.pressed = false; // why on release?
                    process_dynamic_macro(QK_DYNAMIC_MACRO_PLAY_1, record);
                }
                #endif
                #ifdef REPEAT_KEY_ENABLE
                #ifdef JJ_SPLIT_36
                else {
                #else
                else if (get_alt_repeat_key_keycode()) {
                #endif
                    #ifdef CONSOLE_ENABLE
                    dprint("\nalt repeat key condition reached\n");
                    #endif
                    alt_repeat_key_invoke(&record->event);
                    clear_keyboard(); // will keep spam tapping the alt-repeated-keycode otherwise
                }
                #ifndef JJ_SPLIT_36
                else {
                    #ifdef CONSOLE_ENABLE
                    dprint("\nnormal repeat key condition (fallback) reached\n");
                    #endif
                    repeat_key_invoke(&record->event);
                    clear_keyboard(); // will keep spam tapping the alt-repeated-keycode otherwise
                }
                #endif
                #endif
                return false; break;
            }
    }
    return true;
};

/*#if COMBO_ENABLE == yes*/
#if defined(COMBO_ENABLE)
// combos
const uint16_t PROGMEM combo_enter_default[] = {KC_N, KC_E, KC_I, COMBO_END};
const uint16_t PROGMEM combo_enter_mouse[] = {MS_LEFT, MS_DOWN, MS_RGHT, COMBO_END};
const uint16_t PROGMEM combo_mouse_default[] = {KC_L, KC_U, KC_Y, COMBO_END};
const uint16_t PROGMEM combo_mouse_layered[] = {MS_WHLL, MS_UP, MS_WHLR, COMBO_END};
const uint16_t PROGMEM combo_caps[] = {JJ_THUMB_L_OUTER, JJ_THUMB_R_OUTER, COMBO_END};
const uint16_t PROGMEM combo_tab[] = {KC_W, KC_F, KC_P, COMBO_END};
const uint16_t PROGMEM combo_one_shot_shift[] = {KC_R, KC_S, KC_T, COMBO_END};
const uint16_t PROGMEM combo_esc[] = {KC_X, RALT_T(KC_C), RGUI_T(KC_V), COMBO_END};
const uint16_t PROGMEM combo_backspace[] = {LGUI_T(KC_M), LALT_T(KC_COMM), RCTL_T(KC_DOT), COMBO_END};
const uint16_t PROGMEM combo_one_shot_shift_l[] = {KC_W, KC_F, COMBO_END};
const uint16_t PROGMEM combo_one_shot_shift_r[] = {KC_U, KC_Y, COMBO_END};
const uint16_t PROGMEM combo_reset[] = {KC_F3, KC_F10, KC_F6, KC_F11, COMBO_END};
// This globally defines all combos to be used
combo_t key_combos[] = {
    COMBO(combo_enter_default, KC_ENTER),
    COMBO(combo_enter_mouse, KC_ENTER),
    COMBO(combo_mouse_default, TG(_MOUSE)),
    COMBO(combo_mouse_layered, TG(_MOUSE)),
    #if CAPS_WORD_ENABLE == yes
    COMBO(combo_caps, QK_CAPS_WORD_TOGGLE),
    #endif
    COMBO(combo_tab, KC_TAB),
    COMBO(combo_one_shot_shift, OSM(MOD_LSFT)),
    COMBO(combo_esc, KC_ESC),
    COMBO(combo_backspace, KC_BACKSPACE),
    COMBO(combo_one_shot_shift_l, OSM(MOD_LSFT)),
    COMBO(combo_one_shot_shift_r, OSM(MOD_LSFT)),
    COMBO(combo_reset, QK_BOOTLOADER),
};
#endif

/*#if KEY_OVERRIDE_ENABLE == yes*/
#if defined(KEY_OVERRIDE_ENABLE)
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
#endif

// hold-tap config
bool HT_THUMBS_IF(uint16_t thekeycode) {
    switch (thekeycode) {
        case JJ_THUMB_L_INNER:
        case JJ_THUMB_L_OUTER:
        case JJ_THUMB_L_INNER_36_TMP:
        case JJ_THUMB_R_OUTER:
        case JJ_MAGIC:
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
// tap flow (require-prior-idle-ms)
static uint16_t jj_get_tap_keycode(uint16_t keycode) { // almost able to remove this!
  switch (keycode) {
    case QK_MOD_TAP ... QK_MOD_TAP_MAX:
      return QK_MOD_TAP_GET_TAP_KEYCODE(keycode);
#ifndef NO_ACTION_LAYER
    case QK_LAYER_TAP ... QK_LAYER_TAP_MAX:
      return QK_LAYER_TAP_GET_TAP_KEYCODE(keycode);
#endif  // NO_ACTION_LAYER
  }
  return keycode;
}
bool is_tap_flow_key(uint16_t keycode) {
  switch (jj_get_tap_keycode(keycode)) {
    // Tap Flow is enabled for the following keys. (Space removed here.)
    case KC_A ... KC_Z:
    case KC_DOT:
    case KC_COMM:
    case KC_SCLN:
    case KC_SLSH:
      return true;
  }
  return false;
}
const char chordal_hold_layout[MATRIX_ROWS][MATRIX_COLS] PROGMEM =
    LAYOUT(
        'L', 'L', 'L', 'L', 'L',  'R', 'R', 'R', 'R', 'R',
        'L', 'L', 'L', 'L', 'L',  'R', 'R', 'R', 'R', 'R',
        'L', 'L', 'L', 'L', 'L',  'R', 'R', 'R', 'R', 'R',
#ifdef JJ_SPLIT_36
                  '*', '*', '*',  '*', '*', '*'
#else
                       '*', '*',  '*', '*'
#endif
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

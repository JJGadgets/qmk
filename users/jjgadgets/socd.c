// Source: https://www.reddit.com/r/MechanicalKeyboards/comments/1ec88th/how_to_enable_null_bind_snap_tapsocd_on_any_qmk

#include "socd.h"

bool socd_w_down = false;
bool socd_r_down = false;
bool socd_a_down = false;
bool socd_s_down = false;
bool socd_d_down = false;
bool socd_q_down = false;
bool socd_f_down = false;
bool socd_e_down = false;

void jj_socd(keyrecord_t *record, uint16_t keycode1, uint16_t keycode2, bool* keydown1, bool keydown2) {
    if (record->event.pressed) {
        if (keydown2) {
            unregister_code(keycode2);
        }
        register_code(keycode1);
        *keydown1 = true;
    } else {
        unregister_code(keycode1);
        *keydown1 = false;

        if (keydown2) {
            register_code(keycode2);
        }
    }
}

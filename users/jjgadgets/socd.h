#pragma once
#include <stdint.h>
#include <stdbool.h>
#include "quantum.h"

enum gaming_keycodes {
  SOCD_W = SAFE_RANGE,
  /*SOCD_W,*/
  SOCD_R,
  SOCD_A,
  SOCD_S,
  SOCD_D,
  SOCD_Q,
  SOCD_E,
  SOCD_F
};

bool socd_w_down;
bool socd_r_down;
bool socd_a_down;
bool socd_s_down;
bool socd_d_down;
bool socd_q_down;
bool socd_f_down;
bool socd_e_down;

void jj_socd(keyrecord_t *record, uint16_t keycode1, uint16_t keycode2, bool* keydown1, bool* keydown2);

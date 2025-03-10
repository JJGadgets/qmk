#pragma once

#define EE_HANDS
/*#define MASTER_LEFT*/
// detect master based on location of USB rather than voltage detection, thank my cheap ass Pro Micro for that :(
#define SPLIT_USB_DETECT
/*#define SPLIT_USB_TIMEOUT 2000*/

// default but used in macros
#undef TAPPING_TERM
#define TAPPING_TERM_PER_KEY
#define QUICK_TAP_TERM_PER_KEY
#define PERMISSIVE_HOLD_PER_KEY
#define HOLD_ON_OTHER_KEY_PRESS_PER_KEY
#define CHORDAL_HOLD

/*// Enable rapid switch from tap to hold, disables double tap hold auto-repeat.*/
/*#define TAPPING_FORCE_HOLD*/

// Auto Shift
#define NO_AUTO_SHIFT_ALPHA
#define AUTO_SHIFT_TIMEOUT TAPPING_TERM
#define AUTO_SHIFT_NO_SETUP

// Neutralized keycode
#define DUMMY_MOD_NEUTRALIZER_KEYCODE KC_F18
// Neutralize key override mods (so a key override doesn't trigger the tap of these mods)
#undef MODS_TO_NEUTRALIZE
/*#define MODS_TO_NEUTRALIZE { MOD_BIT(KC_RALT), }*/

// Mouse key speed and acceleration.
#undef MOUSEKEY_DELAY
#define MOUSEKEY_DELAY          0
#undef MOUSEKEY_INTERVAL
#define MOUSEKEY_INTERVAL       16
#undef MOUSEKEY_WHEEL_DELAY
#define MOUSEKEY_WHEEL_DELAY    0
#undef MOUSEKEY_MAX_SPEED
#define MOUSEKEY_MAX_SPEED      6
#undef MOUSEKEY_TIME_TO_MAX
#define MOUSEKEY_TIME_TO_MAX    64

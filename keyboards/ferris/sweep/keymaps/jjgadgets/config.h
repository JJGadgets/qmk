#pragma once

#define EE_HANDS
/*#define MASTER_LEFT*/
// detect master based on location of USB rather than voltage detection, thank my cheap ass Pro Micro for that :(
#define SPLIT_USB_DETECT
#define SPLIT_USB_TIMEOUT 2500
#define SPLIT_WATCHDOG_ENABLE
#define SPLIT_WATCHDOG_TIMEOUT 10000

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
/*#define NO_AUTO_SHIFT_ALPHA*/
/*#define AUTO_SHIFT_TIMEOUT TAPPING_TERM*/
/*#define AUTO_SHIFT_NO_SETUP*/

// Neutralized keycode
#define DUMMY_MOD_NEUTRALIZER_KEYCODE KC_F18
// Neutralize key override mods (so a key override doesn't trigger the tap of these mods)
#undef MODS_TO_NEUTRALIZE
/*#define MODS_TO_NEUTRALIZE { MOD_BIT(KC_RALT), }*/

/*// Mouse key speed and acceleration.*/
/*#undef MOUSEKEY_DELAY*/
/*#define MOUSEKEY_DELAY          0*/
/*#undef MOUSEKEY_INTERVAL*/
/*#define MOUSEKEY_INTERVAL       16*/
/*#undef MOUSEKEY_WHEEL_DELAY*/
/*#define MOUSEKEY_WHEEL_DELAY    0*/
/*#undef MOUSEKEY_MAX_SPEED*/
/*#define MOUSEKEY_MAX_SPEED      6*/
/*#undef MOUSEKEY_TIME_TO_MAX*/
/*#define MOUSEKEY_TIME_TO_MAX    64*/

// space savings
#define LAYER_STATE_8BIT // 8 layers max, change to 16bit if 16 layers
#define EXTRA_SHORT_COMBOS // 6 keycodes max in combo trigger
#define NO_MUSIC_MODE
#undef LOCKING_SUPPORT_ENABLE
#undef LOCKING_RESYNC_ENABLE

// gaming
#define USB_POLLING_INTERVAL_MS 1 // 1000Hz polling rate

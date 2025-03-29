#define DEBOUNCE 5

// default but used in macros
#undef TAPPING_TERM
#define TAPPING_TERM 280
#define QUICK_TAP_TERM 175
#define PERMISSIVE_HOLD
#define TAP_FLOW_TERM 150
#define TAP_CODE_DELAY 100

// Neutralized keycode
#define DUMMY_MOD_NEUTRALIZER_KEYCODE KC_F18
// Neutralize key override mods (so a key override doesn't trigger the tap of these mods)
#undef MODS_TO_NEUTRALIZE

// space savings
#define LAYER_STATE_8BIT // 8 layers max, change to 16bit if 16 layers
#define NO_MUSIC_MODE
#undef LOCKING_SUPPORT_ENABLE
#undef LOCKING_RESYNC_ENABLE
#define NO_ACTION_ONESHOT

// gaming
#define USB_POLLING_INTERVAL_MS 1 // 1000Hz polling rate

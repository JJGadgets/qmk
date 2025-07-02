# ifdef SOCD_ENABLE
ifeq ($(strip $(SOCD_ENABLE)), yes)
	SRC += socd.c
endif
# ifdef REQUIRE_PRIOR_IDLE_MS
# 	SRC += require-prior-idle-ms.c
# endif
ifneq ($(strip $(JJ_SPLIT)), no)
	# common keymap stuff
	OPT_DEFS += -DJJ_SPLIT
	INTROSPECTION_KEYMAP_C = split.c

	# features
	COMBO_ENABLE = yes
	KEY_OVERRIDE_ENABLE = yes
	REPEAT_KEY_ENABLE = yes
	MOUSEKEY_ENABLE = yes
	LAYER_LOCK_ENABLE = yes
	CAPS_WORD_ENABLE = yes
	DYNAMIC_MACRO_ENABLE = yes
	SEND_STRING_ENABLE = yes

	# space savings
	LTO_ENABLE = yes
	MUSIC_ENABLE = no
	CONSOLE_ENABLE = no
	COMMAND_ENABLE = no
	MAGIC_ENABLE = no
	SPACE_CADET_ENABLE = no
	GRAVE_ESC_ENABLE = no

	# gaming
	SOCD_ENABLE = yes
endif
ifeq ($(strip $(JJ_SPLIT)), 36)
    OPT_DEFS += -DJJ_SPLIT_36
endif
ifeq ($(strip $(JJ_SPLIT)), 34)
    OPT_DEFS += -DJJ_SPLIT_34
endif
# ifeq ($(strip $(COMBO_ENABLE)), yes)
# 	VPATH += keyboards/gboards

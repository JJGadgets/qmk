# ifdef SOCD_ENABLE
ifeq ($(strip $(SOCD_ENABLE)), yes)
	SRC += socd.c
endif
# ifdef REQUIRE_PRIOR_IDLE_MS
# 	SRC += require-prior-idle-ms.c
# endif
ifneq ($(strip $(JJ_SPLIT)), no)
	# SRC += split.c
	OPT_DEFS += -DJJ_SPLIT
	INTROSPECTION_KEYMAP_C = split.c
endif
ifeq ($(strip $(JJ_SPLIT)), 36)
    OPT_DEFS += -DJJ_SPLIT_36
endif
ifeq ($(strip $(JJ_SPLIT)), 34)
    OPT_DEFS += -DJJ_SPLIT_34
endif
# ifeq ($(strip $(COMBO_ENABLE)), yes)
# 	VPATH += keyboards/gboards

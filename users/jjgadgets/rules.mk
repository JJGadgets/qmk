# ifdef SOCD_ENABLE
ifeq ($(strip $(SOCD_ENABLE)), yes)
	SRC += socd.c
endif
# ifdef REQUIRE_PRIOR_IDLE_MS
# 	SRC += require-prior-idle-ms.c
# endif

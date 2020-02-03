#include <stddef.h>

#include "config.h"

const UWORD WINDOW_SCREEN_WIDTH = 320;
const UWORD WINDOW_SCREEN_HEIGHT = 256;
const UWORD WINDOW_SCREEN_BPP = 4;

// Some legacy stuff from previous ACE versions.
// It's here while we are upgrading to the latest version.
// To be removed eventually.

// Originally in ace/util/custom.c
/* volatile tRayPos * const vhPosRegs = (APTR)&custom.vposr; */
volatile tRayPos * const vhPosRegs = (tRayPos REGPTR)(
	CUSTOM_BASE + offsetof(tCustom, vposr)
);



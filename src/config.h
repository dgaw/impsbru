#ifndef GUARD_IMPSBRU_CONFIG_H
#define GUARD_IMPSBRU_CONFIG_H

#include <ace/types.h>
#include <ace/utils/custom.h>

extern const UWORD WINDOW_SCREEN_WIDTH;
extern const UWORD WINDOW_SCREEN_HEIGHT;
extern const UWORD WINDOW_SCREEN_BPP;

#define CROSS_SIDE_A 0
#define CROSS_SIDE_B 1
#define CROSS_SIDE_C 2
#define CROSS_SIDE_D 3
#define CROSS_SIDE_E 4
#define CROSS_SIDE_F 5
#define CROSS_SIDE_COUNT 6
#define CROSS_SIDE_OPPOSITE_SHIFT 3

#define CROSS_SIDE_A_BIT (1 << CROSS_SIDE_A)
#define CROSS_SIDE_B_BIT (1 << CROSS_SIDE_B)
#define CROSS_SIDE_C_BIT (1 << CROSS_SIDE_C)
#define CROSS_SIDE_D_BIT (1 << CROSS_SIDE_D)
#define CROSS_SIDE_E_BIT (1 << CROSS_SIDE_E)
#define CROSS_SIDE_F_BIT (1 << CROSS_SIDE_F)

#define CROSS_SIDE_A_FINAL 6
#define CROSS_SIDE_C_FINAL 7
#define CROSS_SIDE_E_FINAL 8
#define CROSS_CENTER 9
#define CROSS_CURSOR 10
#define CROSS_CLEANUP 11

#define CROSS_SIDE_DESTINATION_OFFSET 12
/* CROSS_SIDE_DESTINATION FROM 13 TO 17 */
#define CROSS_ATLAS_SIZE 18

#define CROSS_CURSOR_TOP 26
#define CROSS_CURSOR_RIGHT 14
#define CROSS_CURSOR_BOTTOM 29
#define CROSS_CURSOR_LEFT 12

#define CROSS_BYTE_SIZE sizeof(UBYTE)
#define CROSS_WIDTH 64
#define CROSS_HEIGHT 64
#define CROSS_X_SHIFT 50
#define CROSS_Y_SHIFT 50
#define CROSS_ODD_Y_SHIFT 25

#define CUBE_ATLAS_SIZE 1

#define CUBE_WIDTH 18
#define CUBE_HEIGHT 18
#define CUBE_BITMAP_WIDTH 32
#define CUBE_BITMAP_HEIGHT 32

#define CUBE_STEP_X 2
#define CUBE_STEP_Y_SLOW 1
#define CUBE_STEP_Y_FAST 2

#define CUBE_DEPTH_BOTTOM 0
#define CUBE_DEPTH_MIDDLE 1
#define CUBE_DEPTH_TOP 2

#define MAP_WIDTH 6
#define MAP_HEIGHT 4
#define MAP_Y_OFFSET 17


// Some legacy stuff from previous ACE versions.
// It's here while we are upgrading to the latest version.
// To be removed eventually.

#define IN    /* Input parameter. Passed pointer contents is const */
#define OUT   /* Output parameter. Passed pointer contents will be changed. */
#define INOUT /* Input/output parameter. */

// Originally in ace/utils/custom.h
extern volatile tRayPos * const vhPosRegs;

// Originally in ace/utils/custom.c
#define CUSTOM_BASE 0xDFF000


#endif

#ifndef GUARD_ACE_UTIL_BITMAPMASK_H
#define GUARD_ACE_UTIL_BITMAPMASK_H

/*
 * This file was originally in ace/utils/bitmapmask.h
 * It's here while we are transitioning to the new version of ACE.
 * Probably will be removed eventually.
 */

#include <ace/types.h>
#include "config.h"

typedef struct _tBitmapMask {
	UWORD *pData;
	UWORD uwWidth;
	UWORD uwHeight;
} tBitmapMask;

tBitmapMask *bitmapMaskCreate(
	IN UWORD uwWidth,
	IN UWORD uwHeight
);

tBitmapMask *bitmapMaskCreateFromFile(
	IN char *szFile
);

void bitmapMaskDestroy(
	IN tBitmapMask *pMask
);

/**
 * @brief Writes mask to file in ACE's .msk format.
 * @param pMask  Mask to be saved.
 * @param szPath Path to output file.
 */
void bitmapMaskSave(
	IN tBitmapMask *pMask,
	IN char *szPath
);

/**
 *  @brief Writes mask as 1bpp bitmap.
 *  Only for debug purposes, because it's as unoptimized as bitmapSaveBmp().
 *
 *  @see bitmapSaveBmp()
 */
void bitmapMaskSaveBmp(
	IN tBitmapMask *pMask,
	IN char *szPath
);

#endif // GUARD_ACE_UTIL_BITMAPMASK_H

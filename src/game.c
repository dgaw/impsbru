#include "game.h"

#include <stdio.h>

#include <ace/types.h>
#include <ace/generic/main.h>
#include <ace/managers/game.h>
#include <ace/managers/viewport/simplebuffer.h>
#include <ace/utils/extview.h>
#include <ace/utils/palette.h>

#include "config.h"
#include "gamestates/menu/menu.h"

tView *g_pView;
tVPort *g_pVPort;
tSimpleBufferManager *g_pBufferManager;

void genericCreate() {
	g_pView = (tView *) viewCreate(0,
		TAG_VIEW_GLOBAL_CLUT, 1,
		TAG_DONE
	);

	copBlockDisableSprites(g_pView->pCopList, 0xFF);

	g_pVPort = vPortCreate(0,
		TAG_VPORT_VIEW, g_pView,
		TAG_DONE
	);

	g_pBufferManager = simpleBufferCreate(0,
		TAG_SIMPLEBUFFER_VPORT, g_pVPort,
		TAG_DONE
	);

	paletteLoad("/data/impsbru.plt", g_pVPort->pPalette, 1 << WINDOW_SCREEN_BPP);

	viewLoad(g_pView); // FIXME: This breaks in DEBUG but works ok in release

	/* asm("clr.w 0x100"); // To set a breakpoint in FS-UAE: w 1 $100 1 w */

	keyCreate(); // We'll use keyboard

	gamePushState(gsMenuCreate, gsMenuLoop, gsMenuDestroy);
}

void genericProcess() {
	keyProcess();
	gameProcess();
	WaitTOF();
}

void genericDestroy() {
	keyDestroy();
	viewDestroy(g_pView);
}

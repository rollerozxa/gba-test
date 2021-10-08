
#include <gba_console.h>
#include <gba_video.h>
#include <gba_interrupt.h>
#include <gba_systemcalls.h>
#include <gba_input.h>
#include <stdio.h>
#include <stdlib.h>

int playerX = 3;
int playerY = 3;

int oldPlayerX = -1;
int oldPlayerY = -1;

//---------------------------------------------------------------------------------
// Program entry point
//---------------------------------------------------------------------------------
int main(void) {
//---------------------------------------------------------------------------------

	// the vblank interrupt must be enabled for VBlankIntrWait() to work
	// since the default dispatcher handles the bios flags no vblank handler
	// is required
	irqInit();
	irqEnable(IRQ_VBLANK);

	consoleDemoInit();

	// ansi escape sequence to set print co-ordinates
	// /x1b[line;columnH
	//iprintf("\x1b[10;10HHello World!\n");

	for (int x = 0; x < 30; x++) {
		iprintf("\x1b[0;%dHX", x);
	}

	for (int x = 0; x < 30; x++) {
		iprintf("\x1b[19;%dHX", x);
	}
	
	for (int y = 0; y < 30; y++) {
		iprintf("\x1b[%d;0HX", y);
	}
	
	for (int y = 0; y < 30; y++) {
		iprintf("\x1b[%d;29HX", y);
	}

	while (1) {
		VBlankIntrWait();

		//iprintf("\x1b[%d;%dHOwO", rand() % 40, rand() % 30);

		scanKeys();
		u16 keys = keysDown();
		if (keys & KEY_UP) {
			playerY--;
		}
		if (keys & KEY_LEFT) {
			playerX--;	
		}
		if (keys & KEY_DOWN) {
			playerY++;	
		}
		if (keys & KEY_RIGHT) {
			playerX++;	
		}
		
		if (oldPlayerX != playerX || oldPlayerY != playerY) {
			iprintf("\x1b[%d;%dH ", oldPlayerY, oldPlayerX);
			oldPlayerX = playerX;
			oldPlayerY = playerY;
		}
		
		iprintf("\x1b[%d;%dHO", playerY, playerX);
	}
}



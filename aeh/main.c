#include <stdio.h>
#include <stdlib.h>
#include <math.h>

#include "tools.h"
#include "vect.h"

int main() {
	initTools();

	sfVideoMode mode = { W_WINDOW, H_WINDOW, 2 };
	sfRenderWindow* w = sfRenderWindow_create(mode, "Milky Way", sfNone, NULL);

	float tick = 0., tickExit = 0.;
	sfEvent e;
	sfVector2i mousePos;

	while (sfRenderWindow_isOpen(w)) {
		while (sfRenderWindow_pollEvent(w, &e));
		restartClock();
		tick += getDeltaTime();
		mousePos = sfMouse_getPositionRenderWindow(w);

		if (tick >= TICK) {
			if (testKeyPress(w, sfKeyEscape)) {
				tickExit += tick;
				if (tickExit >= 2.f) sfRenderWindow_close(w);
			}
			else tickExit = 0.f;

			tick = 0.f;
			sfRenderWindow_clear(w, sfBlack);





			sfRenderWindow_display(w);
		}

	}



	return 0;
}
#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <Windows.h>

#include "render.h"
#include "tools.h"
#include "vect.h"
#include "player.h"
#include "enemy.h"

int main() {
	///***  = = =  PREINIT  = = =  ***///
	ShowWindow(GetConsoleWindow(), 0);

	initTools();
	initMenu();

	sfVideoMode mode = { W_WINDOW, H_WINDOW, 2 };
	sfRenderWindow* w = sfRenderWindow_create(mode, "Milky Way", sfNone, NULL);
	sfRenderWindow_setFramerateLimit(w, TICKSPEED);

	/* == BACKDROP TEXTURES == */
	sfTexture* bg_1 = newTexture(PATH_TEXTURES"res_test_1.png");
	sfTexture* bg_main = newTexture(PATH_TEXTURES"backgroundMainMenu.jpg");
	sfTexture* aeh = newTexture(PATH_TEXTURES"a.png");
	sfTexture* grr = newTexture(PATH_TEXTURES"grr.png");

	/* == PLAYER == */
	Player player;
	initPlayer(&player, aeh);
	Enemy enemy;
	initEnemy(&enemy, grr, vector2f(500., 500.));

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



			displayMenu(w);
			renderBackdrop(w, bg_main);
	//		renderBackdrop(w, bg_1);
	//		renderSprite(w, NULL, aeh, TEX_RECT_NULL, vector2f(8., 8.), vectorSnap(vector2f(mousePos.x, mousePos.y), 8));

			playerUpdate(&player, w);
			enemyUpdate(&enemy, w);

			sfRenderWindow_display(w);
		}

	}



	return 0;
}
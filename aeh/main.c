#include <stdio.h>
#include <stdlib.h>
#include <math.h>

#include "render.h"
#include "tools.h"
#include "vect.h"
#include "MainMenu.h"



int main() {
	
	sfSprite* SpriteBackgroundMenu;
	sfTexture* TextureBackgroundMenu;
	sfVector2f pos = { 960.0f, 540.0f };
	SpriteBackgroundMenu = sfSprite_create();
	TextureBackgroundMenu = newTexture(TEXTURE_PATH"backgroundMainMenu.jpg");
	initTools();
	initMenu(SpriteBackgroundMenu, TextureBackgroundMenu, pos);
	sfVideoMode mode = { W_WINDOW, H_WINDOW, 2 };
	sfRenderWindow* w = sfRenderWindow_create(mode, "Milky Way", sfNone, NULL);

	/* == BACKDROP TEXTURES == */
	sfTexture* bg_1 = newTexture(PATH_TEXTURES"res_test_1.png");
	sfTexture* bg_main = newTexture(PATH_TEXTURES"backgroundMainMenu.jpg");
	sfTexture* aeh = newTexture(PATH_TEXTURES"a.png");


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
			renderSprite(w, NULL, aeh, TEX_RECT_NULL, vector2f(8., 8.), vectorSnap(vector2f(mousePos.x, mousePos.y), 8));


			sfRenderWindow_display(w);
		}

	}



	return 0;
}
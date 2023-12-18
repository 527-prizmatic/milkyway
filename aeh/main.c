#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <Windows.h>

#include "render.h"
#include "tools.h"
#include "vect.h"
#include "MainMenu.h"
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
	sfTexture* bg_1 = newTexture(PATH_TEXTURES"bg_galaxy.png");
	sfTexture* bg_2 = newTexture(PATH_TEXTURES"bg_nebula.png");
	sfTexture* bg_3 = newTexture(PATH_TEXTURES"bg_planet.png");
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

	Menu selectMenu = MENU;

	sfVector2i mousePos;

	sfSprite* SpritePlayMenu = sfSprite_create();
	sfTexture* TexturePlayMenu = newTexture(TEXTURE_PATH"buttonStart.png");
	sfVector2f originePlay = vector2f(sfSprite_getGlobalBounds(SpritePlayMenu).width / 2, sfSprite_getGlobalBounds(SpritePlayMenu).height / 2);
	setupSprite(SpritePlayMenu, TexturePlayMenu, TEX_RECT_NULL, originePlay, vector2f(0.5f, 0.5f), vector2f(460.0f, 740.0f));

	sfSprite* SpriteQuitMenu = sfSprite_create();
	sfTexture* TextureQuitMenu = newTexture(TEXTURE_PATH"BlockQuitter.png");
	sfVector2f origineQuit = vector2f(sfSprite_getGlobalBounds(SpriteQuitMenu).width / 2, sfSprite_getGlobalBounds(SpriteQuitMenu).height / 2);
	setupSprite(SpriteQuitMenu, TextureQuitMenu, TEX_RECT_NULL, origineQuit, vector2f(0.5f, 0.5f), vector2f(960.0f, 740.0f));

	sfTexture* TextureBackgroundMenu;
	TextureBackgroundMenu = newTexture(TEXTURE_PATH"backgroundMainMenu.jpg");

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

			updateMenu(w, SpritePlayMenu, SpriteQuitMenu, mousePos, selectMenu);

			sfRenderWindow_clear(w, sfBlack);
			displayMenu(w, TextureBackgroundMenu, SpritePlayMenu, SpriteQuitMenu);
			renderBackdrop(w, bg_1);
	//		renderBackdrop(w, bg_1);
	//		renderSprite(w, NULL, aeh, TEX_RECT_NULL, vector2f(8., 8.), vectorSnap(vector2f(mousePos.x, mousePos.y), 8));
			playerUpdate(&player, w);
			enemyUpdate(&enemy, w);

			sfRenderWindow_display(w);
		}
	}

	return 0;
}
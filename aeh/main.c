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
#include "level.h"

int main() {
	///***  = = =  PREINIT  = = =  ***///
	ShowWindow(GetConsoleWindow(), 0);

	initTools();
	initMenu();

	char lvl_1[] = PATH_LEVELS"lv1.dat";

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
	char levelBuffer[8][16];
	Enemy* enemyBuffer[8][16];
	char enemyMoveDir = 0;
	int grid = (W_WINDOW * 0.75) / 20.;
	sfVector2f mapBounds = vector2f(W_WINDOW * 0.125, W_WINDOW * 0.875 - grid);
	int enemyCount = 0;
	int dirChangeFlag = 0;

	State gameState = MENU;
	sfVector2i mousePos;
	int lives = 3;
	int tickDeath = 0;

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
	sfVector2f oldPos;

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

			if (gameState == MENU) {
				updateMenu(w, SpritePlayMenu, SpriteQuitMenu, mousePos, &gameState, levelBuffer, enemyBuffer);
				displayMenu(w, TextureBackgroundMenu, SpritePlayMenu, SpriteQuitMenu);
			}
			else if (gameState == LOAD) {
				gameState = GAME;
				readLevelFile(lvl_1, levelBuffer);

				enemyCount = 0;
				for (int i = 0; i < 8; i++) {
					for (int j = 0; j < 16; j++) {
						if (levelBuffer[i][j] == 1) {
							enemyBuffer[i][j] = malloc(sizeof(Enemy));
							initEnemy(enemyBuffer[i][j], grr, vector2f(j * grid + grid * 2 + W_WINDOW / 8., i * grid + grid * 2));
							enemyCount++;
						}
						else enemyBuffer[i][j] = NULL;
					}
				}
			}
			else if (gameState == GAME) {
				renderBackdrop(w, bg_1);
				playerUpdate(&player, w);
				tickDeath = -1;

				for (int i = 0; i < 8; i++) {
					for (int j = 0; j < 16; j++) {
						if (enemyBuffer[i][j] != NULL) {
							enemyUpdate(enemyBuffer[i][j], w, enemyMoveDir, enemyCount);
							if (enemyBuffer[i][j]->pos.x < mapBounds.x) dirChangeFlag = -1;
							if (enemyBuffer[i][j]->pos.x > mapBounds.y) dirChangeFlag = 1;
						}
					}
				}

				if (dirChangeFlag == 1) {
					dirChangeFlag = 0;
					enemyMoveDir = 0;
					for (int i = 0; i < 8; i++) for (int j = 0; j < 16; j++) if (enemyBuffer[i][j] != NULL) enemyBuffer[i][j]->pos.y += 16;
				}
				else if (dirChangeFlag == -1) {
					dirChangeFlag = 0;
					enemyMoveDir = 1;
					for (int i = 0; i < 8; i++) for (int j = 0; j < 16; j++) if (enemyBuffer[i][j] != NULL) enemyBuffer[i][j]->pos.y += 16;
				}
				
				if (enemyBuffer[7][0]->pos.y > 800) {
					oldPos.x = enemyBuffer[0][0]->pos.x;
					oldPos.y = enemyBuffer[0][0]->pos.y;
					lives--;
					gameState = DEATH;
				}
			}
			else if (gameState == DEATH) {
				renderBackdrop(w, bg_1);
				for (int i = 0; i < 8; i++) {
					for (int j = 0; j < 16; j++) {
						if (enemyBuffer[i][j] != NULL) {
							if (tickDeath < 40) {
								enemyBuffer[i][j]->pos.x = lerp(oldPos.x + j * grid, W_WINDOW / 2, tickDeath / 40.);
								enemyBuffer[i][j]->pos.y = lerp(oldPos.y + i * grid, H_WINDOW / 2, tickDeath / 40.);
							}
							else if (tickDeath < 80) {
								enemyBuffer[i][j]->pos.x = lerp(W_WINDOW / 2, j * grid + grid * 2 + W_WINDOW / 8., (tickDeath - 40) / 40.);
								enemyBuffer[i][j]->pos.y = lerp(H_WINDOW / 2, i * grid + grid * 2, (tickDeath - 40) / 40.);
							}
							enemyUpdate(enemyBuffer[i][j], w, -1, enemyCount);
						}
					}
				}
				tickDeath++;

				if (tickDeath == 120) gameState = GAME;
			}
			
			sfRenderWindow_display(w);
		}
	}

	return 0;
}
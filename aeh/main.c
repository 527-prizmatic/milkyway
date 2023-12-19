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
#include "music.h"

int main() {
	///***  = = =  PREINIT  = = =  ***///
	ShowWindow(GetConsoleWindow(), 0);
	initTools();

	char lvl_1[] = PATH_LEVELS"lv1.dat";
	char lvl_2[] = PATH_LEVELS"lv2.dat";
	char lvl_3[] = PATH_LEVELS"lv3.dat";

	sfVideoMode mode = { W_WINDOW, H_WINDOW, 2 };
	sfRenderWindow* w = sfRenderWindow_create(mode, "Milky Way", sfNone, NULL);
	sfRenderWindow_setFramerateLimit(w, TICKSPEED);

	///* == TEXTURE DUMP == *///
	sfTexture* bgGalaxy = newTexture(PATH_TEXTURES"bg_galaxy.png");
	sfTexture* bgNebula = newTexture(PATH_TEXTURES"bg_nebula.png");
	sfTexture* bgPlanet = newTexture(PATH_TEXTURES"bg_planet.png");
	sfTexture* bgMain = newTexture(PATH_TEXTURES"bg_menu.png");
	sfTexture* texPlayerShip = newTexture(PATH_TEXTURES"ship_proto.png");
	sfTexture* texEnemy1 = newTexture(PATH_TEXTURES"enemy_1.png");
	sfTexture* texEnemy2 = newTexture(PATH_TEXTURES"enemy_2.png");
	sfTexture* texButtonStart = newTexture(PATH_TEXTURES"button_start.png");
	sfTexture* texButtonQuit = newTexture(PATH_TEXTURES"button_quit.png");

	///* == PLAYER INIT == *///
	Player player;
	initPlayer(&player, texPlayerShip);

	///* == MISC TECHNICAL VARS == *///
	float tick = 0., tickExit = 0.; // Timers - 1
	int tickDeath = 0; // Timers - 2
	sfEvent e; // Event handler
	char levelBuffer[8][16]; // Contains level raw binary data
	Enemy* enemyBuffer[8][16]; // Contains enemy objects
	char enemyMoveDir = 0; // Whether the enemy formation hovers to the left or to the right
	int grid = (W_WINDOW * 0.75) / 20.; // Spacing between enemies within a formation
	sfVector2f mapBounds = vector2f(W_WINDOW * 0.125, W_WINDOW * 0.875 - grid); // Game area's boundaries
	int enemyCount = 0; // How many enemies are present on-screen
	int dirChangeFlag = 0; // Technical flag for changing enemy movement direction
	float enemyPosY = 0.; // Enemy formation's vertical position
	State gameState = MENU; // Game state
	sfVector2i mousePos; // Mouse position
	int lives = 3; // Player's current lives
	sfVector2f oldPos = vector2f(0., 0.); // Keeps track of where the enemy formation was for the death anim's initial lerp

	///* == MAIN MENU BUTTONS == *///
	sfSprite* SpritePlayMenu = sfSprite_create();
	sfSprite* SpriteQuitMenu = sfSprite_create();
	sfVector2f originPlay = vector2f(sfSprite_getGlobalBounds(SpritePlayMenu).width / 2, sfSprite_getGlobalBounds(SpritePlayMenu).height / 2);
	sfVector2f originQuit = vector2f(sfSprite_getGlobalBounds(SpriteQuitMenu).width / 2, sfSprite_getGlobalBounds(SpriteQuitMenu).height / 2);
	setupSprite(SpritePlayMenu, texButtonStart, TEX_RECT_NULL, originPlay, vector2f(0.5f, 0.5f), vector2f(460.0f, 740.0f));
	setupSprite(SpriteQuitMenu, texButtonQuit, TEX_RECT_NULL, originQuit, vector2f(0.5f, 0.5f), vector2f(960.0f, 740.0f));

	///* == MUSIC & SFX == *///
	sfMusic* musicMenu = sfMusic_createFromFile(PATH_MUSIC"invaders.ogg");
	sfMusic* musicGame = sfMusic_createFromFile(PATH_MUSIC"stretch.ogg");
	MusicState music = MENU;
	stopMusic(musicMenu, musicGame);
	updateMusic(&music, musicMenu, musicGame);

	sfSound* soundPlayerShoot = sfSound_create();
	sfSoundBuffer* soundBufferPlayerShoot = sfSoundBuffer_createFromFile(PATH_SOUNDS"shoot-1-81135.ogg");
	sfSound_setBuffer(soundPlayerShoot, soundBufferPlayerShoot);

	sfSound* soundEnnemisShoot = sfSound_create();
	sfSoundBuffer* soundBufferEnnemisShoot = sfSoundBuffer_createFromFile(PATH_SOUNDS"shoot-5-102360.ogg");
	sfSound_setBuffer(soundEnnemisShoot, soundBufferEnnemisShoot);

	///***  = = =  GAME LOOP  = = =  ***///
	while (sfRenderWindow_isOpen(w)) {
		while (sfRenderWindow_pollEvent(w, &e));
		restartClock();
		tick += getDeltaTime();
		mousePos = sfMouse_getPositionRenderWindow(w);

		if (tick >= TICK) {
			sfRenderWindow_clear(w, sfBlack);
			if (testKeyPress(w, sfKeyEscape)) {
				tickExit += tick;
				if (tickExit >= 2.f) sfRenderWindow_close(w);
			}
			else tickExit = 0.f;
			tick = 0.f;

			if (gameState == MENU) {
				updateMenu(w, SpritePlayMenu, SpriteQuitMenu, mousePos, &gameState, levelBuffer, enemyBuffer);
				displayMenu(w, bgMain, SpritePlayMenu, SpriteQuitMenu);
			}
			else if (gameState == LOAD) {
				gameState = GAME;
				readLevelFile(lvl_3, levelBuffer);

				enemyCount = 0;
				for (int i = 0; i < 8; i++) {
					for (int j = 0; j < 16; j++) {
						if (levelBuffer[i][j] == 1) {
							enemyBuffer[i][j] = malloc(sizeof(Enemy));
							initEnemy(enemyBuffer[i][j], texEnemy1, vector2f(j * grid + grid * 2 + W_WINDOW / 8., i * grid + grid * 2), ENEMY_1);
							enemyCount++;
						}
						else if (levelBuffer[i][j] == 2) {
							enemyBuffer[i][j] = malloc(sizeof(Enemy));
							initEnemy(enemyBuffer[i][j], texEnemy2, vector2f(j * grid + grid * 2 + W_WINDOW / 8., i * grid + grid * 2), ENEMY_2);
							enemyCount++;
						}
						else enemyBuffer[i][j] = NULL;
					}
				}
				enemyPosY = 9 * grid;
				music = MUSICGAME;
				stopMusic(musicMenu, musicGame);
				updateMusic(&music, musicMenu, musicGame);
			}
			else if (gameState == GAME) {
				renderBackdrop(w, bgGalaxy);
				playerUpdate(&player, w, soundPlayerShoot);
				tickDeath = -1;

				for (int i = 0; i < 8; i++) {
					for (int j = 0; j < 16; j++) {
						if (enemyBuffer[i][j] != NULL) {
							enemyUpdate(enemyBuffer[i][j], w, enemyMoveDir, enemyCount, soundEnnemisShoot);
							if (enemyBuffer[i][j]->pos.x < mapBounds.x) dirChangeFlag = -1;
							if (enemyBuffer[i][j]->pos.x > mapBounds.y) dirChangeFlag = 1;
						}
					}
				}

				if (dirChangeFlag == 1) {
					dirChangeFlag = 0;
					enemyMoveDir = 0;
					for (int i = 0; i < 8; i++) for (int j = 0; j < 16; j++) if (enemyBuffer[i][j] != NULL) enemyBuffer[i][j]->pos.y += 16;
					enemyPosY += 16;
				}
				else if (dirChangeFlag == -1) {
					dirChangeFlag = 0;
					enemyMoveDir = 1;
					for (int i = 0; i < 8; i++) for (int j = 0; j < 16; j++) if (enemyBuffer[i][j] != NULL) enemyBuffer[i][j]->pos.y += 16;
					enemyPosY += 16;
				}
				
				if (enemyPosY > 800) {
					if (enemyMoveDir == 1) oldPos.x = mapBounds.x;
					else oldPos.x = mapBounds.y - grid * 16;
					oldPos.y = enemyPosY - grid * 7;
					lives--;
					gameState = DEATH;
				}
			}
			else if (gameState == DEATH) {
				sfMusic_pause(musicGame);
				renderBackdrop(w, bgGalaxy);
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
							enemyUpdate(enemyBuffer[i][j], w, -1, enemyCount, soundEnnemisShoot);
						}
					}
				}
				tickDeath++;
				enemyPosY = 9 * grid;

				if (tickDeath == 120) {
					gameState = GAME;
					sfMusic_play(musicGame);
				}
			}
			
			sfRenderWindow_display(w);
		}
	}

	return 0;
}
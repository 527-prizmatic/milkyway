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

#define ITERATE_ALL_ENEMIES for (int i = 0; i < 8; i++) for (int j = 0; j < 16; j++) if (enemyBuffer[i][j] != NULL)

int main() {
	///***  = = =  PREINIT  = = =  ***///
	ShowWindow(GetConsoleWindow(), 0);
	initTools();

	char lvl_1[] = PATH_LEVELS"lv1.dat";
	char lvl_2[] = PATH_LEVELS"lv2.dat";
	char lvl_3[] = PATH_LEVELS"lv3.dat";
	char lvl_4[] = PATH_LEVELS"lv4.dat";
	char lvl_5[] = PATH_LEVELS"lv5.dat";

	sfVideoMode mode = { W_WINDOW, H_WINDOW, 2 };
	sfRenderWindow* w = sfRenderWindow_create(mode, "Milky Way", sfNone, NULL);
	sfRenderWindow_setFramerateLimit(w, TICKSPEED);

	///* == TEXTURE DUMP == *///
	sfTexture* bgGalaxy = newTexture(PATH_TEXTURES"bg_galaxy.png");
	sfTexture* bgNebula = newTexture(PATH_TEXTURES"bg_nebula.png");
	sfTexture* bgPlanet = newTexture(PATH_TEXTURES"bg_planet.png");
	sfTexture* bgStar = newTexture(PATH_TEXTURES"bg_star.png");
	sfTexture* bgStation = newTexture(PATH_TEXTURES"bg_station.png");
	sfTexture* bgMain = newTexture(PATH_TEXTURES"bg_menu.png");
	sfTexture* bgGO = newTexture(PATH_TEXTURES"GAMEOVER.png");
	sfTexture* texPlayerShip = newTexture(PATH_TEXTURES"ship_proto.png");
	sfTexture* texEnemy1 = newTexture(PATH_TEXTURES"enemy_1.png");
	sfTexture* texEnemy2 = newTexture(PATH_TEXTURES"enemy_2.png");
	sfTexture* texEnemy3 = newTexture(PATH_TEXTURES"enemy_3.png");
	sfTexture* texEnemy4 = newTexture(PATH_TEXTURES"enemy_4.png");
	sfTexture* texEnemy5 = newTexture(PATH_TEXTURES"enemy_5.png");
	sfTexture* texEnemy6 = newTexture(PATH_TEXTURES"enemy_6.png");
	sfTexture* texEnemy7 = newTexture(PATH_TEXTURES"enemy_7.png");
	sfTexture* texEnemy8 = newTexture(PATH_TEXTURES"enemy_8.png");

	///* == PLAYER INIT == *///
	Player player;
	initPlayer(&player, texPlayerShip);

	///* == RANDOMIZED LEVEL DATA == *///
	char* lvlCurrent = NULL;
	sfTexture* bgCurrent = NULL;

	///* == MISC TECHNICAL VARS == *///
	float tick = 0., tickExit = 0.; // Timers - 1
	int tickDeath = 0, tickNext = 0, tickShaders = 0, tickGO = 0; // Timers - 2
	sfEvent e; // Event handler
	char levelBuffer[8][16]; // Contains level raw binary data
	Enemy* enemyBuffer[8][16]; // Contains enemy objects
	char enemyMoveDir = 0; // Whether the enemy formation hovers to the left or to the right
	int grid = (int)(W_WINDOW * 0.75) / 20.; // Spacing between enemies within a formation
	sfVector2f mapBounds = vector2f(W_WINDOW * 0.125, W_WINDOW * 0.875 - grid); // Game area's boundaries
	int enemyCount = 0; // How many enemies are present on-screen
	int dirChangeFlag = 0; // Technical flag for changing enemy movement direction
	sfVector2f enemyPos = vector2f(0., 0.); // Enemy formation's vertical position
	State gameState = MENU; // Game state
	sfVector2i mousePos; // Mouse position
	int lives = 3; // Player's current lives
	sfVector2f oldPos = vector2f(0., 0.); // Keeps track of where the enemy formation was for the death anim's initial lerp
	char flagCheckCollisions = 1;

	///* == SHADERS == *///
	sfShader* shaderBulletsP = NULL;
	sfRenderStates rstateBulletsP;
	sfShader* shaderBulletsE = NULL;
	sfRenderStates rstateBulletsE;
	sfShader* shaderBG = NULL;
	sfRenderStates rstateBG;
	if (!sfShader_isAvailable()) {
		printf("cususucdics");
		return;
	}
	else {
		shaderBulletsP = sfShader_createFromFile(NULL, NULL, PATH_SHADERS"bulletsp.frag");
		if (shaderBulletsP == NULL) return;
		rstateBulletsP.shader = shaderBulletsP;
		rstateBulletsP.blendMode = sfBlendAlpha;
		rstateBulletsP.transform = sfTransform_Identity;
		rstateBulletsP.texture = NULL;

		shaderBulletsE = sfShader_createFromFile(NULL, NULL, PATH_SHADERS"bulletse.frag");
		if (shaderBulletsE == NULL) return;
		rstateBulletsE.shader = shaderBulletsE;
		rstateBulletsE.blendMode = sfBlendAlpha;
		rstateBulletsE.transform = sfTransform_Identity;
		rstateBulletsE.texture = NULL;

		shaderBG = sfShader_createFromFile(NULL, NULL, PATH_SHADERS"bg.frag");
		if (shaderBG == NULL) return;
		rstateBG.shader = shaderBG;
		rstateBG.blendMode = sfBlendAlpha;
		rstateBG.transform = sfTransform_Identity;
		rstateBG.texture = NULL;
	}
	sfShader_setVec2Uniform(shaderBulletsP, "uRes", vector2f(W_WINDOW, H_WINDOW));
	sfShader_setVec2Uniform(shaderBulletsE, "uRes", vector2f(W_WINDOW, H_WINDOW));
	sfShader_setVec2Uniform(shaderBG, "uRes", vector2f(W_WINDOW, H_WINDOW));


	///* == MUSIC & SFX == *///
	sfMusic* musicMenu = sfMusic_createFromFile(PATH_MUSIC"invaders.ogg");
	sfMusic* musicGame = sfMusic_createFromFile(PATH_MUSIC"stretch.ogg");
	sfMusic* musicPluto = sfMusic_createFromFile(PATH_MUSIC"pluto.ogg");
	sfMusic* musicSaturn = sfMusic_createFromFile(PATH_MUSIC"saturn.ogg");
	sfMusic* musicMars = sfMusic_createFromFile(PATH_MUSIC"mars.ogg");
	sfMusic* musicVenus = sfMusic_createFromFile(PATH_MUSIC"venus.ogg");
	sfMusic* musicMercury = sfMusic_createFromFile(PATH_MUSIC"mercury.ogg");
	sfMusic* musicCurrent = musicGame;
	MusicState music = MENU;
	stopMusic(musicMenu, musicCurrent);
	updateMusic(&music, musicMenu, musicCurrent);

	sfSound* soundPlayerShoot = sfSound_create();
	sfSoundBuffer* soundBufferPlayerShoot = sfSoundBuffer_createFromFile(PATH_SOUNDS"shoot-allie.ogg");
	sfSound_setBuffer(soundPlayerShoot, soundBufferPlayerShoot);

	sfSound* soundEnnemisShoot = sfSound_create();
	sfSoundBuffer* soundBufferEnnemisShoot = sfSoundBuffer_createFromFile(PATH_SOUNDS"shoot-ennemis.ogg");
	sfSound_setBuffer(soundEnnemisShoot, soundBufferEnnemisShoot);

	///* == SCORE BOARD == *///
	int scoreGame = 0;
	int scoreGameBonusLife = 0;
	sfText* score = sfText_create();
	sfFont* scoreFront = sfFont_createFromFile(PATH_FRONT"8-bit-hud.ttf");
	sfVector2f txtsize = { 0.8f, 0.8f };
	sfVector2f txtPos = { 1600.0f, 50.0f };
	char scoreChar[16];

	///* == TEXT MAIN MENU == *///
	sfText* PressSpace = sfText_create();
	sfFont* PressSpaceFront = sfFont_createFromFile(PATH_FRONT"8-bit-hud.ttf");
	sfVector2f PressSpacetxtsize = { 0.8f, 0.8f };
	sfVector2f PressSpacetxtPos = { 810.0f, 840.0f };
	char* PressSpaceChar = "Press Space";
	sfText_setFont(PressSpace, PressSpaceFront);
	sfText_setString(PressSpace, PressSpaceChar);
	sfText_setScale(PressSpace, PressSpacetxtsize);
	sfText_setPosition(PressSpace, PressSpacetxtPos);

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
			tickShaders++;
			sfShader_setIntUniform(shaderBulletsP, "uTime", tickShaders);
			sfShader_setIntUniform(shaderBulletsE, "uTime", tickShaders);
			sfShader_setIntUniform(shaderBG, "uTime", tickShaders);

			/// Gamestate - MAIN MENU
			if (gameState == MENU) {
				updateMenu(w, &gameState);
				displayMenu(w, bgMain, PressSpace);
			}

			/// Gamestate - LOADING NEXT WAVE
			else if (gameState == LOAD) {
				stopMusic(musicMenu, musicCurrent);
				gameState = GAME;
				int rl = random(5);
				switch (rl) {
				case 0: lvlCurrent = lvl_1; break;
				case 1: lvlCurrent = lvl_2; break;
				case 2: lvlCurrent = lvl_3; break;
				case 3: lvlCurrent = lvl_4; break;
				case 4: lvlCurrent = lvl_5; break;
				}

				int rb = random(5);
				switch (rb) {
				case 0: bgCurrent = bgGalaxy; break;
				case 1: bgCurrent = bgNebula; break;
				case 2: bgCurrent = bgPlanet; break;
				case 3: bgCurrent = bgStar; break;
				case 4: bgCurrent = bgStation; break;
				}
				sfShader_setTextureUniform(shaderBG, "texture", bgCurrent);

				int rm = random(5);
				switch (rm) {
				case 0: musicCurrent = musicPluto; break;
				case 1: musicCurrent = musicSaturn; break;
				case 2: musicCurrent = musicMars; break;
				case 3: musicCurrent = musicVenus; break;
				case 4: musicCurrent = musicMercury; break;
				default: musicCurrent = musicPluto; break;
				}

				readLevelFile(lvlCurrent, levelBuffer);

				enemyCount = 0;
				for (int i = 0; i < 8; i++) {
					for (int j = 0; j < 16; j++) {
						if (levelBuffer[i][j] != 0) {
							enemyBuffer[i][j] = malloc(sizeof(Enemy));
							enemyCount++;
							if (levelBuffer[i][j] == 1) initEnemy(enemyBuffer[i][j], texEnemy1, vector2f(j * grid + grid * 2 + W_WINDOW / 8., i * grid + grid * 2), ENEMY_1);
							else if (levelBuffer[i][j] == 2) initEnemy(enemyBuffer[i][j], texEnemy2, vector2f(j * grid + grid * 2 + W_WINDOW / 8., i * grid + grid * 2), ENEMY_2);
							else if (levelBuffer[i][j] == 3) initEnemy(enemyBuffer[i][j], texEnemy3, vector2f(j * grid + grid * 2 + W_WINDOW / 8., i * grid + grid * 2), ENEMY_3);
							else if (levelBuffer[i][j] == 4) initEnemy(enemyBuffer[i][j], texEnemy4, vector2f(j * grid + grid * 2 + W_WINDOW / 8., i * grid + grid * 2), ENEMY_4);
							else if (levelBuffer[i][j] == 5) initEnemy(enemyBuffer[i][j], texEnemy5, vector2f(j * grid + grid * 2 + W_WINDOW / 8., i * grid + grid * 2), ENEMY_5);
							else if (levelBuffer[i][j] == 6) initEnemy(enemyBuffer[i][j], texEnemy6, vector2f(j * grid + grid * 2 + W_WINDOW / 8., i * grid + grid * 2), ENEMY_6);
							else if (levelBuffer[i][j] == 7) initEnemy(enemyBuffer[i][j], texEnemy7, vector2f(j * grid + grid * 2 + W_WINDOW / 8., i * grid + grid * 2), ENEMY_7);
							else if (levelBuffer[i][j] == 8) initEnemy(enemyBuffer[i][j], texEnemy8, vector2f(j * grid + grid * 2 + W_WINDOW / 8., i * grid + grid * 2), ENEMY_8);
						}
						else enemyBuffer[i][j] = NULL;
					}
				}
				enemyPos.x = grid * 2 + W_WINDOW / 8.;
				enemyPos.y = 2 * grid;
				music = MUSICGAME;
				updateMusic(&music, musicMenu, musicCurrent);
			}

			/// Gamestate - IN-GAME
			else if (gameState == GAME) {
				renderBackdrop(w, bgCurrent, &rstateBG);
				playerUpdate(&player, w, soundPlayerShoot, &rstateBulletsP);
				tickDeath = -1;
				tickNext = -1;
				sprintf(scoreChar,"%07d", scoreGame);
				sfText_setFont(score, scoreFront);
				sfText_setString(score, scoreChar);
				sfText_setScale(score, txtsize);
				sfText_setPosition(score, txtPos);
				sfRenderWindow_drawText(w, score, NULL);
				enemyPos.x += ENEMY_SPD / (enemyCount + 1) * TICK * 2 * (enemyMoveDir - 0.5);

				ITERATE_ALL_ENEMIES {
					enemyUpdate(enemyBuffer[i][j], w, enemyMoveDir, enemyCount, gameState, soundEnnemisShoot, &rstateBulletsE);
					if (enemyBuffer[i][j]->pos.x < mapBounds.x) dirChangeFlag = -1;
					if (enemyBuffer[i][j]->pos.x > mapBounds.y) dirChangeFlag = 1;

					// Testing for player-bullet collisions
					if (flagCheckCollisions) {
						if (enemyBuffer[i][j]->hasFired) {
							sfFloatRect hitboxP = sfSprite_getGlobalBounds(player.spr);
							sfFloatRect hitboxB = sfSprite_getGlobalBounds(enemyBuffer[i][j]->bullet->spr);
							if (sfFloatRect_intersects(&hitboxP, &hitboxB, NULL)) {
								destroyBulletEnemy(enemyBuffer[i][j]);
								oldPos.x = enemyPos.x;
								oldPos.y = enemyPos.y;
								lives--;
								gameState = DEATH;
								flagCheckCollisions = 0;
								break;
							}
						}
					}
					flagCheckCollisions = 1;
				}

				if (dirChangeFlag == 1) {
					dirChangeFlag = 0;
					enemyMoveDir = 0;
					ITERATE_ALL_ENEMIES {
						enemyBuffer[i][j]->pos.y += 20;
						if (enemyBuffer[i][j]->pos.y > 800) {
							oldPos.x = mapBounds.y - grid * 16;
							oldPos.y = enemyPos.y;
							lives--;
							gameState = DEATH;
						}
					}
					enemyPos.y += 16;
				}
				else if (dirChangeFlag == -1) {
					dirChangeFlag = 0;
					enemyMoveDir = 1;
					ITERATE_ALL_ENEMIES {
						enemyBuffer[i][j]->pos.y += 20;
						if (enemyBuffer[i][j]->pos.y > 800) {
							oldPos.x = mapBounds.x;
							oldPos.y = enemyPos.y;
							lives--;
							gameState = DEATH;
						}

					}
					enemyPos.y += 16;
				}
				
				// Enemy-bullet collisions
				if (player.hasFired) {
					ITERATE_ALL_ENEMIES if (flagCheckCollisions) {
						sfFloatRect hitboxE = sfSprite_getGlobalBounds(enemyBuffer[i][j]->spr);
						sfFloatRect hitboxB = sfSprite_getGlobalBounds(player.bullet->spr);
						if (sfFloatRect_intersects(&hitboxE, &hitboxB, NULL)) {
							scoreGame += 100;
							scoreGameBonusLife += 100;
							if (scoreGameBonusLife >= 10000) {
								scoreGameBonusLife = 0;
								lives += 1;
							}
							destroyBulletPlayer(&player);
							if (enemyBuffer[i][j]->hasFired) destroyBulletEnemy(enemyBuffer[i][j]);
							free(enemyBuffer[i][j]);
							enemyBuffer[i][j] = NULL;
							enemyCount--;
							flagCheckCollisions = 0;
							break;
						}
					}
				}
				flagCheckCollisions = 1;
				if (enemyCount == 0) gameState = NEXT;

				for (int i = 0; i < lives; i++) {
					sfSprite_setPosition(player.spr, vector2f(40., 40. + 64 * i));
					sfRenderWindow_drawSprite(w, player.spr, NULL);
				}
			}

			/// Gamestate - DEATH TRANSITION
			else if (gameState == DEATH) {
				sfMusic_pause(musicCurrent);
				renderBackdrop(w, bgCurrent, &rstateBG);
				ITERATE_ALL_ENEMIES {
					if (tickDeath >= 0 && tickDeath < 40) {
						enemyBuffer[i][j]->pos.x = lerp(oldPos.x + j * grid, W_WINDOW / 2, tickDeath / 40.);
						enemyBuffer[i][j]->pos.y = lerp(oldPos.y + i * grid, H_WINDOW / 2, tickDeath / 40.);
					}
					else if (tickDeath >= 0 && tickDeath < 80) {
						enemyBuffer[i][j]->pos.x = lerp(W_WINDOW / 2, j * grid + grid * 2 + W_WINDOW / 8., (tickDeath - 40) / 40.);
						enemyBuffer[i][j]->pos.y = lerp(H_WINDOW / 2, i * grid + grid * 2, (tickDeath - 40) / 40.);
					}
					enemyUpdate(enemyBuffer[i][j], w, -1, enemyCount, gameState, soundEnnemisShoot, &rstateBulletsE);
				}
				tickDeath++;
				enemyPos.y = 2 * grid;

				if (tickDeath == 120 && lives > 0) {
					enemyPos.x = grid * 2 + W_WINDOW / 8.;
					enemyPos.y = grid * 2;
					gameState = GAME;
					sfMusic_play(musicCurrent);
				}
				else if (tickDeath == 120 && lives == 0) {
					gameState = GAMEOVER;
				}
			}

			/// Gamestate - GAME OVER
			else if (gameState == GAMEOVER) {
				renderBackdrop(w, bgGO, NULL);
				if (tickGO > 100) {
					gameState = MENU;
					music = MUSICMENU;
					stopMusic(musicMenu, musicCurrent);
					updateMusic(&music, musicMenu, musicCurrent);
				}
				tickGO++;
			}

			/// Gamestate - WAITING FOR NEXT WAVE
			else if (gameState == NEXT) {
				renderBackdrop(w, bgCurrent, &rstateBG);
				playerUpdate(&player, w, soundPlayerShoot, &rstateBulletsP);

				tickNext++;
				if (tickNext == 60) gameState = LOAD;
			}

			sfRenderWindow_display(w);
		}
	}

	return 0;
}
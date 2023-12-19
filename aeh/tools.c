#include <math.h>
#include "tools.h"

sfTime sf_time;
sfClock* sf_clock;
sfBool isRunning = sfTrue;
sfClock* clockGame;

void initTools() {
	sf_clock = sfClock_create();
	srand((unsigned int)time(NULL));
	clockGame = sfClock_create();
}

void restartClock() { sf_time = sfClock_restart(sf_clock); }

float getDeltaTime() { return sfTime_asSeconds(sf_time); }

float getGameTime() { return sfTime_asSeconds(sfClock_getElapsedTime(clockGame)); }

float lerp(float _a, float _b, float _x) {
	return (_b - _a) * _x + _a;
}

sfBool testKeyPress(sfRenderWindow* _w, sfKeyCode _k) {
	if (_w != NULL && !sfRenderWindow_hasFocus(_w)) return sfFalse;
	if (!sfKeyboard_isKeyPressed(_k)) return sfFalse;
	return sfTrue;
}

sfBool testLClick(sfRenderWindow* _w) {
	if (_w != NULL && !sfRenderWindow_hasFocus(_w)) return sfFalse;
	if (!sfMouse_isButtonPressed(sfMouseLeft)) return sfFalse;
	return sfTrue;
}

int random(int _u) {
	return rand() % (_u + 1);
}
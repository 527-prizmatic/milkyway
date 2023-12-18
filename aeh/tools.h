#pragma once
#include <stdlib.h>
#include <string.h>
#include <stdio.h>
#include <time.h>
#include "SFML/Graphics.h"

#define TEXTURE_PATH "../Ressources/Textures/" 
#define W_WINDOW 1920
#define H_WINDOW 1080
#define TICKSPEED 20.
#define TICK 1. / TICKSPEED

#define PATH_TEXTURES "..\\Ressources\\Textures\\"
#define PATH_LEVELS "..\\Ressources\\Levels\\"

typedef enum Menu Menu;
enum Menu {
	MENU = 0,
	GAME,
	LOAD,
	CREDITS
};



/// Initializes misc tools for handling time.
void initTools();

/// Restarts the game's internal clock, for time-tracking purposes.
void restartClock();

/// \return Time elapsed since last restartClock() call
float getDeltaTime();

/// \return Time elapsed since the program's start
float getGameTime();

float lerp(float _a, float _b, float _x);

/// Checks if the user is pressing a given key. Also tests for window focus.
/// \param _w - Current window, for testing for focus
/// \param _k - Keyboard key for which to test for input
sfBool testKeyPress(sfRenderWindow* _w, sfKeyCode _k);

/// Checks if the user is left-clicking. Also tests for window focus.
/// \param _w - Current window, for testing for focus
sfBool testLClick(sfRenderWindow* _w);

int random(int _u);
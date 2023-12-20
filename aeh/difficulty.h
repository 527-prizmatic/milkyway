#pragma once
#include "tools.h"
#include "vect.h"
#include "SFML/Graphics.h"

typedef struct {
	float enemySpdMul;
	float enemyFireRateMul;
	int startingLives;
	int bonusLifeScore;
} Difficulty;

Difficulty newDifficulty(float _spd_mul, float _fire_mul, int _lives, int _bonus);
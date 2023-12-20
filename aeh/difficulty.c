#include "difficulty.h"

Difficulty newDifficulty(float _spd_mul, float _fire_mul, int _lives, int _bonus) {
	Difficulty d;
	d.enemySpdMul = _spd_mul;
	d.enemyFireRateMul = _fire_mul;
	d.startingLives = _lives;
	d.bonusLifeScore = _bonus;
	return d;
}
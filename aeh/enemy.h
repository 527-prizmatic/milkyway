#pragma once
#include "tools.h"
#include "vect.h"
#include "projectile.h"
#include "SFML/Graphics.h"

typedef struct {
	sfSprite* spr;
	sfTexture* tex;
	sfVector2f pos;
	Projectile* bullet;
	char hasFired;
} Enemy;

void initEnemy(Enemy* _e, sfTexture* _t, sfVector2f _p);

void enemyUpdate(Enemy* _e, sfRenderWindow* _w);
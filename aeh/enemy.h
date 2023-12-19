#pragma once
#include "tools.h"
#include "vect.h"
#include "projectile.h"
#include "SFML/Graphics.h"

typedef struct {
	sfSprite* spr;
	sfTexture* tex;
	sfVector2f pos;
	BulletTypes type;
	Projectile* bullet;
	char hasFired;
} Enemy;

void initEnemy(Enemy* _e, sfTexture* _t, sfVector2f _p, BulletTypes _type);

void enemyUpdate(Enemy* _e, sfRenderWindow* _w, char _dir, int _c, State _s, sfSound* _soundEnnemisShoot, sfRenderStates* _state);

void destroyBulletEnemy(Enemy* _e);
#pragma once
#include "tools.h"
#include "vect.h"
#include "render.h"
#include "SFML/Graphics.h"

typedef enum {
	PLAYER,
	ENEMY_1,
	ENEMY_2
} BulletTypes;

typedef struct {
	BulletTypes type;
	sfSprite* spr;
	sfVector2f pos;
	char dir;
} Projectile;

void initProjectile(Projectile* _p, BulletTypes _type, sfVector2f _pos, char _dir);

sfTexture* projectileTextureByType(BulletTypes _t);
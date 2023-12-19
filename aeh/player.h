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
} Player;

void initPlayer(Player* _p, sfTexture* _t);

void playerUpdate(Player* _p, sfRenderWindow* _w, sfSound* _soundPlayerShoot);

void destroyBulletPlayer(Player* _p);


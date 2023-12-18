#include "enemy.h"
#include "render.h"

#define ENEMY_SPD 50.
#define BULLET_SPD 600.

void initEnemy(Enemy* _e, sfTexture* _t, sfVector2f _p) {
	_e->spr = sfSprite_create();
	_e->tex = _t;
	_e->pos.x = _p.x;
	_e->pos.y = _p.y;
	_e->bullet = NULL;
	_e->hasFired = 0;

	sfSprite_setTexture(_e->spr, _e->tex, sfTrue);
	sfSprite_setOrigin(_e->spr, vector2f(8., 8.));
	_e->pos = vectorSnap(_e->pos, 4);
	sfSprite_setPosition(_e->spr, _e->pos);
	sfSprite_setScale(_e->spr, SCALE_SPRITES);
}

void enemyUpdate(Enemy* _e, sfRenderWindow* _w) {

	_e->pos.x += ENEMY_SPD * TICK;

	// Bullet updates
	if (_e->hasFired) {
		_e->bullet->pos.y += BULLET_SPD * TICK;
		sfSprite_setPosition(_e->bullet->spr, _e->bullet->pos);
		sfRenderWindow_drawSprite(_w, _e->bullet->spr, NULL);
		if (_e->bullet->pos.y > 1000.) {
			_e->hasFired = 0;
			free(_e->bullet);
		}
	}

	sfSprite_setPosition(_e->spr, vectorSnap(_e->pos, 4));

	sfRenderWindow_drawSprite(_w, _e->spr, NULL);
}
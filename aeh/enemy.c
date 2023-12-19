#include "enemy.h"
#include "render.h"

#define ENEMY_SPD 900.
#define BULLET_SPD 200.

void initEnemy(Enemy* _e, sfTexture* _t, sfVector2f _p, BulletTypes _type) {
	_e->spr = sfSprite_create();
	_e->tex = _t;
	_e->pos.x = _p.x;
	_e->pos.y = _p.y;
	_e->type = _type;
	_e->bullet = NULL;
	_e->hasFired = 0;

	sfSprite_setTexture(_e->spr, _e->tex, sfTrue);
	sfSprite_setOrigin(_e->spr, vector2f(0., 0.));
	_e->pos = vectorSnap(_e->pos, 4);
	sfSprite_setPosition(_e->spr, _e->pos);
	sfSprite_setScale(_e->spr, SCALE_SPRITES);
}

void enemyUpdate(Enemy* _e, sfRenderWindow* _w, char _dir, int _c, sfSound* _soundEnnemisShoot) {
	if (_dir == 0) _e->pos.x -= ENEMY_SPD / (_c + 1) * TICK;
	else if (_dir == 1) _e->pos.x += ENEMY_SPD / (_c + 1) * TICK;

	if (random(_c * _c) == 0 && !_e->hasFired) {
		_e->hasFired = 1;
		_e->bullet = malloc(sizeof(Projectile));
		if (_e->bullet == NULL) return;
		sfSound_play(_soundEnnemisShoot);
		initProjectile(_e->bullet, _e->type, vector2f(_e->pos.x + 32, _e->pos.y + 20.), 0);
	}

	// Bullet updates
	if (_e->hasFired) {
		_e->bullet->pos.y += BULLET_SPD * TICK;
		sfSprite_setPosition(_e->bullet->spr, _e->bullet->pos);
		sfRenderWindow_drawSprite(_w, _e->bullet->spr, NULL);
		if (_e->bullet->pos.y > 1000.) destroyBulletEnemy(_e);
	}

	sfSprite_setPosition(_e->spr, vectorSnap(_e->pos, 4));
	sfRenderWindow_drawSprite(_w, _e->spr, NULL);
}

void destroyBulletEnemy(Enemy* _e) {
	_e->hasFired = 0;
	free(_e->bullet);
}
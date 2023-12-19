#include "player.h"
#include "render.h"

#define PLAYER_SPD 300.
#define BULLET_SPD 600.

void initPlayer(Player* _p, sfTexture* _t) {
	_p->spr = sfSprite_create();
	_p->tex = _t;
	_p->pos.x = W_WINDOW / 2.;
	_p->pos.y = 900.;
	_p->bullet = NULL;
	_p->hasFired = 0;

	sfSprite_setTexture(_p->spr, _p->tex, sfTrue);
	sfSprite_setOrigin(_p->spr, vector2f(8., 8.));
	_p->pos = vectorSnap(_p->pos, 4);
	sfSprite_setPosition(_p->spr, _p->pos);
	sfSprite_setScale(_p->spr, SCALE_SPRITES);
}

void playerUpdate(Player* _p, sfRenderWindow* _w, sfSound* _soundPlayerShoot) {
	if (testKeyPress(_w, sfKeyQ) && !testKeyPress(_w, sfKeyD) && _p->pos.x > W_WINDOW / 8.) _p->pos.x -= PLAYER_SPD * TICK;
	else if (testKeyPress(_w, sfKeyD) && !testKeyPress(_w, sfKeyQ) && _p->pos.x < W_WINDOW * 7. / 8.) _p->pos.x += PLAYER_SPD * TICK;

	if (testKeyPress(_w, sfKeySpace) && !_p->hasFired) {

		_p->hasFired = 1;
		_p->bullet = malloc(sizeof(Projectile));
		if (_p->bullet == NULL) return;
		sfSound_play(_soundPlayerShoot);
		initProjectile(_p->bullet, PLAYER, vector2f(_p->pos.x, _p->pos.y - 20.), 0);
	
	}

	// Bullet updates
	if (_p->hasFired) {
		_p->bullet->pos.y -= BULLET_SPD * TICK;
		sfSprite_setPosition(_p->bullet->spr, _p->bullet->pos);
		sfRenderWindow_drawSprite(_w, _p->bullet->spr, NULL);
		if (_p->bullet->pos.y < 0) destroyBulletPlayer(_p);
	}
	
	sfSprite_setPosition(_p->spr, vectorSnap(_p->pos, 4));
	sfRenderWindow_drawSprite(_w, _p->spr, NULL);
}

void destroyBulletPlayer(Player* _p) {
	_p->hasFired = 0;
	free(_p->bullet);
}
#include "projectile.h"

// \param _dir - 0 for player-side, 1 for enemy-side
void initProjectile(Projectile* _p, BulletTypes _type, sfVector2f _pos, char _dir) {
	_p->type = _type;
	_p->spr = sfSprite_create();
	_p->pos = _pos;
	_p->dir = _dir;

	sfSprite_setTexture(_p->spr, projectileTextureByType(_p->type), sfFalse);
	sfSprite_setOrigin(_p->spr, vector2f(2., 5.));
	sfSprite_setScale(_p->spr, SCALE_SPRITES);
	sfSprite_setPosition(_p->spr, vectorSnap(_p->pos, 8));
}

sfTexture* projectileTextureByType(BulletTypes _t) {
	switch (_t) {
		case PLAYER: return sfTexture_createFromFile(PATH_TEXTURES"pew.png", NULL);
		case ENEMY_1: return sfTexture_createFromFile(PATH_TEXTURES"unpew.png", NULL);
	}
}
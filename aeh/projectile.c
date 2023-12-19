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
		case PLAYER: return sfTexture_createFromFile(PATH_TEXTURES"bullet_plr.png", NULL);
		case ENEMY_1: return sfTexture_createFromFile(PATH_TEXTURES"bullet_enemy_1.png", NULL);
		case ENEMY_2: return sfTexture_createFromFile(PATH_TEXTURES"bullet_enemy_2.png", NULL);
		case ENEMY_3: return sfTexture_createFromFile(PATH_TEXTURES"bullet_enemy_3.png", NULL);
		case ENEMY_4: return sfTexture_createFromFile(PATH_TEXTURES"bullet_enemy_4.png", NULL);
		case ENEMY_5: return sfTexture_createFromFile(PATH_TEXTURES"bullet_enemy_5.png", NULL);
		case ENEMY_6: return sfTexture_createFromFile(PATH_TEXTURES"bullet_enemy_6.png", NULL);
		case ENEMY_7: return sfTexture_createFromFile(PATH_TEXTURES"bullet_enemy_7.png", NULL);
		case ENEMY_8: return sfTexture_createFromFile(PATH_TEXTURES"bullet_enemy_8.png", NULL);
	}
}
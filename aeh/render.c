#include "render.h"

sfTexture* newTexture(char* _n) {
	return sfTexture_createFromFile(_n, NULL);
}

void setupSprite(sfSprite* _sprite, sfTexture* _t, sfIntRect _r, sfVector2f _o, sfVector2f _s, sfVector2f _p) {
	sfSprite_setTexture(_sprite, _t, sfTrue);
	sfSprite_setOrigin(_sprite, _o);
	if (_r.height != 0) sfSprite_setTextureRect(_sprite, _r);
	sfSprite_setScale(_sprite, _s);
	sfSprite_setPosition(_sprite, _p);
}
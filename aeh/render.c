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

void renderBackdrop(sfRenderWindow* _w, sfTexture* _t, sfRenderStates* _s) {
	sfSprite* spr = sfSprite_create();
	setupSprite(spr, _t, TEX_RECT_NULL, vector2f(0., 0.), SCALE_BACKDROPS, vector2f(0., 0.));
	sfRenderWindow_drawSprite(_w, spr, _s);
	sfSprite_destroy(spr);
}

void renderSprite(sfRenderWindow* _w, sfRenderStates* _state, sfTexture* _t, sfIntRect _r, sfVector2f _o, sfVector2f _p) {
	sfSprite* spr = sfSprite_create();
	setupSprite(spr, _t, _r, _o, SCALE_SPRITES, _p);
	sfRenderWindow_drawSprite(_w, spr, _state);
	sfSprite_destroy(spr);
}
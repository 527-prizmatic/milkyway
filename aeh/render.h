#pragma once
#include "tools.h"
#include "vect.h"
#include "SFML/Graphics.h"

#define SCALE_BACKDROPS vector2f(8., 8.)
#define SCALE_SPRITES vector2f(4., 4.)
#define TEX_RECT_NULL (sfIntRect) { 0., 0., 0., 0. }

sfTexture* newTexture(char* _n);
void setupSprite(sfSprite* _sprite, sfTexture* _t, sfIntRect _r, sfVector2f _o, sfVector2f _s, sfVector2f _p);

void renderBackdrop(sfRenderWindow* _w, sfTexture* _t, sfRenderStates* _s);
void renderSprite(sfRenderWindow* _w, sfRenderStates* _state, sfTexture* _t, sfIntRect _r, sfVector2f _o, sfVector2f _p);
#pragma once
#include "tools.h"
#include "vect.h"
#include "SFML/Graphics.h"

sfTexture* newTexture(char* _n);
void setupSprite(sfSprite* _sprite, sfTexture* _t, sfIntRect _r, sfVector2f _o, sfVector2f _s, sfVector2f _p);
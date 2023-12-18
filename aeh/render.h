#pragma once
#include "tools.h"
#include "vect.h"
#include "SFML/Graphics.h"

sfTexture* newTexture(char* _n);
void setupSprite(sfTexture* _t, sfVector2f _o, sfVector2f _s, sfVector2f _p);

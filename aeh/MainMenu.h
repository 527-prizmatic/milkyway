#pragma once
#include "tools.h"
#include "vect.h"
#include "render.h"

void initMenu(sfSprite* _spriteMainMenu, sfTexture* _textureMainMenu, sfVector2f _posMainMenu);
void updateMenu(sfRenderWindow* _window);
void displayMenu(sfRenderWindow* _window, sfSprite* _spriteMainMenu);
#pragma once
#include "tools.h"
#include "vect.h"
#include "render.h"
#include "enemy.h"

void updateMenu(sfRenderWindow* _window, sfSprite* _spritePressPlayUpdate, sfSprite* _spriteQuitUpdate, sfVector2i _mousePosMenu, State* _selectMenu, char* _cbuf, Enemy* _ebuf);
void displayMenu(sfRenderWindow* _window, sfTexture* _textureMainMenu, sfSprite* _spritePressPlay, sfSprite* _spriteQuit);
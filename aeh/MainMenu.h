#pragma once
#include "tools.h"
#include "vect.h"
#include "render.h"
#include "enemy.h"

void initMenu();
void updateMenu(sfRenderWindow* _window, sfSprite* _spritePressPlayUpdate, sfSprite* _spriteQuitUpdate, sfVector2i _mousePosMenu, Menu* _selectMenu, char* _cbuf, Enemy* _ebuf);
void displayMenu(sfRenderWindow* _window, sfTexture* _textureMainMenu, sfSprite* _spritePressPlay, sfSprite* _spriteQuit);
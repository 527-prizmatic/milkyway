#pragma once
#include "tools.h"
#include "vect.h"
#include "render.h"


void initMenu(Musique* _musicMenuInit, sfMusic* _musiqueMenuInit, sfMusic* _musiqueGameInit);
void updateMenu(sfRenderWindow* _window, sfSprite* _spritePressPlayUpdate, sfSprite* _spriteQuitUpdate, sfVector2i _mousePosMenu, Menu* _selectMenu, Musique* _musicMenuUpdate, sfMusic* _musiqueMenu, sfMusic* _musiqueGame);
void displayMenu(sfRenderWindow* _window, sfTexture* _textureMainMenu, sfSprite* _spritePressPlay, sfSprite* _spriteQuit);
#pragma once
#include "tools.h"
#include "vect.h"

void initMenuGame();
void updateMenuGame(sfRenderWindow* _window, GameDifficulty* _dificulty, State* _selectMenu, char* _flags);
void displayMenuGame(sfRenderWindow* _window, sfTexture* _textureMainMenu);
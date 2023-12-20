#pragma once
#include "tools.h"
#include "vect.h"
#include "render.h"
#include "enemy.h"

void updateMenu(sfRenderWindow* _window, State* _selectMenu, char* _flags);
void displayMenu(sfRenderWindow* _window, sfTexture* _textureMainMenu, sfText* _PressSpace);
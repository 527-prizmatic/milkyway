#pragma once
#include "tools.h"

void initMusic();
void updateMusic(MusicState* _music, sfMusic* _musicMenuUpdate, sfMusic* _musicGameUpdate);
void stopMusic(sfMusic* _musicMenuStop, sfMusic* _musicGameStop);
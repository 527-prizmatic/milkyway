#include "music.h"

void initMusic()
{

}

void updateMusic(Musique* _music, sfMusic* _musicMenuUpdate, sfMusic* _musicGameUpdate)
{
	if (*_music == MUSICMENU)
	{
		sfMusic_play(_musicMenuUpdate);
		sfMusic_setLoop(_musicMenuUpdate, sfTrue);
	}

	else if (*_music == MUSICGAME)
	{
		sfMusic_play(_musicGameUpdate);
		sfMusic_setLoop(_musicGameUpdate, sfTrue);
	}
}

void stopMusic(sfMusic* _musicMenuStop, sfMusic* _musicGameStop)
{
	sfMusic_stop(_musicMenuStop);
	sfMusic_stop(_musicGameStop);
}
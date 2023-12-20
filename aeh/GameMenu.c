#include "GameMenu.h"

void initMenuGame()
{

}

void updateMenuGame(sfRenderWindow* _window, MenuJouer* _dificulty, State* _selectMenu)
{
	sfText* selectDifficulty = sfText_create();
	sfFont* selectDifficultyFont = sfFont_createFromFile(PATH_FRONT"8-bit-hud.ttf");
	sfVector2f selectDifficultySize = { 0.8f, 0.8f };
	sfVector2f selectDifficultyPos = { 810.0f, 840.0f };
	sfText_setFont(selectDifficulty, selectDifficultyFont);
	sfText_setScale(selectDifficulty, selectDifficultySize);
	sfText_setPosition(selectDifficulty, selectDifficultyPos);

	if (testKeyPress(_window, sfKeyQ))
	{
		(*_dificulty)--;
		if (*_dificulty<0)
		{
			*_dificulty = 3;
		}
	}

	if (testKeyPress(_window, sfKeyD))
	{
		(*_dificulty)++;
		if (*_dificulty > 3)
		{
			*_dificulty = 0;
		}
	}

	switch (*_dificulty)
	{
	case RECON :
		sfText_setString(selectDifficulty, "< RECON >");
		break;
	case ASSAULT : 
		sfText_setString(selectDifficulty, "< ASSAULT >");
		break;
	case INVASION:
		sfText_setString(selectDifficulty, "< INVASION >");
		break;
	case GENOCIDE:
		sfText_setString(selectDifficulty, "< GENOCIDE >");
		break;
	}

	sfRenderWindow_drawText(_window, selectDifficulty, NULL);

	if (testKeyPress(_window, sfKeyC))
	{
		*_selectMenu = LOAD;
	}
}

void displayMenuGame(sfRenderWindow* _window, sfTexture* _textureMainMenu)
{
	renderBackdrop(_window, _textureMainMenu, NULL);
}

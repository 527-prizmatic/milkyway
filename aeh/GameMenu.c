#include "GameMenu.h"

void initMenuGame()
{

}

void updateMenuGame(sfRenderWindow* _window, GameDifficulty* _dificulty, State* _selectMenu, char* _flags) {
	sfText* selectDifficulty = sfText_create();
	sfFont* selectDifficultyFont = sfFont_createFromFile(PATH_FRONT"8-bit-hud.ttf");
	sfText_setFont(selectDifficulty, selectDifficultyFont);
	sfText_setScale(selectDifficulty, vector2f(0.8f, 0.8f));
	sfText_setPosition(selectDifficulty, vector2f(810.0f, 840.0f));

	if (testKeyPress(_window, sfKeyQ)) {
		if ((*_flags & 0b00000010) == 0) {
			(*_dificulty)--;
			if (*_dificulty < 0) *_dificulty = 3;
		}
		*_flags |= 2;
	}
	else *_flags &= 0b11111101;

	if (testKeyPress(_window, sfKeyD)) {
		if ((*_flags & 0b00000001) == 0) {
			(*_dificulty)++;
			if (*_dificulty > 3) *_dificulty = 0;
		}
		*_flags |= 1;
	}
	else *_flags &= 0b11111110;

	switch (*_dificulty) {
		case RECON: sfText_setString(selectDifficulty, "< RECON >"); break;
		case ASSAULT: sfText_setString(selectDifficulty, "< ASSAULT >"); break;
		case INVASION: sfText_setString(selectDifficulty, "< INVASION >"); break;
		case GENOCIDE: sfText_setString(selectDifficulty, "< GENOCIDE >"); break;
	}

	sfRenderWindow_drawText(_window, selectDifficulty, NULL);

	if (testKeyPress(_window, sfKeySpace)) {
		if ((*_flags & 128) == 0) *_selectMenu = LOAD;
		*_flags |= 128;
	}
	else *_flags &= 0b01111111;
}

void displayMenuGame(sfRenderWindow* _window, sfTexture* _textureMainMenu)
{
	renderBackdrop(_window, _textureMainMenu, NULL);
}

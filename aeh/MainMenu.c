#include "MainMenu.h"
#include "level.h"
#include "enemy.h"

#define NUCLEARBOMB exit(EXIT_SUCCESS);

/*sfSprite* SpritePlayMenu;
sfTexture* TexturePlayMenu;
sfVector2f posPlay = { 960.0f, 540.0f };
sfFloatRect rectPlay;

sfSprite* SpriteQuitterMenu;
sfTexture* TextureQuitterMenu;
sfVector2f posQuitter = { 700.0f, 450.0f };
sfFloatRect rectQuitter;

sfSprite* SpriteTitreMenu;
sfTexture* TextureTitreMenu;
sfVector2f posTitre = { 400.0f, 200.0f };

sfVector2i mousePosMenu;*/

void updateMenu(sfRenderWindow* _window, State* _selectMenu) {
	if (testKeyPress(_window, sfKeySpace))
	{
		*_selectMenu = CHOOSEDIFICULTY;
	}

	if (testKeyPress(_window, sfKeyEscape))
	{
		NUCLEARBOMB
	}
}

void displayMenu(sfRenderWindow* _window, sfTexture* _textureMainMenu, sfText* _PressSpace) {
	renderBackdrop(_window, _textureMainMenu, NULL);
	sfRenderWindow_drawText(_window, _PressSpace, NULL);
}

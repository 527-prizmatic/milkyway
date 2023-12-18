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

void initMenu()
{
	
}

void updateMenu(sfRenderWindow* _window, sfSprite* _spritePressPlayUpdate, sfSprite* _spriteQuitUpdate, sfVector2i _mousePosMenu, State* _selectMenu, char* _cbuf, Enemy* _ebuf) {
	sfFloatRect rectPlay = sfSprite_getGlobalBounds(_spritePressPlayUpdate);
	sfFloatRect rectQuit = sfSprite_getGlobalBounds(_spriteQuitUpdate);

	if (sfFloatRect_contains(&rectPlay, _mousePosMenu.x, _mousePosMenu.y)) {
		if (testLClick(_window)) {
			*_selectMenu = LOAD;
	//		NUCLEARBOMB
		}
	}

	if (sfFloatRect_contains(&rectQuit, _mousePosMenu.x, _mousePosMenu.y)) {
		if (testLClick(_window)) NUCLEARBOMB 
	}
}

void displayMenu(sfRenderWindow* _window, sfTexture* _textureMainMenu, sfSprite* _spritePressPlay, sfSprite* _spriteQuit) {
	renderBackdrop(_window, _textureMainMenu);
	sfRenderWindow_drawSprite(_window, _spritePressPlay, NULL);
	sfRenderWindow_drawSprite(_window, _spriteQuit, NULL);
}

#include "MainMenu.h"



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

void initMenu(sfSprite* _spriteMainMenu, sfTexture* _textureMainMenu, sfVector2f _posMainMenu)
{
	
	
	/*sfSprite_setTexture(SpriteBackgroundMenu, TextureBackgroundMenu, sfTrue);
	sfSprite_setOrigin(SpriteBackgroundMenu, vector2f(sfSprite_getGlobalBounds(SpriteBackgroundMenu).width / 2, sfSprite_getGlobalBounds(SpriteBackgroundMenu).height / 2));
	sfSprite_setPosition(SpriteBackgroundMenu, pos);*/
	setupSprite(_spriteMainMenu, _textureMainMenu, {0, 0, 0, 0}, vector2f(sfSprite_getGlobalBounds(_spriteMainMenu).width / 2, sfSprite_getGlobalBounds(_spriteMainMenu).height / 2), 1, _posMainMenu);

	SpritePlayMenu = sfSprite_create();
	TexturePlayMenu = sfTexture_createFromFile(TEXTURE_PATH"buttonStart.png", NULL);
	sfSprite_setTexture(SpritePlayMenu, TexturePlayMenu, sfTrue);
	sfSprite_setOrigin(SpritePlayMenu, vector2f(sfSprite_getGlobalBounds(SpritePlayMenu).width / 2, sfSprite_getGlobalBounds(SpritePlayMenu).height / 2));
	sfSprite_setPosition(SpritePlayMenu, posPlay);
}

void updateMenu(sfRenderWindow* _window)
{

}

void displayMenu(sfRenderWindow* _window, sfSprite* _spriteMainMenu)
{
	/*sfSprite_setOrigin(SpriteBackgroundMenu, vector2f(sfSprite_getGlobalBounds(SpriteBackgroundMenu).width / 2, sfSprite_getGlobalBounds(SpriteBackgroundMenu).height / 2));
	sfSprite_setPosition(SpriteBackgroundMenu, pos);*/
	sfRenderWindow_drawSprite(_window, _spriteMainMenu, NULL);

	/*sfSprite_setOrigin(SpritePlayMenu, vector2f(sfSprite_getGlobalBounds(SpritePlayMenu).width / 2, sfSprite_getGlobalBounds(SpritePlayMenu).height / 2));
	sfSprite_setPosition(SpritePlayMenu, posPlay);
	sfRenderWindow_drawSprite(_window, SpritePlayMenu, NULL);*/
}

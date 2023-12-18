#include "MainMenu.h"

sfSprite* SpriteBackgroundMenu;
sfTexture* TextureBackgroundMenu;
sfVector2f pos = { 400.0f, 300.0f };


void initMenu()
{
	SpriteBackgroundMenu = sfSprite_create();
	TextureBackgroundMenu = sfTexture_createFromFile(TEXTURE_PATH"backgroundMainMenu.jpg", NULL);
	sfSprite_setTexture(SpriteBackgroundMenu, TextureBackgroundMenu, sfTrue);
	sfSprite_setOrigin(SpriteBackgroundMenu, vector2f(sfSprite_getGlobalBounds(SpriteBackgroundMenu).width / 2, sfSprite_getGlobalBounds(SpriteBackgroundMenu).height / 2));
	sfSprite_setPosition(SpriteBackgroundMenu, pos);
	return SpriteBackgroundMenu;
}

void updateMenu(sfRenderWindow* _window)
{

}

void displayMenu(sfRenderWindow* _window)
{
	sfSprite_setOrigin(SpriteBackgroundMenu, vector2f(sfSprite_getGlobalBounds(SpriteBackgroundMenu).width / 2, sfSprite_getGlobalBounds(SpriteBackgroundMenu).height / 2));
	sfSprite_setPosition(SpriteBackgroundMenu, pos);
	sfRenderWindow_drawSprite(_window, SpriteBackgroundMenu, NULL);
}

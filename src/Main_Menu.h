#ifndef MAIN_MENU_H
#define MAIN_MENU_H

#include "Scene.h"

#include "UI_ButtonText.h"
#include "Interpol.h"

//
#include "Console.h"

class Main_Menu :
	public Scene
{
private:
	sf::Sprite *background;
	sf::RectangleShape *backText;

	UI::ButtonText *button_start;
	UI::ButtonText *button_exit;

	sf::Text *text;
	sf::Text *log;
public:
	void InitText();
	void InitTexture();
	void InitBackground();
	void InitButtons();
	Main_Menu(Resource_Manager *resource_manager);
	virtual ~Main_Menu();

	void update(float &dt, int &current_scene, sf::RenderWindow &window);
	void render(sf::RenderTarget &window);
};

#endif
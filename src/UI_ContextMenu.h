#ifndef UI_CONTEXTMENU_H
#define UI_CONTEXTMENU_H

#include <SFML/Graphics.hpp>
#include <SFML/Window.hpp>
#include <SFML/Audio.hpp>
#include <SFML/Network.hpp>
#include <SFML/System.hpp>

#include "UIelement.h"

#include <vector>

namespace UI
{

	class ContextMenu : public UIelement
	{
	private:
		std::vector<sf::String> *list;
		sf::Vector2f size;
		sf::Vector2f position;
		sf::Font *font;
		sf::Text *text;

		//Rectangle of one button
		sf::RectangleShape *box;

		//Show or hide Context Menu
		bool show;

		bool rightPressed;
		bool leftPressed;

		//Index of current cursor position from list
		int indexCursor;

		//Rectangle of current button cursor position
		sf::RectangleShape *chosenBox;

		//Default = -1
		int indexPressedButNotReleased;

		bool isInsideWindow(sf::RenderWindow & window);
		bool isCursorInsideMenu(sf::RenderWindow & window);
		int returnIndex(sf::RenderWindow & window);
	public:
		ContextMenu(std::vector<sf::String> list, sf::Font& font, sf::Vector2f size = sf::Vector2f(200.f, 25.f), int FontSize = 20, sf::Color color = sf::Color(150, 150, 150, 255), sf::Color TextColor = sf::Color(30, 30, 30, 255));
		ContextMenu(std::vector<sf::String> list, const char * fontPath, sf::Vector2f size = sf::Vector2f(200.f, 25.f), int FontSize = 20, sf::Color color = sf::Color(150, 150, 150, 255), sf::Color TextColor = sf::Color(30, 30, 30, 255));
		virtual ~ContextMenu();

		std::vector<sf::String> * getList();
		void setMenuColor(sf::Color color);
		void setPointedButtonColor(sf::Color color);
		void setTextColor(sf::Color color);
		void setFontSize(unsigned int size);


		/*==============================================================================**
		**ContextMenu logic, return vector index if pressed and released, else return -1**
		**==============================================================================*/
		int run(sf::RenderWindow &window);

		/*==========================================================================================================================**
		**ContextMenu logic, return vector index if pressed and released, else return -1 and write it at first element of int vector**
		**==========================================================================================================================*/
		void update(float &dt, sf::RenderWindow &window, MultiStorage &multistorage);

		void draw(sf::RenderTarget &window, sf::RenderStates states) const;
	};

}

#endif

#ifndef UI_BUTTONTEXT
#define UI_BUTTONTEXT

#include "UIelement.h"

namespace UI
{
	class ButtonText : public UIelement
	{
	private:
		sf::RectangleShape *button;
		sf::Color *DefaultColorButton;
		sf::Color *CursorColorButton;
		sf::Color *PressedColorButton;

		sf::Color *DefaultColorText;
		sf::Color *CursorColorText;
		sf::Color *PressedColorText;

		sf::Font *font;
		sf::Text *text;
		bool isPressed;
	public:
		ButtonText(sf::Font *font, sf::String Text, sf::Vector2f size, int FontSize, sf::Color DefaultButton, sf::Color CursorButton, sf::Color PressedButton, sf::Color DefaultText, sf::Color CursorText, sf::Color PressedText);
		ButtonText(const char * fontPath, sf::String Text, sf::Vector2f size, int FontSize, sf::Color DefaultButton, sf::Color CursorButton, sf::Color PressedButton, sf::Color DefaultText, sf::Color CursorText, sf::Color PressedText);
		ButtonText(sf::Font *font, sf::String Text, sf::Vector2f size, int FontSize);
		ButtonText(const char * fontPath, sf::String Text, sf::Vector2f size, int FontSize);
		virtual ~ButtonText();

		/*=================================================**
		**Button logic, return true if pressed and released**
		**=================================================*/
		bool isClicked(sf::RenderWindow &window);

		/*==================================================================================================**
		**Button logic, return true if pressed and released into first element of int vector of multistorage**
		**==================================================================================================*/
		void update(float &dt, sf::RenderWindow &window, MultiStorage &multistorage);

		void draw(sf::RenderTarget &window, sf::RenderStates states) const;
	};
}

#endif
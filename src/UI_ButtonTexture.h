#ifndef UI_BUTTONTEXTURE_H
#define UI_BUTTONTEXTURE_H

#include <SFML/Graphics.hpp>
#include <SFML/Window.hpp>
#include <SFML/Audio.hpp>
#include <SFML/Network.hpp>
#include <SFML/System.hpp>

#include "UIelement.h"

namespace UI
{

	class ButtonTexture : public UIelement
	{
	protected:
		sf::Texture *texture;
		sf::Sprite *button;
		sf::IntRect pos; //Position on texture
		sf::IntRect pos_cursor; //Position on texture when cursor is on button

		bool image; //true if text doesnt used

		bool isPressed;
	public:
		//Graphical consructors
		ButtonTexture(sf::Texture *texture, sf::IntRect Position, sf::IntRect Position_Cursor);
		ButtonTexture(sf::Texture *texture, sf::IntRect Position, sf::IntRect Position_Cursor, sf::Vector2f CoordsInWindow);

		virtual ~ButtonTexture();

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


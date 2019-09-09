#ifndef UI_WINDOW_H
#define UI_WINDOW_H

#include <SFML/Graphics.hpp>
#include <SFML/Window.hpp>
#include <SFML/Audio.hpp>
#include <SFML/Network.hpp>
#include <SFML/System.hpp>

#include "UIelement.h"

#include <vector>
#include <string>
#include <sstream>


namespace UI
{

	class Window : public UIelement
	{
	private:
		std::vector<UIelement*> *vectorUIelements;

		unsigned int size;
	public:
		Window();
		virtual ~Window();

		void pushUIelement(UIelement *uielement);
		void removeUielement(unsigned int index);

		void update(float &dt, sf::RenderWindow &window, MultiStorage &multistorage);
		void draw(sf::RenderTarget &window, sf::RenderStates states) const;
	};
}

#endif


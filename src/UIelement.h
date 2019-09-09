#ifndef UIELEMENT_H
#define UIELEMENT_H

#include <SFML/Graphics.hpp>
#include <SFML/Window.hpp>
#include <SFML/Audio.hpp>
#include <SFML/Network.hpp>
#include <SFML/System.hpp>

#include "MultiStorage.h"

class UIelement : public sf::Transformable, public sf::Drawable
{
public:
	UIelement();
	virtual ~UIelement();

	virtual void update(float &dt, sf::RenderWindow &window, MultiStorage &multistorage) = 0;
	void render(sf::RenderTarget &window, sf::RenderStates states = sf::RenderStates::Default);
};

#endif

#ifndef PLAYER_H
#define PLAYER_H

#include <SFML/Graphics.hpp>
#include <SFML/Window.hpp>
#include <SFML/Audio.hpp>
#include <SFML/Network.hpp>
#include <SFML/System.hpp>

class Player
{
private:
	sf::Texture *texture;
	///
	sf::IntRect texture_pos;
public:
	sf::Sprite *sprite; ///
	Player(sf::Texture *texture, sf::IntRect Position_on_texture, sf::Vector2f coords);
	virtual ~Player();

	void render(sf::RenderTarget &window);
};

#endif

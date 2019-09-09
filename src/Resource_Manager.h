#ifndef RESOURCE_MANAGER
#define RESOURCE_MANAGER

#include <SFML/Graphics.hpp>
#include <SFML/Window.hpp>
#include <SFML/Audio.hpp>
#include <SFML/Network.hpp>
#include <SFML/System.hpp>

#include <string>

class Resource_Manager
{
private:
	sf::Texture *texture;
	sf::SoundBuffer *sbuffer;
	sf::Music *music;
	sf::Font *font;

	sf::Font *fontSystem;
public:
	Resource_Manager();
	virtual ~Resource_Manager();

	void setTexture(const std::string path);
	void setSbuffer(const std::string path);
	void setFont(const std::string path);

	void setFontSystem(const std::string path);

	sf::Texture *getTexture();
	sf::SoundBuffer *getSbuffer();
	sf::Font *getFont();
	sf::Font *getFontSystem();
};

#endif
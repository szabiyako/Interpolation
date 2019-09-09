#include "Resource_Manager.h"



Resource_Manager::Resource_Manager() : texture(nullptr), sbuffer(nullptr), music(nullptr), font(nullptr), fontSystem(nullptr)
{
}


Resource_Manager::~Resource_Manager()
{
	if (this->texture != nullptr)
		delete this->texture;
	if (this->sbuffer != nullptr)
		delete this->sbuffer;
	if (this->music != nullptr)
		delete this->music;
	if (this->font != nullptr)
		delete this->font;
	if (this->fontSystem != nullptr)
		delete this->fontSystem;
}

void Resource_Manager::setTexture(const std::string path)
{
	if (this->texture != nullptr)
		delete this->texture;

	this->texture = new sf::Texture();
	this->texture->loadFromFile(path);
}

void Resource_Manager::setSbuffer(const std::string path)
{
	if (this->sbuffer != nullptr)
		delete this->sbuffer;

	this->sbuffer = new sf::SoundBuffer();
	this->sbuffer->loadFromFile(path);
}

void Resource_Manager::setFont(const std::string path)
{
	if (this->font != nullptr)
		delete this->font;

	this->font = new sf::Font();
	this->font->loadFromFile(path);
}

void Resource_Manager::setFontSystem(const std::string path)
{
	if (this->fontSystem != nullptr)
		delete this->fontSystem;

	this->fontSystem = new sf::Font();
	this->fontSystem->loadFromFile(path);
}

sf::Texture * Resource_Manager::getTexture()
{
	return this->texture;
}

sf::SoundBuffer * Resource_Manager::getSbuffer()
{
	return this->sbuffer;
}

sf::Font * Resource_Manager::getFont()
{
	return this->font;
}

sf::Font * Resource_Manager::getFontSystem()
{
	return this->fontSystem;
}

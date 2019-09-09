#include "Player.h"



Player::Player(sf::Texture * texture, sf::IntRect Position_on_texture, sf::Vector2f coords)
{
	this->texture = texture;
	this->texture_pos = Position_on_texture;
	this->sprite = new sf::Sprite();
	this->sprite->setTexture(*texture);
	this->sprite->setTextureRect(this->texture_pos);
	this->sprite->setPosition(coords);
}

Player::~Player()
{
	delete this->sprite;
}

void Player::render(sf::RenderTarget & window)
{
	window.draw(*this->sprite);
}

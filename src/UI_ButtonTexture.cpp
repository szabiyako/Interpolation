#include "UI_ButtonTexture.h"


UI::ButtonTexture::ButtonTexture(sf::Texture * texture, sf::IntRect Position, sf::IntRect Position_Cursor) : image(true), isPressed(false)
{
	this->texture = texture;
	this->button = new sf::Sprite();
	this->button->setTexture(*this->texture);
	this->pos = Position;
	this->pos_cursor = Position_Cursor;
	this->button->setTextureRect(this->pos);

	//For invisible button
	if (this->texture == nullptr)
		image = false;
}

UI::ButtonTexture::ButtonTexture(sf::Texture * texture, sf::IntRect Position, sf::IntRect Position_Cursor, sf::Vector2f coords) : image(true), isPressed(false)
{
	this->texture = texture;
	this->button = new sf::Sprite();
	this->button->setTexture(*this->texture);
	this->pos = Position;
	this->pos_cursor = Position_Cursor;
	this->button->setTextureRect(this->pos);

	this->setPosition(coords);

	//this->button->

	//For invisible button
	if (this->texture == nullptr)
		image = false;
}

UI::ButtonTexture::~ButtonTexture()
{
	delete this->button;
}

bool UI::ButtonTexture::isClicked(sf::RenderWindow &window)
{
	sf::RectangleShape temp(sf::Vector2f(this->button->getGlobalBounds().width, this->button->getGlobalBounds().height));

	temp.setOrigin(this->getOrigin());
	temp.setPosition(this->getPosition());
	temp.setRotation(this->getRotation());
	temp.setScale(this->getScale());

	sf::Vector2i cursor = sf::Mouse::getPosition(window);

	if (temp.getGlobalBounds().intersects(sf::FloatRect((float)cursor.x, (float)cursor.y, 1.f, 1.f)))
	{
		this->button->setTextureRect(this->pos_cursor);

		if (sf::Mouse::isButtonPressed(sf::Mouse::Left) && !this->isPressed)
			this->isPressed = true;
		else if (!sf::Mouse::isButtonPressed(sf::Mouse::Left) && this->isPressed)
		{
			this->isPressed = false;
			return true;
		}
	}
	else
	{
		this->isPressed = false;
		this->button->setTextureRect(this->pos);
	}

	return false;
}


void UI::ButtonTexture::update(float & dt, sf::RenderWindow & window, MultiStorage & multistorage)
{
	bool temp = this->isClicked(window);

	if (multistorage.getVectorInt() == nullptr)
		multistorage.CreateVectorInt();

	if (multistorage.getVectorInt()->size() < 1)
		multistorage.getVectorInt()->push_back(temp);
	else
		multistorage.getVectorInt()->at(0) = temp;
}

void UI::ButtonTexture::draw(sf::RenderTarget & window, sf::RenderStates states) const
{
	states.transform *= this->getTransform();
	if (this->image)
		window.draw(*this->button, states);
}


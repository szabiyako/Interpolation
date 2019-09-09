#include "UI_ButtonText.h"


UI::ButtonText::ButtonText(sf::Font * font, sf::String Text, sf::Vector2f size, int FontSize, sf::Color DefaultButton, sf::Color CursorButton, sf::Color PressedButton, sf::Color DefaultText, sf::Color CursorText, sf::Color PressedText)
	: font(nullptr), isPressed(false)
{
	this->button = new sf::RectangleShape(size);
	this->DefaultColorButton = new sf::Color(DefaultButton);
	this->CursorColorButton = new sf::Color(CursorButton);
	this->PressedColorButton = new sf::Color(PressedButton);

	this->DefaultColorText = new sf::Color(DefaultText);
	this->CursorColorText = new sf::Color(CursorText);
	this->PressedColorText = new sf::Color(PressedText);

	this->text = new sf::Text(Text, *font, FontSize);
}

UI::ButtonText::ButtonText(const char * fontPath, sf::String Text, sf::Vector2f size, int FontSize, sf::Color DefaultButton, sf::Color CursorButton, sf::Color PressedButton, sf::Color DefaultText, sf::Color CursorText, sf::Color PressedText)
	: isPressed(false)
{
	this->button = new sf::RectangleShape(size);
	this->DefaultColorButton = new sf::Color(DefaultButton);
	this->CursorColorButton = new sf::Color(CursorButton);
	this->PressedColorButton = new sf::Color(PressedButton);

	this->DefaultColorText = new sf::Color(DefaultText);
	this->CursorColorText = new sf::Color(CursorText);
	this->PressedColorText = new sf::Color(PressedText);

	this->font = new sf::Font();
	this->font->loadFromFile(fontPath);
	this->text = new sf::Text(Text, *this->font, FontSize);
}

UI::ButtonText::ButtonText(sf::Font * font, sf::String Text, sf::Vector2f size, int FontSize)
	: font(nullptr), isPressed(false)
{
	this->button = new sf::RectangleShape(size);
	this->DefaultColorButton = new sf::Color(40, 40, 40, 255);
	this->CursorColorButton = new sf::Color(80, 80, 80, 255);
	this->PressedColorButton = new sf::Color(160, 160,  160, 255);

	this->DefaultColorText = new sf::Color(240, 240, 240, 255);
	this->CursorColorText = new sf::Color(210, 210, 210, 255);
	this->PressedColorText = new sf::Color(210, 210, 210, 255);

	this->text = new sf::Text(Text, *font, FontSize);
}

UI::ButtonText::ButtonText(const char * fontPath, sf::String Text, sf::Vector2f size, int FontSize)
	: isPressed(false)
{
	this->button = new sf::RectangleShape(size);
	this->DefaultColorButton = new sf::Color(40, 40, 40, 255);
	this->CursorColorButton = new sf::Color(80, 80, 80, 255);
	this->PressedColorButton = new sf::Color(160, 160, 160, 255);

	this->DefaultColorText = new sf::Color(240, 240, 240, 255);
	this->CursorColorText = new sf::Color(210, 210, 210, 255);
	this->PressedColorText = new sf::Color(210, 210, 210, 255);

	this->text = new sf::Text(Text, *font, FontSize);
}

UI::ButtonText::~ButtonText()
{
	delete this->button;
	delete this->DefaultColorButton;
	delete this->CursorColorButton;
	delete this->PressedColorButton;

	delete this->DefaultColorText;
	delete this->CursorColorText;
	delete this->PressedColorText;

	delete this->text;
	if (this->font != nullptr)
		delete this->font;
}

bool UI::ButtonText::isClicked(sf::RenderWindow & window)
{
	sf::RectangleShape temp(sf::Vector2f(this->button->getGlobalBounds().width, this->button->getGlobalBounds().height));

	temp.setOrigin(this->getOrigin());
	temp.setPosition(this->getPosition());
	temp.setRotation(this->getRotation());
	temp.setScale(this->getScale());

	sf::Vector2i cursor = sf::Mouse::getPosition(window);

	if (temp.getGlobalBounds().intersects(sf::FloatRect((float)cursor.x, (float)cursor.y, 1.f, 1.f)))
	{
		if (this->isPressed)
		{
			this->button->setFillColor(*this->PressedColorButton);
			this->text->setFillColor(*this->PressedColorText);
		}
		else
		{
			this->button->setFillColor(*this->CursorColorButton);
			this->text->setFillColor(*this->CursorColorText);
		}

		if (sf::Mouse::isButtonPressed(sf::Mouse::Left) && !this->isPressed)
		{
			this->isPressed = true;
		}
		else if (!sf::Mouse::isButtonPressed(sf::Mouse::Left) && this->isPressed)
		{
			this->isPressed = false;
			return true;
		}
	}
	else
	{
		this->isPressed = false;
		this->button->setFillColor(*this->DefaultColorButton);
		this->text->setFillColor(*this->DefaultColorText);
	}

	return false;
}

void UI::ButtonText::update(float & dt, sf::RenderWindow & window, MultiStorage & multistorage)
{
	bool temp = this->isClicked(window);

	if (multistorage.getVectorInt() == nullptr)
		multistorage.CreateVectorInt();

	if (multistorage.getVectorInt()->size() < 1)
		multistorage.getVectorInt()->push_back(temp);
	else
		multistorage.getVectorInt()->at(0) = temp;
}

void UI::ButtonText::draw(sf::RenderTarget & window, sf::RenderStates states) const
{
	states.transform *= this->getTransform();
	window.draw(*this->button, states);
	window.draw(*this->text, states);
}

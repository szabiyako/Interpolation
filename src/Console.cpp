#include "Console.h"


StrList* Console::lines = nullptr;

//PRIVATE
//direction 1-Down, 0-UP
void Console::move(float & dt, bool direction)
{
	if (direction) //Down
	{
		this->background->move(sf::Vector2f(0.f, CONSOLE_MOVE_SPEED * dt));
		this->inputLine->move(sf::Vector2f(0.f, CONSOLE_MOVE_SPEED * dt));
		this->text->move(sf::Vector2f(0.f, CONSOLE_MOVE_SPEED * dt));
		if (this->inputLine->getPosition().y >= 360.f)
		{
			this->stopMoving = true;
			
			this->background->setPosition(sf::Vector2f(0.f, 360.f));
			this->inputLine->setPosition(sf::Vector2f(0.f, 360.f));
			this->text->setPosition(sf::Vector2f(0.f, 360.f));
		}
	}
	else //UP
	{
		this->background->move(sf::Vector2f(0.f, -CONSOLE_MOVE_SPEED * dt));
		this->inputLine->move(sf::Vector2f(0.f, -CONSOLE_MOVE_SPEED * dt));
		this->text->move(sf::Vector2f(0.f, -CONSOLE_MOVE_SPEED * dt));

		this->stopMoving = false;

		if (this->inputLine->getPosition().y <= 0.f)
		{
			this->stopMoving = false;
			this->visible = false;
			this->scrollPosition = 0.f;

			this->background->setPosition(sf::Vector2f(0.f, 0.f));
			this->inputLine->setPosition(sf::Vector2f(0.f, 0.f));
			this->text->setPosition(sf::Vector2f(0.f, 0.f));
		}
	}
}

//PUBLIC
Console::Console(sf::Font & font)
	: visible(false), keyPressed(false), running(false), stopMoving(false), font(nullptr), scrollPosition(0.f)
{
	this->lines = new StrList();
	this->text = new sf::Text("", font, 20);
	this->text->setFillColor(sf::Color::Green);
	this->text->setOrigin(sf::Vector2f(-2.f, 52.f));
	this->text->setPosition(sf::Vector2f(0.f, 0.f));

	this->background = new sf::RectangleShape(sf::Vector2f(1280.f, 360.f));
	this->background->setFillColor(sf::Color(10, 10, 10, 190));
	this->background->setOrigin(sf::Vector2f(0.f, 360.f));
	this->background->setPosition(sf::Vector2f(0.f, 0.f));
	this->inputLine = new sf::RectangleShape(sf::Vector2f(1280.f, 26.f));
	this->inputLine->setFillColor(sf::Color(55, 55, 55, 150));
	this->inputLine->setOrigin(sf::Vector2f(0.f, 26.f));
	this->inputLine->setPosition(sf::Vector2f(0.f, 0.f));
}

Console::Console(const char * fontPath)
	: visible(false), keyPressed(false), running(false), stopMoving(false), scrollPosition(0.f)
{
	this->font = new sf::Font();
	this->font->loadFromFile(fontPath);
	this->lines = new StrList();
	this->text = new sf::Text("", *this->font, 20);
	this->text->setFillColor(sf::Color::Green);
	this->text->setOrigin(sf::Vector2f(-2.f, 52.f));
	this->text->setPosition(sf::Vector2f(0.f, 0.f));

	this->background = new sf::RectangleShape(sf::Vector2f(1280.f, 360.f));
	this->background->setFillColor(sf::Color(10, 10, 10, 190));
	this->background->setOrigin(sf::Vector2f(0.f, 360.f));
	this->background->setPosition(sf::Vector2f(0.f, 0.f));
	this->inputLine = new sf::RectangleShape(sf::Vector2f(1280.f, 26.f));
	this->inputLine->setFillColor(sf::Color(55, 55, 55, 150));
	this->inputLine->setOrigin(sf::Vector2f(0.f, 26.f));
	this->inputLine->setPosition(sf::Vector2f(0.f, 0.f));
}

Console::~Console()
{
	delete this->lines;
	delete this->background;
	delete this->inputLine;
	delete this->text;
	if (this->font != nullptr)
		delete this->font;
}

void Console::addLine(sf::String line)
{
	lines->push(line);
	if (lines->size() > CONSOLE_MAX_LINES)
		lines->pop();
}

bool Console::run(float & dt, sf::RenderWindow & window, float & mouseWheelDelta)
{
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Tilde))
		this->keyPressed = true;
	else if (!sf::Keyboard::isKeyPressed(sf::Keyboard::Tilde) && this->keyPressed)
	{
		this->keyPressed = false;
		this->running = this->running ? false : true;
	}

	//Controls
	if (this->visible)
	{
		if (mouseWheelDelta != 0.f)
		{
			this->scrollPosition += 30000 * dt * mouseWheelDelta;
			if (this->scrollPosition < 0)
				this->scrollPosition = 0;

			int size = this->lines->size();
			if (size <= 13)
			{
				this->scrollPosition = 0;
			}
			else if (this->scrollPosition > 26.f * (size - 13))
			{
				this->scrollPosition = 26.f * (size - 13);
			}
		}
	}
	
	if (this->running)
	{
		this->visible = true;
		if (!this->stopMoving)
			this->move(dt, 1);
	}
	else if (visible)
	{
		this->move(dt, 0);
	}

	return this->visible;
}

void Console::update(float & dt, sf::RenderWindow & window, MultiStorage & multistorage)
{
	if (multistorage.getVectorInt() == nullptr)
		multistorage.CreateVectorInt();

	if (multistorage.getVectorInt()->size() < 1)
		multistorage.getVectorInt()->push_back(false);
	if (multistorage.getVectorDouble()->size() < 1)
		multistorage.getVectorDouble()->push_back(0);

	float temp = (float)multistorage.getVectorDouble()->at(0);
	multistorage.getVectorInt()->at(0) = this->run(dt, window, temp);
}

void Console::draw(sf::RenderTarget & window, sf::RenderStates states) const
{
	if (this->visible)
	{
		window.draw(*this->background, states);
		window.draw(*this->inputLine, states);
		unsigned int size = this->lines->size();
		if (size > 0)
		{
			sf::Vector2f startPosForRender = this->inputLine->getPosition();
			this->text->setPosition(startPosForRender.x, startPosForRender.y + this->scrollPosition);

			this->lines->ResetCurrent();
			for (unsigned int i = 0; i < size && this->text->getPosition().y > 0; i++, this->lines->NextCurrent())
			{
				if (this->text->getPosition().y <= startPosForRender.y)
				{
					this->text->setString(this->lines->getCurrentString());
					window.draw(*this->text, states);
				}
				this->text->move(sf::Vector2f(0.f, -26.f));
			}
		}
	}
}

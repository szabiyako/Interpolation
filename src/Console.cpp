#include "Console.h"

unsigned int Console::CONSOLE_MAX_LINES = 250;

StrList* Console::lines = nullptr;
float Console::scrollPosition = 0;

//PRIVATE
//direction 1-Down, 0-UP
void Console::move(float & dt, bool direction)
{
	if (direction) //Down
	{
		this->background->move(sf::Vector2f(0.f, CONSOLE_MOVE_SPEED * dt));
		this->inputLine->move(sf::Vector2f(0.f, CONSOLE_MOVE_SPEED * dt));
		this->text->move(sf::Vector2f(0.f, CONSOLE_MOVE_SPEED * dt));
		this->scrollBar->move(sf::Vector2f(0.f, CONSOLE_MOVE_SPEED * dt));

		if (this->inputLine->getPosition().y >= 360.f)
		{
			this->stopMoving = true;
			
			this->background->setPosition(sf::Vector2f(0.f, 360.f));
			this->inputLine->setPosition(sf::Vector2f(0.f, 360.f));
			this->text->setPosition(sf::Vector2f(0.f, 360.f));
			this->scrollBar->setPosition(sf::Vector2f(1260.f, 250.f - ((250.f * this->scrollPosition) / (26.f * (this->lines->size() - 12)))));
		}
	}
	else //UP
	{
		this->background->move(sf::Vector2f(0.f, -CONSOLE_MOVE_SPEED * dt));
		this->inputLine->move(sf::Vector2f(0.f, -CONSOLE_MOVE_SPEED * dt));
		this->text->move(sf::Vector2f(0.f, -CONSOLE_MOVE_SPEED * dt));
		this->scrollBar->move(sf::Vector2f(0.f, -CONSOLE_MOVE_SPEED * dt));

		this->stopMoving = false;

		if (this->inputLine->getPosition().y <= 0.f)
		{
			this->stopMoving = false;
			this->visible = false;
			this->scrollPosition = 0.f;

			this->scrollBar->setPosition(sf::Vector2f(1260.f, -110.f));
			this->background->setPosition(sf::Vector2f(0.f, 0.f));
			this->inputLine->setPosition(sf::Vector2f(0.f, 0.f));
			this->text->setPosition(sf::Vector2f(0.f, 0.f));
		}
	}
}

bool Console::isScrollPressd(sf::RenderWindow &window)
{
	sf::Vector2i cursor = sf::Mouse::getPosition(window);

	if (this->scrollBar->getGlobalBounds().intersects(sf::FloatRect((float)cursor.x, (float)cursor.y, 1.f, 1.f)))
	{
		if (sf::Mouse::isButtonPressed(sf::Mouse::Left) && !this->scrollPressed)
		{
			this->oldMouseY = cursor.y;
			this->oldScrollPos.x = 1260;
			this->oldScrollPos.y = this->scrollBar->getPosition().y;
			this->scrollPressed = true;
		}
	}
	if (!sf::Mouse::isButtonPressed(sf::Mouse::Left) && this->scrollPressed)
	{
		this->scrollPressed = false;
		return false;
	}
	if (this->scrollPressed)
		return true;
	return false;
}

void Console::setMaxLines(unsigned int count)
{
	unsigned int size = this->lines->size();
	if (size < count)
	{
		int delta = count - size;
		for (int i = 0; i < delta; i++)
			this->lines->pop();
	}
}

int Console::getMaxLines()
{
	return this->CONSOLE_MAX_LINES;
}

//PUBLIC
Console::Console(sf::Font & font)
	: visible(false), keyPressed(false), running(false), stopMoving(false), font(nullptr), scrollPressed(false)
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
	this->inputLine->setFillColor(sf::Color(55, 55, 55, 255));
	this->inputLine->setOrigin(sf::Vector2f(0.f, 26.f));
	this->inputLine->setPosition(sf::Vector2f(0.f, 0.f));

	this->scrollBar = new sf::RectangleShape(sf::Vector2f(20.f, 80.f));
	this->scrollBar->setFillColor(sf::Color(55, 55, 55, 150));
	this->scrollBar->setPosition(sf::Vector2f(1260.f, -110.f));
}

Console::Console(const char * fontPath)
	: visible(false), keyPressed(false), running(false), stopMoving(false), scrollPressed(false)
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

	this->scrollBar = new sf::RectangleShape(sf::Vector2f(20.f, 80.f));
	this->scrollBar->setFillColor(sf::Color(55, 55, 55, 150));
	this->scrollBar->setPosition(sf::Vector2f(1260.f, -110.f));
}

Console::~Console()
{
	delete this->lines;
	delete this->background;
	delete this->inputLine;
	delete this->scrollBar;
	delete this->text;
	if (this->font != nullptr)
		delete this->font;
}

void Console::addLine(sf::String line)
{
	//125 maxline size for UbuntuMono-R.ttf
	unsigned int SymbolsCount = 125;
	while (line.getSize() > SymbolsCount)
	{
		sf::String temp = L"";
		for (unsigned int i = 0; i < SymbolsCount; i++)
			temp += line[i];
		addLine(temp);
		line.erase(0, SymbolsCount);
	}

	lines->push(line);
	if (lines->size() > CONSOLE_MAX_LINES)
		lines->pop();
	scrollPosition = 0.f;
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
		if (this->stopMoving)
		{
			if (mouseWheelDelta != 0.f)
			{
				//OLD this->scrollPosition += 30000 * dt * mouseWheelDelta;
				this->scrollPosition += 6.81f * mouseWheelDelta;
				if (this->scrollPosition < 0.f)
					this->scrollPosition = 0.f;

				int size = this->lines->size();
				if (size <= 12)
				{
					this->scrollPosition = 0.f;
				}
				else if (this->scrollPosition > 26.f * (size - 12))
				{
					this->scrollPosition = 26.f * (size - 12);
				}
				this->scrollBar->setPosition(sf::Vector2f(1260.f, 250.f - ((250.f * this->scrollPosition) / (26.f * (size - 12)))));
			}
			else if (this->isScrollPressd(window))
			{
				int size = this->lines->size();
				if (size > 12)
				{
					sf::Vector2i cursor = sf::Mouse::getPosition(window);
					float newPos = this->oldScrollPos.y + (float)(cursor.y - this->oldMouseY);
					if (newPos > 250.f)
						newPos = 250.f;
					else if (newPos < 0.f)
						newPos = 0.f;

					this->scrollPosition = (250.f - newPos) * ((26.f * (size - 12)) / 250.f);

					this->scrollBar->setPosition(sf::Vector2f(1260.f, newPos));
				}
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
		unsigned int size = this->lines->size();
		if (size > 0)
		{
			sf::Vector2f startPosForRender = this->inputLine->getPosition();
			this->text->setPosition(startPosForRender.x, startPosForRender.y + this->scrollPosition);
			startPosForRender.y += 26.f;

			this->lines->ResetCurrent();
			for (unsigned int i = 0; i < size && this->text->getPosition().y > 0.f; i++, this->lines->NextCurrent())
			{
				if (this->text->getPosition().y <= startPosForRender.y)
				{
					this->text->setString(this->lines->getCurrentString());
					window.draw(*this->text, states);
				}
				this->text->move(sf::Vector2f(0.f, -26.f));
			}
		}
		window.draw(*this->inputLine, states);
		window.draw(*this->scrollBar, states);
	}
}

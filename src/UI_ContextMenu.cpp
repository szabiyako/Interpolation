#include "UI_ContextMenu.h"


//PRIVATE
bool UI::ContextMenu::isInsideWindow(sf::RenderWindow & window)
{
	sf::Vector2i cursor = sf::Mouse::getPosition(window);

	sf::Vector2u size = window.getSize();

	if (cursor.x >= 0 && cursor.x <= (int)size.x &&
		cursor.y >= 0 && cursor.y <= (int)size.y)
		return true;
	return false;
}

bool UI::ContextMenu::isCursorInsideMenu(sf::RenderWindow & window)
{
	if (!this->show)
		return false;
	sf::Vector2i cursor = sf::Mouse::getPosition(window);
	sf::IntRect Menu;

	unsigned int size = this->list->size();

	int h = size * (int)this->size.y + (size - 1);

	Menu.left = (int)this->position.x;
	Menu.top = (int)(this->position.y - h);
	Menu.width = (int)this->size.x;
	Menu.height = h;

	if (cursor.x >= Menu.left && cursor.x <= Menu.width + Menu.left &&
		cursor.y >= Menu.top && cursor.y <= Menu.height + Menu.top)
		return true;
	return false;
}

int UI::ContextMenu::returnIndex(sf::RenderWindow & window)
{
	if (!this->show)
		return -1;
	sf::Vector2i cursor = sf::Mouse::getPosition(window);
	sf::IntRect Menu;

	unsigned int size = this->list->size();

	for (unsigned int i = 0; i < size; i++)
	{
		int h = (i + 1) * (int)this->size.y + ((i + 1) - 1);

		Menu.left = (int)this->position.x;
		Menu.top = (int)this->position.y - h;
		Menu.width = (int)this->size.x;
		Menu.height = h;

		if (cursor.x >= Menu.left && cursor.x <= Menu.width + Menu.left &&
			cursor.y >= Menu.top && cursor.y <= Menu.height + Menu.top)
			return i;
	}
	return -1;
}

//PUBLIC

UI::ContextMenu::ContextMenu(std::vector<sf::String> list, sf::Font &font, sf::Vector2f size, int FontSize, sf::Color color, sf::Color TextColor)
	: show(false), rightPressed(false), leftPressed(false), indexCursor(-1), position(0.f, 0.f), font(nullptr), indexPressedButNotReleased(-1)
{
	this->list = new std::vector<sf::String>(list);
	this->text = new sf::Text("", font, FontSize);
	this->text->setFillColor(TextColor);
	this->size = size;
	this->box = new sf::RectangleShape;
	this->box->setFillColor(color);
	this->box->setSize(size);
	this->box->setOrigin(sf::Vector2f(0, size.y));

	this->chosenBox = new sf::RectangleShape(*this->box);
	this->chosenBox->setFillColor(sf::Color(0, 0, 0, 105));
}

UI::ContextMenu::ContextMenu(std::vector<sf::String> list, const char * fontPath, sf::Vector2f size, int FontSize, sf::Color color, sf::Color TextColor)
	: show(false), rightPressed(false), leftPressed(false), indexCursor(-1), position(0.f, 0.f), indexPressedButNotReleased(-1)
{
	this->list = new std::vector<sf::String>(list);
	this->font = new sf::Font();
	this->font->loadFromFile(fontPath);
	this->text = new sf::Text("", *this->font, FontSize);
	this->text->setFillColor(TextColor);
	this->size = size;
	this->box = new sf::RectangleShape;
	this->box->setFillColor(color);
	this->box->setSize(size);
	this->box->setOrigin(sf::Vector2f(0, size.y));

	this->chosenBox = new sf::RectangleShape(*this->box);
	this->chosenBox->setFillColor(sf::Color(0, 0, 0, 105));
}

UI::ContextMenu::~ContextMenu()
{
	delete this->chosenBox;
	delete this->box;
	delete this->text;
	delete this->list;
	if (this->font != nullptr)
		delete this->font;
}

std::vector<sf::String>* UI::ContextMenu::getList()
{
	return this->list;
}

void UI::ContextMenu::setMenuColor(sf::Color color)
{
	this->box->setFillColor(color);
}

void UI::ContextMenu::setPointedButtonColor(sf::Color color)
{
	this->chosenBox->setFillColor(color);
}

void UI::ContextMenu::setTextColor(sf::Color color)
{
	this->text->setFillColor(color);
}

void UI::ContextMenu::setFontSize(unsigned int size)
{
	this->text->setCharacterSize(size);
}

int UI::ContextMenu::run(sf::RenderWindow & window)
{
	if (this->isInsideWindow(window))
	{
		sf::Vector2i cursor = sf::Mouse::getPosition(window);

		if (sf::Mouse::isButtonPressed(sf::Mouse::Right))
		{
			//Return pressed index
			if (this->leftPressed && !sf::Mouse::isButtonPressed(sf::Mouse::Left))
			{
				int index = this->returnIndex(window);
				this->show = false;
				this->leftPressed = false;

				return index;
			}
			//End return

			if ((!this->show || !this->isCursorInsideMenu(window)) && !this->rightPressed)
			{
				this->show = true;
				this->position.x = (float)cursor.x;
				this->position.y = (float)cursor.y;
			}
			this->rightPressed = true;
		}
		else if (sf::Mouse::isButtonPressed(sf::Mouse::Left))
		{
			this->rightPressed = false;
			if (!this->isCursorInsideMenu(window) && !this->leftPressed)
			{
				this->show = false;
			}
			else
			{
				this->leftPressed = true;
			}
		}
		else
		{
			//Return pressed index
			if (this->leftPressed)
			{
				int index = this->returnIndex(window);
				this->show = false;
				this->leftPressed = false;

				return index;
			}
			//End return
			
			this->rightPressed = false;
		}

		if (this->isCursorInsideMenu(window))
		{
			this->indexCursor = this->returnIndex(window);
		}
		else
			this->indexCursor = -1;

		//default return -1
		return -1;
	}

	//default return -1
	return -1;
}

void UI::ContextMenu::update(float & dt, sf::RenderWindow & window, MultiStorage & multistorage)
{
	int temp = this->run(window);

	if (multistorage.getVectorInt() == nullptr)
		multistorage.CreateVectorInt();

	if (multistorage.getVectorInt()->size() < 1)
		multistorage.getVectorInt()->push_back(temp);
	else
		multistorage.getVectorInt()->at(0) = temp;
}

void UI::ContextMenu::draw(sf::RenderTarget &window, sf::RenderStates states) const
{
	if (this->show)
	{
		unsigned int size = this->list->size();
		this->box->setPosition(position);
		for (unsigned int i = 0; i < size; i++)
		{
			window.draw(*this->box);
			this->box->move(0.f, -(float)(this->size.y + 1));

			this->text->setString(this->list->at(i));
			this->text->setPosition(this->box->getPosition());
			window.draw(*this->text);
			if (this->indexCursor == i)
			{
				this->chosenBox->setPosition(this->box->getPosition());
				this->chosenBox->move(0.f, (float)(this->size.y + 1));
				window.draw(*this->chosenBox);
			}
		}
	}
}

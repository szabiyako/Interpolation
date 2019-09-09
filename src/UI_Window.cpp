#include "UI_Window.h"



UI::Window::Window() : size(0)
{
	this->vectorUIelements = new std::vector<UIelement*>();
}


UI::Window::~Window()
{
	delete this->vectorUIelements;
}

void UI::Window::pushUIelement(UIelement * uielement)
{
	this->vectorUIelements->push_back(uielement);
}

void UI::Window::removeUielement(unsigned int index)
{
	this->vectorUIelements->erase(this->vectorUIelements->begin() + index);
}

void UI::Window::update(float & dt, sf::RenderWindow & window, MultiStorage & multistorage)
{
	//Логика окна а также его перемещения внутри основного Window

	for (unsigned int i = 0; i < this->size; i++)
		this->vectorUIelements->at(i)->update(dt, window, multistorage);
}

void UI::Window::draw(sf::RenderTarget &window, sf::RenderStates states) const
{
	for (unsigned int i = 0; i < this->size; i++)
		this->vectorUIelements->at(i)->render(window);
}

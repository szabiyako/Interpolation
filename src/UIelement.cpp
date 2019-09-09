#include "UIelement.h"



UIelement::UIelement()
{
}


UIelement::~UIelement()
{
}

void UIelement::render(sf::RenderTarget & window, sf::RenderStates states)
{
	this->draw(window, states);
}

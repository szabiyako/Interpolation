#include "FPS.h"



FPS::FPS(const char * font) : fps(0), fpsSum(0), fpsCount(0), updatefps(0.25), upd(0), fromFont(false)
{
	this->font = new sf::Font();
	this->font->loadFromFile(font);
	this->text = new sf::Text("", *this->font, 10);
	this->backround = new sf::RectangleShape(sf::Vector2f(50.f, 13.f));
	this->backround->setFillColor(sf::Color(0, 0, 0, 150));
	this->backround->setPosition(sf::Vector2f(0.f, 0.f));
}

FPS::FPS(sf::Font & font) : fps(0), fpsSum(0), fpsCount(0), updatefps(0.25), upd(0), fromFont(true)
{
	this->text = new sf::Text("", font, 10);
	this->backround = new sf::RectangleShape(sf::Vector2f(50.f, 13.f));
	this->backround->setFillColor(sf::Color(0, 0, 0, 150));
	this->backround->setPosition(sf::Vector2f(0.f, 0.f));
}

FPS::~FPS()
{
	delete this->backround;
	delete this->text;
	if (fromFont)
		delete this->font;
}

void FPS::setFps(float & dt)
{
	this->fps = (int)(1 / dt);
}

void FPS::setFpsSmooth(float & dt)
{
	this->upd += dt;

	this->fpsSum += (int)(1 / dt);
	this->fpsCount++;

	if (upd > updatefps)
	{
		this->fps = this->fpsSum / this->fpsCount;
		this->upd = 0;
		this->fpsSum = 0;
		this->fpsCount = 0;
	}
}

void FPS::render(sf::RenderTarget & window)
{
	window.draw(*this->backround);
	this->text->setString((std::string)("FPS " + std::to_string(fps)));
	window.draw(*this->text);
}

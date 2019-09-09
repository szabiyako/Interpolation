#ifndef CONSOLE_H
#define CONSOLE_H

#define CONSOLE_MOVE_SPEED 1800.f
#define CONSOLE_MAX_LINES 13

#include "UIelement.h"

#include "StrList.h"

class Console : public UIelement
{
private:
	bool visible;
	bool keyPressed;
	bool running;
	bool stopMoving;
	static StrList *lines;
	sf::RectangleShape *background;
	sf::RectangleShape *inputLine;
	sf::Font *font;
	sf::Text *text;

	

	//direction 1-Down, 0-UP
	void move(float &dt, bool direction);
public:
	Console(sf::Font& font);
	Console(const char * fontPath);
	virtual ~Console();

	static void addLine(sf::String line);

	/*==========================================================**
	** Console logic, return true if opened and false if closed **
	**==========================================================*/
	bool run(float &dt, sf::RenderWindow &window);

	void update(float &dt, sf::RenderWindow &window, MultiStorage &multistorage);

	void draw(sf::RenderTarget &window, sf::RenderStates states) const;

	void render(sf::RenderTarget &window, sf::RenderStates states = sf::RenderStates::Default);
};

#endif CONSOLE_H


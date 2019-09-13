#ifndef CONSOLE_H
#define CONSOLE_H

#define CONSOLE_MOVE_SPEED 1800.f

#include "UIelement.h"

#include "StrList.h"

class Console : public UIelement
{
private:
	//Visual part
	bool visible;
	bool keyPressed;
	bool running;
	bool stopMoving;
	static StrList *lines;
	sf::RectangleShape *background;
	sf::RectangleShape *inputLine;
	sf::Font *font;
	sf::Text *text;
	sf::RectangleShape *scrollBar;
	
	//Control part
	static unsigned int CONSOLE_MAX_LINES;

	static float scrollPosition;
	bool scrollPressed;
	int oldMouseY;
	sf::Vector2f oldScrollPos;
	

	//direction 1-Down, 0-UP
	void move(float &dt, bool direction);

	//Return true if scrollBar is pressed else return false
	bool isScrollPressd(sf::RenderWindow &window);
	
	//CONSOLE COMMANDS
	void setMaxLines(unsigned int count);
	int getMaxLines();
public:
	Console(sf::Font& font);
	Console(const char * fontPath);
	virtual ~Console();

	static void addLine(sf::String line);

	/*==========================================================**
	** Console logic, return true if opened and false if closed **
	**==========================================================*/
	bool run(float &dt, sf::RenderWindow &window, float &mouseWheelDelta);

	/*=========================================================================================================**
	**Console logic, return true if opened and false if closed into first element of int vector of multistorage**
	**also cathing mouseWheelDelta from first element of double vector of multistorage                         **
	**=========================================================================================================*/
	void update(float &dt, sf::RenderWindow &window, MultiStorage &multistorage);

	void draw(sf::RenderTarget &window, sf::RenderStates states) const;
};

#endif


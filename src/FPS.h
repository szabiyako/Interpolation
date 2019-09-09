#ifndef FPS_H
#define FPS_H

#include "DeltaTime.h"
#include <string>

class FPS
{
protected:
	sf::Font *font;
	sf::Text *text;
	sf::RectangleShape *backround;
	int fps;

	int fpsSum;
	int fpsCount;
	float updatefps;
	float upd;

	bool fromFont;
public:
	FPS(const char *font);
	FPS(sf::Font &font);
	virtual ~FPS();

	void setFps(float &dt);
	void setFpsSmooth(float &dt);
	void render(sf::RenderTarget &window);
};

#endif

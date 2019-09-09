#ifndef DELTATIME_H
#define DELTATIME_H

#include <SFML/Graphics.hpp>

class DeltaTime
{
protected:
	sf::Clock *clock;
	sf::Time *dt;
public:
	DeltaTime();
	virtual ~DeltaTime();

	void clock_start();
	void save_restart();
	float get();
};

#endif

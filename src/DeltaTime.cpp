#include "DeltaTime.h"



DeltaTime::DeltaTime()
{
	this->clock = new sf::Clock();
	this->dt = new sf::Time();
	*dt = clock->restart();
}


DeltaTime::~DeltaTime()
{
	delete this->clock;
	delete this->dt;
}

void DeltaTime::clock_start()
{
	*dt = clock->restart();
}

void DeltaTime::save_restart()
{
	*dt = clock->restart();
}

float DeltaTime::get()
{
	return dt->asSeconds();
}

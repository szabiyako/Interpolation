#ifndef SCENE_H
#define SCENE_H

#include <SFML/Graphics.hpp>
#include <SFML/Window.hpp>
#include <SFML/Audio.hpp>
#include <SFML/Network.hpp>
#include <SFML/System.hpp>

#include "Resource_Manager.h"

class Scene
{
protected:
	Resource_Manager *resource_manager;
private:
	bool resource_manager_is_used;
public:
	Scene();
	Scene(Resource_Manager *resource_manager);
	virtual ~Scene();

	virtual void update(float &dt, int &current_scene, sf::RenderWindow &window) = 0;
	virtual void render(sf::RenderTarget &window) = 0;
};

#endif


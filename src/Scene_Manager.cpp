#include "Scene_Manager.h"



void Scene_Manager::changeScene()
{
	switch (this->current_scene)
	{
	case 0: this->scene = new Main_Menu(this->resource_manager); break;
	}
}

Scene_Manager::Scene_Manager(sf::RenderWindow *window, Resource_Manager *resource_manager) : scene_count(2),
current_scene(0), current_scene_check(0), close(false), resource_manager(resource_manager)
{
	this->window = window;
	this->scene = new Main_Menu(this->resource_manager);
}


Scene_Manager::~Scene_Manager()
{
	if (this->scene != nullptr && !this->close)
		delete this->scene;
}

void Scene_Manager::update(float & dt)
{
	if (this->current_scene != this->current_scene_check)
	{
		if (this->scene != nullptr)
			delete this->scene;
		if (this->current_scene >= 0 && this->current_scene < this->scene_count)
		{
			this->current_scene_check = this->current_scene;
			this->changeScene();
		}
		else
			close = true;
	}
	else
		this->scene->update(dt, this->current_scene, *this->window);

	if (close)
		this->window->close();
}

void Scene_Manager::render()
{
	if (!close)
		this->scene->render(*this->window);
}

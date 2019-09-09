#ifndef SCENE_MANAGER_H
#define SCENE_MANAGER_H

#include "Scene.h"
#include "Resource_Manager.h"

/*=================================================**
**                   Scenes                        **
**=================================================*/
#include "Main_Menu.h"
/*=================================================*/

class Scene_Manager
{
private:
	sf::RenderWindow *window;
	Resource_Manager *resource_manager;

	Scene *scene;
	int scene_count;
	int current_scene; //index of current scene
	int current_scene_check; //index of scene at previous frame

	bool close; //if true, close the window

	//Change Scene function
	void changeScene();
public:
	Scene_Manager(sf::RenderWindow *window, Resource_Manager *resource_manager);
	virtual ~Scene_Manager();

	void update(float &dt);
	void render();
};

#endif


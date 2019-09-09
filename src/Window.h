#ifndef WINDOW_H
#define WINDOW_H

#include "Scene_Manager.h"
#include "Resource_Manager.h"

//For window settings from file
#include <fstream>
#include <string>

#include "DeltaTime.h"
#include "FPS.h"
#include "Console.h"

//For fps render, to turn off comment out line below
#define FPS_RENDER_ON

//To show console comment out line below
#pragma comment(linker, "/SUBSYSTEM:windows /ENTRY:mainCRTStartup")

class Window
{
private:
	//Vars
	sf::RenderWindow *window;
	sf::Event *sfEvent;
	sf::Clock *dtClock;
	float dt;
	FPS *fps;
	Scene_Manager *scene_manager;
	Resource_Manager *resource_manager;
	Console *console;
	sf::RenderStates *render_states; //Currently doesnt work, need to connect it whith scenes

	//Initialazers
	void InitWindow();
	void InitSFMLevent();
	void InitClock();
	void InitFPS();
	void InitRender_States();
	void InitScene_Manager();
	void InitResource_Manager();
	void InitConsole();
public:
	Window();
	virtual ~Window();

	//Functions
	void updateDt();
	void updateSFMLevents();
	void update();
	void render();
	void run();
};

#endif

#include "Window.h"

//Initialazers
void Window::InitWindow()
{
	std::ifstream input("configs/window.ini");

	std::string title = "Default Window";
	sf::VideoMode window_bounds(1280, 720);
	unsigned short int framerate_limit = 120;
	bool vertical_sync_enabled = false;

	if (input.is_open())
	{
		std::getline(input, title);
		input >> window_bounds.width >> window_bounds.height;
		input >> framerate_limit >> vertical_sync_enabled;
	}

	input.close();

	this->window = new sf::RenderWindow(window_bounds, title);
	this->window->setFramerateLimit(framerate_limit);
	this->window->setVerticalSyncEnabled(vertical_sync_enabled);
}

void Window::InitSFMLevent()
{
	this->sfEvent = new sf::Event();
}

void Window::InitClock()
{
	this->dtClock = new sf::Clock();
}

void Window::InitFPS()
{
	this->fps = new FPS(*this->resource_manager->getFontSystem());
}

void Window::InitRender_States()
{
	this->render_states = new sf::RenderStates(sf::RenderStates::Default);
}

void Window::InitScene_Manager()
{
	this->scene_manager = new Scene_Manager(this->window, this->resource_manager);
}

void Window::InitResource_Manager()
{
	this->resource_manager = new Resource_Manager();
	this->resource_manager->setFontSystem("resources/fonts/arial.ttf");
}

void Window::InitConsole()
{
	this->console = new Console(*this->resource_manager->getFontSystem());
}

//Constructor/destructor
Window::Window() : dt(0)
{
	this->InitWindow();
	this->InitSFMLevent();
	this->InitClock();
	this->InitResource_Manager();
	this->InitFPS();
	this->InitConsole();
	this->InitRender_States();
	this->InitScene_Manager();
}

//Functions
Window::~Window()
{
	delete this->window;
	delete this->dtClock;
	delete this->fps;
	delete this->console;
	delete this->sfEvent;
	delete this->scene_manager;
	delete this->render_states;
	delete this->resource_manager;
}

void Window::updateDt()
{
	this->dt = dtClock->restart().asSeconds();
}

void Window::updateSFMLevents()
{
	while (this->window->pollEvent(*this->sfEvent))
	{
		if (this->sfEvent->type == sf::Event::Closed)
			this->window->close();
		else if (this->sfEvent->type == sf::Event::Resized)
		{
			this->window->setSize(sf::Vector2u(1280, 720));
		}
	}
}

void Window::update()
{
	this->updateSFMLevents();
	if (!this->console->run(this->dt, *this->window))
		this->scene_manager->update(this->dt);
	this->fps->setFpsSmooth(this->dt);
}

void Window::render()
{
	this->window->clear();

	//Render BEGIN

	this->scene_manager->render();

	this->console->render(*this->window);

	#ifdef FPS_RENDER_ON
		this->fps->render(*this->window);
	#endif
	//Render END

	this->window->display();
}

void Window::run()
{
	while (this->window->isOpen())
	{
		this->updateDt();
		this->update();
		this->render();
	}
}

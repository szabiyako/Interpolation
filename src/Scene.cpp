#include "Scene.h"



Scene::Scene() : resource_manager_is_used(false)
{
	this->resource_manager = nullptr;
}

Scene::Scene(Resource_Manager * resource_manager) : resource_manager_is_used(true)
{
	this->resource_manager = resource_manager;
}


Scene::~Scene()
{
	if (this->resource_manager != nullptr && !resource_manager_is_used)
		delete this->resource_manager;
}

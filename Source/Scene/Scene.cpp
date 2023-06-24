#include "Scene.h"
#include "Graphics/Drawable/Screen.h"

Scene::~Scene() = default;

const Screen& Scene::GetScreen(void) const
{
	return *screen_;
}

const std::string& Scene::GetName(void) const
{
	return name_;
}

Scene::Scene(const std::string& name) :
	screen_(Screen::Create()), name_(name)
{
}

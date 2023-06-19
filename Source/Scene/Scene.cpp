#include "Scene.h"
#include "Graphics/Drawable/Screen.h"

Scene::~Scene() = default;

const Screen& Scene::GetScreen(void) const
{
	return *screen_;
}

Scene::Scene() :
	screen_(Screen::Create())
{
}

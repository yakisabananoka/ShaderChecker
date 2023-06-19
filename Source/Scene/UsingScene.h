#pragma once
#include <memory>

class Scene;

template<typename T>
using ScenePtrTemplate = std::unique_ptr<T>;
using ScenePtr = ScenePtrTemplate<Scene>;

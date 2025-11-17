#pragma once
#include "pch.h"
class Scene;

extern sf::RenderWindow window;
extern sf::View playerView;
extern sf::View defaultView;

extern std::unique_ptr<Scene> scene;

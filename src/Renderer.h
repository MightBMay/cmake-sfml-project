#pragma once
#include "pch.h"

class Renderer {

protected:
	sf::Drawable* _drawable;

public:
	virtual ~Renderer() = default;

	virtual void draw(sf::RenderTarget& target, sf::RenderStates states) const = 0;

	


};
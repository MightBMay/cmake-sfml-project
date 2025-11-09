#pragma once
#include "pch.h"


class CircleRenderer : public Renderer {

private:

	std::unique_ptr<sf::CircleShape> _circleShape;

public:
	CircleRenderer(float radius =0, float vertexCount = 32) {
		_circleShape = std::make_unique<sf::CircleShape>(radius, vertexCount);
		_drawable = _circleShape.get();
		
			
	}

	void SetRadius(float newRadius) {
		_circleShape->setRadius(newRadius);
	}

	virtual void draw(sf::RenderTarget& target, sf::RenderStates states) const override {

		target.draw(*_drawable, states);
	}
};
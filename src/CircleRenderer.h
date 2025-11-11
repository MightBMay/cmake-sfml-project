#pragma once
#include "pch.h"


class CircleRenderer : public Renderer {

private:

	std::unique_ptr<sf::CircleShape> _circleShape;




public:

	static std::unique_ptr<Renderer> Create(const nlohmann::json& data) {

		int radius = 0, vertexCount = 0;
		if (data.contains("radius")) radius = data["radius"];
			
		if (data.contains("vertexCount")) vertexCount = data["vertexCount"];

		return std::make_unique<CircleRenderer>(radius, vertexCount);
	}

	CircleRenderer(float radius =0, float vertexCount = 32) : Renderer() {
		_circleShape = std::make_unique<sf::CircleShape>(radius, vertexCount);
		_drawable = _circleShape.get();
		
	}

	virtual sf::FloatRect GetGlobalBounds() const override {
		// since gameobject has its own transform and we just multiply the shape transform by that to position it on screen, we gotta do this to reflect its position.
		return _transform->GetSFTransform().transformRect(_circleShape->getGlobalBounds());
	}




	void SetRadius(float newRadius) {
		_circleShape->setRadius(newRadius);
	}

	virtual void draw(sf::RenderTarget& target, sf::RenderStates states) const override {
		target.draw(*_drawable, states);
	}


private:
	inline static bool registered = [] {
		RendererFactory::instance().Register("circle", &CircleRenderer::Create);
		return true;
		}();
};
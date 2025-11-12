#pragma once
#include "pch.h"

class RectRenderer : public Renderer {
private:
	std::unique_ptr<sf::RectangleShape> _rectShape;
	float _width = 32;
	float _height = 32;


public:
	static std::unique_ptr<Renderer> Create(const nlohmann::json& data) {
		float width = 0, height = 0;
		if (data.contains("width")) width = data["width"];
		if (data.contains("height")) height = data["height"];

		return std::make_unique<RectRenderer>(sf::Vector2f( width, height ));
	}

	RectRenderer(sf::Vector2f size) {
		_rectShape = std::make_unique<sf::RectangleShape>(size);
		_drawable = _rectShape.get();
	}

	virtual void getImGuiParams(nlohmann::json& data) override {
		if (!data.contains("width"))       data["width"] = _width;
		if (!data.contains("height"))  data["height"] = _height;

		float width = data.value("width", _width);
		float height = data.value("height", _height);

		if (ImGui::InputFloat("width", &width)) data["width"] = width;
		if (ImGui::InputFloat("height", &height)) data["height"] = height;
	}

	virtual sf::FloatRect GetGlobalBounds() const override {
		return _transform->GetSFTransform().transformRect(_rectShape->getGlobalBounds());
	}


private:
	inline static bool registered = [] {
		RendererFactory::instance().Register("rectangle", &RectRenderer::Create);
		return true;
		}();

};
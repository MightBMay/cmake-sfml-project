#pragma once
#include "pch.h"



#if  IN_EDITOR


#endif //  IN_EDITOR

#define missing "../assets/sprites/missingTexture.png"

class SpriteRenderer : public Renderer {


private:
	std::unique_ptr<sf::Sprite> _sprite;
	std::unique_ptr<sf::Texture>_texture;
	std::string _spritePath = "../assets/sprites/missingTexture.png";

public:
	
	static std::unique_ptr<Renderer> Create(const nlohmann::json& data) {
		std::string spritePath = data.value("spritePath", missing);
		sf::Color colour = data.value("colour", sf::Color::White);
		sf::IntRect rect = data.value("textureRect", sf::IntRect());
		bool repeatTexture = data.value("isRepeated", false);


		return std::make_unique<SpriteRenderer>(spritePath, rect, colour, repeatTexture);
	}


	SpriteRenderer(std::string& spritePath,sf::IntRect textureRect, sf::Color colour, bool repeatTexture) {
		_spritePath = spritePath;

		sf::Texture texture;
		_texture = std::make_unique<sf::Texture>();

		if (_texture->loadFromFile(spritePath) == false)
		{
			_texture->loadFromFile(missing);
		}

		
		_texture->setRepeated(repeatTexture);
		_sprite = std::make_unique<sf::Sprite>(*_texture);
		_sprite->setTextureRect(textureRect);

		sf::Vector2f origin = { textureRect.size.x / 2.0f, textureRect.size.y / 2.0f };

		_sprite->setOrigin(origin);

		_drawable = _sprite.get();


		_sprite->setColor(colour);
		

	}

	virtual void SetOrigin() {
		sf::IntRect rect = _sprite->getTextureRect();
		_sprite->setOrigin(sf::Vector2f(rect.size.x / 2.0f, rect.size.y / 2.0f ));
	}
	virtual void SetOrigin(sf::Vector2i& newOrigin) {
		_sprite->setOrigin(sf::Vector2f(newOrigin.x, newOrigin.y));
	}

	virtual sf::FloatRect GetGlobalBounds() const override {
		return _transform->GetSFTransform().transformRect(_sprite->getGlobalBounds());
	}

#if IN_EDITOR

	virtual void getImGuiParams(nlohmann::json& data) override {
		std::string curPath = data.value("spritePath", _spritePath);

		std::array<char, 512> pathBuffer{};
		std::copy_n(curPath.begin(), std::min(curPath.size(), pathBuffer.size() - 1), pathBuffer.begin());


		if (ImGui::InputText("Sprite Path", pathBuffer.data(), pathBuffer.size())) {
			std::string newPath = pathBuffer.data();


			sf::Texture temp;
			if (temp.loadFromFile(newPath)) {

				_texture->swap(temp);
				_sprite->setTexture(*_texture, true);

				_spritePath = newPath;
				data["spritePath"] = newPath;
			}
			
		}




		bool repeatTexture = _texture->isRepeated();
		if (ImGui::Checkbox("Repeat Texture", &repeatTexture)) {
			_texture->setRepeated(repeatTexture);
		}


		sf::IntRect raw = _sprite->getTextureRect();
		int rectValues[4] = { raw.position.x, raw.position.y, raw.size.x, raw.size.y };

		if (!data.contains("textureRect")) {
			data["textureRect"] = sf::IntRect(
				{ rectValues[0], rectValues[1] },
				{ rectValues[2], rectValues[3] }
			);
		}


		

		if (ImGui::InputInt4("Texture Rect", rectValues)) {
			auto newRect = sf::IntRect(
				{ rectValues[0], rectValues[1] },
				{ rectValues[2] , rectValues[3] }
			);

			data["textureRect"] = newRect;
		}





		//colour
		if (!data.contains("colour")) data["colour"] = { 255,255,255,255 };
		float colourRaw[4] = {255,255,255,255};
		if (ImGui::InputFloat4("Colour", colourRaw)) {
			data["colour"] = sf::Color(colourRaw[0], colourRaw[1], colourRaw[2], colourRaw[3]);

			_sprite->setColor(
				sf::Color(colourRaw[0], colourRaw[1], colourRaw[2], colourRaw[3])
			);
		}







	}

	virtual void getInspectorParams() override {

		ImGui::SeparatorText("Sprite Renderer");

		sf::Color curCol = _sprite->getColor();
		float colourRaw[4] = { curCol.r, curCol.g, curCol.b, curCol.a };
		if (ImGui::InputFloat4("Colour", colourRaw)) {
			_sprite->setColor(
				sf::Color(colourRaw[0], colourRaw[1], colourRaw[2], colourRaw[3])
			);
		}


		std::string curPath = _spritePath;

		std::array<char, 512> pathBuffer{};
		std::copy_n(curPath.begin(), std::min(curPath.size(), pathBuffer.size() - 1), pathBuffer.begin());


		if (ImGui::InputText("Sprite Path", pathBuffer.data(), pathBuffer.size())) {
			std::string newPath = pathBuffer.data();


			sf::Texture temp;
			if (temp.loadFromFile(newPath)) {

				_texture->swap(temp);
				_sprite->setTexture(*_texture, true);

				_spritePath = newPath;
			}

		}




		bool repeatTexture = _texture->isRepeated();
		if (ImGui::Checkbox("Repeat Texture", &repeatTexture)) {
			_texture->setRepeated(repeatTexture);
		}




		auto rect = _sprite->getTextureRect();
		int rectValues[4]{
			rect.position.x,
			rect.position.y,
			rect.size.x,
			rect.size.y
			
		
		};

		if (ImGui::InputInt4("Texture Rect", rectValues)) {
			auto newRect = sf::IntRect(
				{ rectValues[0],rectValues[1] },
				{ rectValues[2] , rectValues[3] }
			);

			_sprite->setTextureRect(newRect);
			SetOrigin();
			std::cout << "changed";

			
		}



	}

	virtual nlohmann::json SaveToJSON()const override {
		nlohmann::json data;
		data["type"] = "sprite";
		data["colour"] = _sprite->getColor();
		data["spritePath"] = _spritePath;
		data["textureRect"] = _sprite->getTextureRect();
		data["isRepeated"] = _texture->isRepeated();

		return data;

	}


#endif


private:
	inline static bool registered = [] {
		RendererFactory::instance().Register("sprite", &SpriteRenderer::Create);
		return true;
		}();

};
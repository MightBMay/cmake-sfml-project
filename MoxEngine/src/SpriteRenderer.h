#pragma once
#include "pch.h"

class SpriteRenderer : public Component {


private:
	sf::Sprite _sprite;


public:
	SpriteRenderer(const sf::Texture& texture) {
		_sprite.setTexture(texture);
		_sprite.setOrigin({
			texture.getSize().x / 2.f, 
			texture.getSize().y / 2.f 
		});
	}
};
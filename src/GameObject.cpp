#include "pch.h"
#include "GameObject.h"



GameObject::GameObject(const sf::Vector2f& position)
{
	_transform = std::make_unique<Transform>();
	_transform->SetPosition(position);

}


void GameObject::Update(float deltaTime) {

	for (auto& c : _components) {
		c->Update(deltaTime);
	}
}

void GameObject::draw(sf::RenderTarget& target, sf::RenderStates states) const {
	states.transform *= _transform->GetSFTransform();
	if (_renderer != nullptr) _renderer->draw(target, states);

}
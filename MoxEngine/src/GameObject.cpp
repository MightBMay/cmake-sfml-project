#include "pch.h"
#include "GameObject.h"



GameObject::GameObject() {
	_transform = std::make_unique<Transform>();
}


GameObject::GameObject(const sf::Vector2f& position)
{
	_transform = std::make_unique<Transform>();
	_transform->SetPosition(position);

}


void GameObject::Update(float deltaTime) {

	for (auto& c : _components) {
		if(c->GetEnabled())
			c->Update(deltaTime);
	}
}


void GameObject::addComponent(std::unique_ptr<Component> component) {
	component->SetParent(this);
	component->Start();
	_components.emplace_back(std::move(component));

}
void GameObject::draw(sf::RenderTarget& target, sf::RenderStates states) const {
	states.transform *= _transform->GetSFTransform();
	if (_renderer != nullptr) _renderer->draw(target, states);

}
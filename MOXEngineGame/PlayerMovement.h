#pragma once
#include "Component.h"
#include "Global.h"

class PlayerMovement : public Component {




protected:
	float moveSpeed = 50;

public:

	static std::unique_ptr<Component> Create(const nlohmann::json& data) {
		return std::make_unique<PlayerMovement>();
	}

	virtual void Start() { }
	virtual void Update(float deltaTime) {
		static Transform* transform = _parent->_transform.get();
		if (Input::GetKeyDown(sf::Keyboard::Scancode::Space)) {
			std::cout << _parent->GetName()<<"\n";
		}
		sf::Vector2f direction(0, 0);
		if (Input::GetAction("up") && !Input::GetAction("down"))
			direction.y = -1;
		else if (Input::GetAction("down") && !Input::GetAction("up"))
			direction.y = 1;

		if (Input::GetAction("right") && !Input::GetAction("left"))
			direction.x = 1;
		else if (Input::GetAction("left") && !Input::GetAction("right"))
			direction.x = -1;
	
		if (direction.lengthSquared() <= 0) return; // if invalid direction vector, do not normalize and move, just exit.

		direction = direction.normalized();

		transform->Move(direction * moveSpeed * deltaTime);

	
	}

private:
	inline static bool registered = [] {// static bool with a lambda assignment. ensures this is calculated exactly once, at startup, to register for the SceneLoader's use later.
		ComponentFactory::instance().Register("PlayerMovement", &PlayerMovement::Create);
		return true;
		}();


};
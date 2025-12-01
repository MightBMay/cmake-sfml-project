#pragma once
#include "SFML/System/Vector2.hpp"
#include "json.hpp"
#include <iostream>


class GameObject;
class Transform;
enum ColliderType {
	None,
	Box,
	Circle,
	Tilemap
};

struct CircleCollider;
struct BoxCollider;




struct Collider {


	sf::Vector2f _colliderOrigin = { 0,0 };
	sf::Vector2f _halfSize = { 0,0 };
	GameObject* _parent = nullptr;
	Transform* _transform = nullptr;

	virtual void getImGuiParams(nlohmann::json& data) = 0;
	virtual void getInspectorParams() = 0;

	virtual nlohmann::json SaveToJSON() const = 0;


	sf::Vector2f GetWorldPosition() const;
	



	static constexpr const char* ToString(const ColliderType type) {
		switch (type) {
			case ColliderType::Box: return "box";
			case ColliderType::Circle: return "circle";
			case ColliderType::Tilemap: return "tilemap";
		}
		return "unknown";
	}

	static ColliderType FromString(const std::string& str) {
	
		if(str == "box") return ColliderType::Box;
		else if (str == "circle") return ColliderType::Circle;
		else if (str == "tilemap") return ColliderType::Tilemap;
		return ColliderType::None;
	}

	ColliderType type;
	virtual ~Collider() = default;


	


	static bool BoxVsBox(const BoxCollider& a, const BoxCollider& b);

	static bool BoxVsCircle(const BoxCollider& box, const CircleCollider& circle);

	static bool CircleVsCircle(const CircleCollider& a, const CircleCollider& b);

	static bool PointVsBox(const sf::Vector2f& p, const BoxCollider& box);

	static bool PointVsCircle(const sf::Vector2f& p, const CircleCollider& c);
	/*bool PointVsTilemap(const sf::Vector2f& p, const TilemapCollider& map)
	{
		int tileX = static_cast<int>(p.x) / map.tileSize.x;
		int tileY = static_cast<int>(p.y) / map.tileSize.y;

		return map.isSolid(tileX, tileY);
	}
	*/

	static bool CheckPoint(const sf::Vector2f& p, const Collider* col);

	static bool CheckCollision(const Collider* a, const Collider* b);

	virtual void OnCollision(const Collider* other) const;
};
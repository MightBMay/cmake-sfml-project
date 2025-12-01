#include "Collider.h"
#include "BoxCollider.h"
#include "CircleCollider.h"
#include "GameObject.h"

sf::Vector2f Collider::GetWorldPosition() const {
	sf::Vector2f scale = _transform->GetScale();
	sf::Vector2f offset{ _colliderOrigin.x * scale.x, _colliderOrigin.y * scale.y };
	return _transform->GetPosition() + offset;
}

bool Collider::BoxVsBox(const BoxCollider& a, const BoxCollider& b) {
	return !(a._position.x + a._size.x < b._position.x ||
		b._position.x + b._size.x < a._position.x ||
		a._position.y + a._size.y < b._position.y ||
		b._position.y + b._size.y < a._position.y);
}


bool Collider::BoxVsCircle(const BoxCollider& box, const CircleCollider& circle)
{

	auto circleCenter = circle.GetWorldPosition();

	float cx = std::clamp(circleCenter.x, box._position.x, box._position.x + box._size.x);
	float cy = std::clamp(circleCenter.y, box._position.y, box._position.y + box._size.y);

	float dx = circleCenter.x - cx;
	float dy = circleCenter.y - cy;

	float radius = circle.GetRadius();
	return (dx * dx + dy * dy) <= radius * radius ;
}

bool Collider::CircleVsCircle(const CircleCollider& a, const CircleCollider& b)
{
	const sf::Vector2f centerA = a.GetWorldPosition();
	const sf::Vector2f centerB = b.GetWorldPosition();

	const float radA = a.GetRadius();
	const float radB = a.GetRadius();

	float dx = centerA.x - centerB.x;
	float dy = centerA.y - centerB.y;
	float rad = a._radius + b._radius;
	return (dx * dx + dy * dy) <= rad * rad;
}

bool Collider::PointVsBox(const sf::Vector2f& p, const BoxCollider& box)
{
	return (p.x >= box._position.x &&
		p.x <= box._position.x + box._size.x &&
		p.y >= box._position.y &&
		p.y <= box._position.y + box._size.y);
}

bool Collider::PointVsCircle(const sf::Vector2f& p, const CircleCollider& c)
{
	auto circleCenter = c.GetWorldPosition();
	float radius = c.GetRadius();

	float dx = p.x - circleCenter.x;
	float dy = p.y - circleCenter.y;
	return (dx * dx + dy * dy) <= (radius * radius);
}

/*bool PointVsTilemap(const sf::Vector2f& p, const TilemapCollider& map)
{
	int tileX = static_cast<int>(p.x) / map.tileSize.x;
	int tileY = static_cast<int>(p.y) / map.tileSize.y;

	return map.isSolid(tileX, tileY);
}
*/


bool Collider::CheckPoint(const sf::Vector2f& p, const Collider* col)
{
	switch (col->type)
	{
		case ColliderType::Box:
			return PointVsBox(p, *(BoxCollider*)col);

		case ColliderType::Circle:
			return PointVsCircle(p, *(CircleCollider*)col);

		/*case ColliderType::Tilemap:
			return PointVsTilemap(p, *(TilemapCollider*)col);*/
	}
	return false;
}

bool Collider::CheckCollision(const Collider* a, const Collider* b) {
	if (a->type == ColliderType::Box && b->type == ColliderType::Box)
		return BoxVsBox(*(BoxCollider*)a, *(BoxCollider*)b);

	else if (a->type == ColliderType::Circle && b->type == ColliderType::Circle)
		return CircleVsCircle(*(CircleCollider*)a, *(CircleCollider*)b);

	else if (a->type == ColliderType::Box && b->type == ColliderType::Circle)
		return BoxVsCircle(*(BoxCollider*)a, *(CircleCollider*)b);

	else if (a->type == ColliderType::Circle && b->type == ColliderType::Box)
		return BoxVsCircle(*(BoxCollider*)b, *(CircleCollider*)a);

	/*else if (a->type == ColliderType::Box && b->type == ColliderType::Tilemap)
		return BoxVsTilemap(*(BoxCollider*)a, *(TilemapCollider*)b);

	else if (a->type == ColliderType::Tilemap && b->type == ColliderType::Box)
		return BoxVsTilemap(*(BoxCollider*)b, *(TilemapCollider*)a);*/


	return false;
}


void Collider::OnCollision(const Collider* other) const {

	std::cout << "this col: " << _parent->GetName() << ", other col: " << other->_parent->GetName() << "\n";


}
#pragma once
#include <vector>
#include <algorithm>
#include "Collider.h"


class CollisionSystem {
private:
	static inline std::vector<const Collider*> _Colliders;



public:
	static void AddCollider(const Collider* col) {
		_Colliders.push_back(col);
	}

	static void RemoveCollider(const Collider* col) {
		auto it = std::find(_Colliders.begin(), _Colliders.end(), col);
		if (it != _Colliders.end()) {
			std::swap(*it, _Colliders.back());
			_Colliders.pop_back();
		}
	}

	static void Update(float deltaTime) {
		
		const size_t count = _Colliders.size();

		for (size_t i = 0; i < count; ++i) {
			const Collider* a = _Colliders[i];

			for (size_t j = i + 1; j < count; ++j) {
				const Collider* b = _Colliders[j];
				if (Collider::CheckCollision(a, b)) {
					a->OnCollision(b);
					b->OnCollision(a);
				}


			}
		}

		// check collisions here somehow. be sure to account for the transforms of the collider's gameobject in _parent.
	}
};
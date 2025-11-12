#pragma once
#include "GameObject.h"
#include "json.hpp"



class Component {

protected:
	GameObject* _parent = nullptr;

public: 
	virtual void SetParent(GameObject* parent) { _parent = parent; }
	virtual ~Component() = default;
	virtual void Start(){}
	virtual void Update(float deltaTime){}

	virtual void getImGuiParams(nlohmann::json& data) = 0;

};
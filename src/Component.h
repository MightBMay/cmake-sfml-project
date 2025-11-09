#pragma once
#include "pch.h"



class Component {

protected:
	GameObject* parent = nullptr;

public: 

	
	virtual ~Component() = default;
	virtual void Update(float deltaTime){}

};
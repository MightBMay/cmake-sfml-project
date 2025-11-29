#pragma once
#include "GUI_CreateGameObject.h"

struct GUI_Action
{
public:
    virtual ~GUI_Action() = default;
	virtual void Execute()  = 0;

	virtual void Undo()  = 0;
};

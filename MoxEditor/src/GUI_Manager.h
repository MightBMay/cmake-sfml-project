#pragma once
#if IN_EDITOR

#include "FixedStack.h"
#include "GUI_Action.h"
#include "GUI_Inspector.h"
#include "SceneHeirarchy.h"
#include "Global.h"





class GUI_Manager {
public:
	inline static FixedStack<std::unique_ptr<GUI_Action>> performedActions;

	static GUI_Manager& instance() {
		static GUI_Manager inst;
		return inst;
	}


	 
    static void ExecuteAction(std::unique_ptr<GUI_Action> action) {
        action->Execute();
        performedActions.push(std::move(action));
    }

    static void UndoLastAction() {
        if (!performedActions.empty()) {
            performedActions.top()->Undo();
            performedActions.pop();
        }
    }

    void Draw();



};

#endif
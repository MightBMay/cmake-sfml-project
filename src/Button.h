#pragma once

#include "Event.h"

class Button : public Component {

protected:
	Renderer* _renderer;
	/// <summary>
	/// was the cursor hovering this component's renderer last update.
	/// </summary>
	bool wasHovering = false;
	bool isClicked = false;
	Event<> _onClick;
	Event<> _onRelease;
	Event<> _onHover;
	Event<> _onHoverExit;


	void oc() { std::cout << "onclick"; }
	void oR() { std::cout << "onrelease"; }
	void oh() { std::cout << "onhover"; }
	void ohe() { std::cout << "onhoverexit"; }

public:
	Event<>& GetOnClick();
	Event<>& GetOnRelease();
	Event<>& GetOnHover();
	Event<>& GetOnHoverExit();


	virtual void Start();

	virtual void Update(float deltaTime);


};

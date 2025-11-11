#include "pch.h"
#include "Button.h"
#include "Event.h"



Event<>& Button::GetOnClick() { return _onClick; }
Event<>& Button::GetOnRelease() { return _onRelease; }
Event<>& Button::GetOnHover() { return _onHover; }
Event<>& Button::GetOnHoverExit() { return _onHoverExit; }

void Button::Start() {
	_renderer = _parent->getRenderer();

	_onClick += [this]() {isClicked = true; };

	_onRelease += [this]() {isClicked = false; };

	_onClick += [this]() {oc(); };

	_onRelease += [this]() {oR(); };
	_onHover += [this]() {oh(); };
	_onHoverExit += [this]() {ohe(); };

}



void Button::Update(float deltaTime) {


	auto mousePos = window.mapPixelToCoords(sf::Mouse::getPosition(window));
	bool isHovering = _renderer->IsPointInside(mousePos);


	if (isHovering && !wasHovering) _onHover(); 

	if (!isHovering && wasHovering) _onHoverExit();

	if (isHovering && Input::GetMouseDown(0)) _onClick();	// only clickable if you are currently hovering.

	if (isClicked && Input::GetMouseUp(0)) _onRelease(); // only release button if it was already clicked.


	wasHovering = isHovering;





}
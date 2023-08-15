//
// Created by MINH NHUT on 8/15/2023.
//

#include "AVLState.hpp"

AVLState::AVLState(StateStack& stack, State::Context context)
    : VisualState(stack, context, "AVL Tree"), Inputs(NumOptions) {}

void AVLState::draw() {
	VisualState::draw();
	//	getContext().window->draw(mHeap);
}

bool AVLState::update(sf::Time dt) {
	bool result = true;
	result |= VisualState::update(dt);
	return result;
}

bool AVLState::handleEvent(const sf::Event& event) {
	VisualState::handleEvent(event);
	return false;
}

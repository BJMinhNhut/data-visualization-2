//
// Created by MINH NHUT on 8/14/2023.
//

#include "HashState.hpp"

HashState::HashState(StateStack& stack, State::Context context)
    : VisualState(stack, context, "Hash table - Linear Probing"), Inputs(NumOptions) {
	initOptions();
	initDetails();
}

void HashState::initOptions() {}

void HashState::initDetails() {}

void HashState::draw() {
	VisualState::draw();
}

bool HashState::update(sf::Time dt) {
	bool result = true;
	result |= VisualState::update(dt);
	return result;
}

bool HashState::handleEvent(const sf::Event& event) {
	VisualState::handleEvent(event);
	return false;
}

std::pair<std::vector<Animation>, std::string> HashState::getSteps(unsigned int option) {
	return VisualState::getSteps(option);
}

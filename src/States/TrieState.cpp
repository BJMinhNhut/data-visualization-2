//
// Created by MINH NHUT on 8/18/2023.
//

#include "TrieState.hpp"

TrieState::TrieState(StateStack& stack, State::Context context)
    : VisualState(stack, context, "Trie"), Inputs(NumOptions) {}

void TrieState::draw() {
	VisualState::draw();
	//	getContext().window->draw(mTree);
}

bool TrieState::update(sf::Time dt) {
	bool result = true;
	result |= VisualState::update(dt);
	//	mTree.update(dt);
	return result;
}

bool TrieState::handleEvent(const sf::Event& event) {
	VisualState::handleEvent(event);
	return false;
}
std::pair<std::vector<Animation>, std::string> TrieState::getSteps(unsigned int option) {
	return VisualState::getSteps(option);
}

//
// Created by MINH NHUT on 8/21/2023.
//

#include "GraphState.hpp"

GraphState::GraphState(StateStack& stack, State::Context context)
    : VisualState(stack, context, "Graph"), mGraph(*context.fonts, *context.colors) {
	mGraph.setTargetPosition(context.window->getSize().x / 2.f + 200.f, 180.f,
	                         Graph::Transition::None);
	//	initOptions();
	//	initCreate();
}

void GraphState::draw() {
	VisualState::draw();
	getContext().window->draw(mGraph);
}

bool GraphState::update(sf::Time dt) {
	bool result = true;
	result |= VisualState::update(dt);
	mGraph.update(dt);
	return result;
}

bool GraphState::handleEvent(const sf::Event& event) {
	VisualState::handleEvent(event);
	return false;
}

std::pair<std::vector<Animation>, std::string> GraphState::getSteps(unsigned int option) {
	return VisualState::getSteps(option);
}
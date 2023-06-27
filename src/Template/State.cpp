//
// Created by MINH NHUT on 6/11/2023.
//

#include "State.hpp"
#include "StateStack.hpp"

State::Context::Context(sf::RenderWindow& window, TextureHolder& textures, FontHolder& fonts)
    : window(&window), textures(&textures), fonts(&fonts) {}

State::State(StateStack& stack, Context context) : mStack(&stack), mContext(context) {}

State::~State() {}

void State::requestStackPush(States::ID stateID) {
	mStack->pushState(stateID);
}

void State::requestStackPop() {
	mStack->popState();
}

void State::requestStateClear() {
	mStack->clearStates();
}

State::Context State::getContext() const {
	return mContext;
}
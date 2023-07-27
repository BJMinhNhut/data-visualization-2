//
// Created by MINH NHUT on 7/28/2023.
//

#include "MaxHeapState.hpp"

MaxHeapState::MaxHeapState(StateStack &stack, State::Context context) :
        VisualState(stack, context, "Max Heap") {}

void MaxHeapState::draw() {
    VisualState::draw();
}

bool MaxHeapState::update(sf::Time dt) {
    bool result = true;
    result |= VisualState::update(dt);
    return result;
}

bool MaxHeapState::handleEvent(const sf::Event &event) {
    VisualState::handleEvent(event);
    return false;
}
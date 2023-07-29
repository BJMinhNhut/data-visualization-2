//
// Created by MINH NHUT on 7/28/2023.
//

#include "MaxHeapState.hpp"

MaxHeapState::MaxHeapState(StateStack &stack, State::Context context) :
        VisualState(stack, context, "Max Heap"),
        mHeap(*context.fonts, *context.colors) {
    mHeap.setPosition(context.window->getSize().x / 2.f, 200.f);
}

void MaxHeapState::draw() {
    VisualState::draw();
    getContext().window->draw(mHeap);
}

bool MaxHeapState::update(sf::Time dt) {
    bool result = true;
    result |= VisualState::update(dt);
    return result;
}

bool MaxHeapState::handleEvent(const sf::Event &event) {
    VisualState::handleEvent(event);

    if (event.type == sf::Event::KeyReleased) {
        if (event.key.code == sf::Keyboard::C)
            mHeap.randomize();
        else if (event.key.code == sf::Keyboard::F) {
            mHeap.loadFromFile(selectedTextFile());
        }
    }
    return false;
}
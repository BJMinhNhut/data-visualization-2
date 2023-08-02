//
// Created by MINH NHUT on 7/28/2023.
//

#include "MaxHeapState.hpp"
#include "Template/Random.hpp"

#include <iostream>

MaxHeapState::MaxHeapState(StateStack &stack, State::Context context) :
        VisualState(stack, context, "Max Heap"),
        mHeap(*context.fonts, *context.colors) {
    mHeap.setPosition(context.window->getSize().x / 2.f, 200.f);
	initOptions();
}

void MaxHeapState::initOptions() {
	mActionsHub.addOption(Create, "Create", [&]() { mActionsHub.setCurrentOption(Create); });
	mActionsHub.addOption(Push, "Push", [&]() { mActionsHub.setCurrentOption(Push); });
	mActionsHub.addOption(Pop, "Pop", [&]() { mActionsHub.setCurrentOption(Pop); });
	mActionsHub.addOption(Top, "Top", [&]() { mActionsHub.setCurrentOption(Top); });
	mActionsHub.addOption(Size, "Size", [&]() { mActionsHub.setCurrentOption(Size); });
}

void MaxHeapState::draw() {
    VisualState::draw();
    getContext().window->draw(mHeap);
}

bool MaxHeapState::update(sf::Time dt) {
    bool result = true;
    result |= VisualState::update(dt);
    mHeap.update(dt);
    return result;
}

bool MaxHeapState::handleEvent(const sf::Event &event) {
    VisualState::handleEvent(event);

    if (event.type == sf::Event::KeyReleased) {
        if (event.key.code == sf::Keyboard::C)
            mHeap.randomize();
        else if (event.key.code == sf::Keyboard::F)
            mHeap.loadFromFile(selectedTextFile());
        else if (event.key.code == sf::Keyboard::I)
            mHeap.push(Random::getInt(1, 99));
        else if (event.key.code == sf::Keyboard::P) {
            std::cout << "Heap top: " << mHeap.top() << '\n';
            mHeap.pop();
        }
    }
    return false;
}
//
// Created by MINH NHUT on 7/28/2023.
//

#include "MaxHeapState.hpp"
#include "Template/Random.hpp"

#include <iostream>

MaxHeapState::MaxHeapState(StateStack& stack, State::Context context)
    : VisualState(stack, context, "Max Heap"), mHeap(*context.fonts, *context.colors) {
	mHeap.setPosition(context.window->getSize().x / 2.f + 200.f, 200.f);
	initOptions();
	initDetails();
}

void MaxHeapState::initOptions() {
	mActionsHub.addOption(Create, "Create", true, [&]() { mActionsHub.setCurrentOption(Create); });
	mActionsHub.addOption(Push, "Push", false, [&]() {
		mActionsHub.setCurrentOption(Push);
		int value = Random::getInt(0, 99);
		mHeap.push(value);
	});
	mActionsHub.addOption(Pop, "Pop", false, [&]() {
		mActionsHub.setCurrentOption(Pop);
		mHeap.pop();
	});
	mActionsHub.addOption(Top, "Top", false, [&]() { mActionsHub.setCurrentOption(Top); });
	mActionsHub.addOption(Size, "Size", false, [&]() { mActionsHub.setCurrentOption(Size); });
}

void MaxHeapState::initDetails() {
	// Create
	auto randomButton = std::make_shared<GUI::Button>(GUI::Button::Small, *getContext().fonts,
	                                                  *getContext().textures, *getContext().colors);
	randomButton->setCallback([&]() { mHeap.randomize(); });
	randomButton->setPosition(250.f, 200.f);
	randomButton->setText("Random");
	mActionsHub.packOptionGUI(Create, randomButton);
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

bool MaxHeapState::handleEvent(const sf::Event& event) {
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
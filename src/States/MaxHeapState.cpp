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

	auto fileButton = std::make_shared<GUI::Button>(GUI::Button::Small, *getContext().fonts,
	                                                *getContext().textures, *getContext().colors);
	fileButton->setCallback([&]() {
		std::string fileDir;
		if (selectedTextFile(fileDir))
			mHeap.loadFromFile(fileDir);
	});
	fileButton->setPosition(250.f, 275.f);
	fileButton->setText("Load file");
	mActionsHub.packOptionGUI(Create, fileButton);
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
	return false;
}
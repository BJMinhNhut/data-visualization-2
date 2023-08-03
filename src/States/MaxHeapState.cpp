//
// Created by MINH NHUT on 7/28/2023.
//

#include "MaxHeapState.hpp"
#include "Template/Random.hpp"

#include <iostream>

MaxHeapState::MaxHeapState(StateStack& stack, State::Context context)
    : VisualState(stack, context, "Max Heap"),
      mHeap(*context.fonts, *context.colors),
      Inputs(NumOptions, nullptr) {
	mHeap.setPosition(context.window->getSize().x / 2.f + 200.f, 200.f);
	initOptions();
	initDetails();
	initActions();
}

void MaxHeapState::initOptions() {
	mActionsHub.addOption(Create, "Create", [&]() { mActionsHub.setCurrentOption(Create); });
	mActionsHub.addOption(Push, "Push", [&]() {
		mActionsHub.setCurrentOption(Push);
		Inputs[Push]->randomizeValue();
	});
	mActionsHub.addOption(Pop, "Pop", [&]() { mActionsHub.setCurrentOption(Pop); });
	mActionsHub.addOption(Top, "Top", [&]() { mActionsHub.setCurrentOption(Top); });
	mActionsHub.addOption(Size, "Size", [&]() { mActionsHub.setCurrentOption(Size); });
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

	// Push
	Inputs[Push] = std::make_shared<GUI::Input>(*getContext().fonts, *getContext().textures,
	                                            *getContext().colors);
	Inputs[Push]->setPosition(250.f, 250.f);
	Inputs[Push]->setRange(Heap::MIN_VALUE, Heap::MAX_VALUE);
	mActionsHub.packOptionGUI(Push, Inputs[Push]);
}

void MaxHeapState::initActions() {
	mActionsHub.setOptionAction(Push, [&]() { mHeap.push(Inputs[Push]->getValue()); });
	mActionsHub.setOptionAction(Pop, [&]() { mHeap.pop(); });
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
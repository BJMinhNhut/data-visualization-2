//
// Created by MINH NHUT on 7/28/2023.
//

#include "MaxHeapState.hpp"
#include "GUI/Label.hpp"
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
	mActionsHub.addOption(Create, "Create", [&]() {
		mActionsHub.setCurrentOption(Create);
		mPlayer.callInfo("Init a new heap");
	});
	mActionsHub.addOption(Push, "Push", [&]() {
		mActionsHub.setCurrentOption(Push);
		mPlayer.callInfo("Push a new value to heap");
		Inputs[Push]->randomizeValue();
	});
	mActionsHub.addOption(Delete, "Delete", [&]() {
		mActionsHub.setCurrentOption(Delete);
		mPlayer.callInfo("Delete a node from heap by ID");
		Inputs[Delete]->setRange(0, mHeap.getSize() - 1);
		if (mHeap.getSize() > 0)
			Inputs[Delete]->randomizeValue();
		else
			Inputs[Delete]->clear();
	});
	mActionsHub.addOption(Top, "Top", [&]() {
		mActionsHub.setCurrentOption(Top);
		mPlayer.callInfo("Get value of the top node");
	});
	mActionsHub.addOption(Size, "Size", [&]() {
		mActionsHub.setCurrentOption(Size);
		mPlayer.callInfo("Get size of heap");
	});
}

void MaxHeapState::initDetails() {
	// Create
	auto randomButton = std::make_shared<GUI::Button>(GUI::Button::Small, *getContext().fonts,
	                                                  *getContext().textures, *getContext().colors);
	randomButton->setCallback([&]() { mHeap.randomize(); });
	randomButton->setPosition(250.f, 590.f - 30.f);
	randomButton->setText("Random");
	mActionsHub.packOptionGUI(Create, randomButton);

	auto fileButton = std::make_shared<GUI::Button>(GUI::Button::Small, *getContext().fonts,
	                                                *getContext().textures, *getContext().colors);
	fileButton->setCallback([&]() {
		std::string fileDir;
		if (selectedTextFile(fileDir))
			mHeap.loadFromFile(fileDir);
	});
	fileButton->setPosition(250.f, 590.f + 30.f);
	fileButton->setText("Load file");
	mActionsHub.packOptionGUI(Create, fileButton);

	// Push
	auto valueLabel = std::make_shared<GUI::Label>(GUI::Label::Small, "Value", *getContext().fonts,
	                                               *getContext().colors);
	valueLabel->setPosition(250.f, 555.f);
	valueLabel->alignCenter();
	mActionsHub.packOptionGUI(Push, valueLabel);

	Inputs[Push] = std::make_shared<GUI::Input>(*getContext().fonts, *getContext().textures,
	                                            *getContext().colors);
	Inputs[Push]->setPosition(250.f, 590.f);
	Inputs[Push]->setRange(Heap::MIN_VALUE, Heap::MAX_VALUE);
	mActionsHub.packOptionGUI(Push, Inputs[Push]);

	// Delete
	auto indexLabel = std::make_shared<GUI::Label>(GUI::Label::Small, "Index", *getContext().fonts,
	                                               *getContext().colors);
	indexLabel->setPosition(250.f, 555.f);
	indexLabel->alignCenter();
	mActionsHub.packOptionGUI(Delete, indexLabel);

	Inputs[Delete] = std::make_shared<GUI::Input>(*getContext().fonts, *getContext().textures,
	                                              *getContext().colors);
	Inputs[Delete]->setPosition(250.f, 590.f);
	mActionsHub.packOptionGUI(Delete, Inputs[Delete]);
}

void MaxHeapState::initActions() {
	mActionsHub.setOptionAction(Push, [&]() { mHeap.push(Inputs[Push]->getValue()); });
	mActionsHub.setOptionAction(Delete, [&]() { mHeap.remove(Inputs[Delete]->getValue()); });
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
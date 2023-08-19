//
// Created by MINH NHUT on 8/11/2023.
//

#include "MinHeapState.hpp"
#include "GUI/Label.hpp"
#include "Template/Random.hpp"

#include <iostream>

MinHeapState::MinHeapState(StateStack& stack, State::Context context)
    : VisualState(stack, context, "Min Heap"),
      mHeap(*context.fonts, *context.colors),
      Inputs(NumOptions, nullptr) {
	mHeap.setTargetPosition(context.window->getSize().x / 2.f + 200.f, 200.f,
	                        MinHeap::Transition::None);
	initOptions();
	initDetails();
}

void MinHeapState::initOptions() {
	mActionsHub.addOption(Create, "Create", [&]() {
		mActionsHub.setCurrentOption(Create);
		mPlayer.reset();
		mPlayer.callInfo("Init a new heap");
	});
	mActionsHub.addOption(Push, "Push", [&]() {
		mActionsHub.setCurrentOption(Push);
		mPlayer.reset();
		mPlayer.callInfo("Push a new value to heap");
		Inputs[Push]->randomizeValue();
	});
	mActionsHub.addOption(Delete, "Delete", [&]() {
		mActionsHub.setCurrentOption(Delete);
		mPlayer.reset();
		mPlayer.callInfo("Delete a node from heap by ID");
		Inputs[Delete]->setRange(0, mHeap.getSize() - 1);
		if (mHeap.getSize() > 0)
			Inputs[Delete]->randomizeValue();
		else
			Inputs[Delete]->clear();
	});
	mActionsHub.addOption(Top, "Top", [&]() {
		mActionsHub.setCurrentOption(Top);
		mPlayer.reset();
		mPlayer.callInfo("Get value of the top node");
	});
	mActionsHub.addOption(Size, "Size", [&]() {
		mActionsHub.setCurrentOption(Size);
		mPlayer.reset();
		mPlayer.callInfo("Get size of heap");
	});
}

void MinHeapState::initDetails() {
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

	Inputs[Push] = std::make_shared<GUI::InputNum>(*getContext().fonts, *getContext().textures,
	                                               *getContext().colors);
	Inputs[Push]->setPosition(250.f, 590.f);
	Inputs[Push]->setRange(MinHeap::MIN_VALUE, MinHeap::MAX_VALUE);
	mActionsHub.packOptionGUI(Push, Inputs[Push]);

	// Delete
	auto indexLabel = std::make_shared<GUI::Label>(GUI::Label::Small, "Index", *getContext().fonts,
	                                               *getContext().colors);
	indexLabel->setPosition(250.f, 555.f);
	indexLabel->alignCenter();
	mActionsHub.packOptionGUI(Delete, indexLabel);

	Inputs[Delete] = std::make_shared<GUI::InputNum>(*getContext().fonts, *getContext().textures,
	                                                 *getContext().colors);
	Inputs[Delete]->setPosition(250.f, 590.f);
	mActionsHub.packOptionGUI(Delete, Inputs[Delete]);
}

void MinHeapState::draw() {
	VisualState::draw();
	getContext().window->draw(mHeap);
}

bool MinHeapState::update(sf::Time dt) {
	bool result = true;
	result |= VisualState::update(dt);
	mHeap.update(dt);
	return result;
}

bool MinHeapState::handleEvent(const sf::Event& event) {
	VisualState::handleEvent(event);
	return false;
}
std::pair<std::vector<Animation>, std::string> MinHeapState::getSteps(unsigned int option) {
	try {
		mHeap.clearHighlight();
		switch (option) {
			case Push:
				if (Inputs[Push]->validate() != GUI::InputNum::Success)
					throw std::out_of_range("Value must be in range " +
					                        Inputs[Push]->getStringRange());
				return mHeap.pushAnimation(Inputs[Push]->getValue());
			case Delete:
				if (Inputs[Delete]->validate() != GUI::InputNum::Success)
					throw std::out_of_range("Value must be in range " +
					                        Inputs[Delete]->getStringRange());
				return mHeap.deleteAnimation(Inputs[Delete]->getValue());
			case Top:
				return mHeap.getTopAnimation();
			case Size:
				return mHeap.getSizeAnimation();
			default:
				return VisualState::getSteps(option);
		}
	} catch (const std::exception& err) {
		mPlayer.callError(err.what());
	}
	return VisualState::getSteps(option);
}

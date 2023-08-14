//
// Created by MINH NHUT on 8/14/2023.
//

#include "HashState.hpp"

HashState::HashState(StateStack& stack, State::Context context)
    : VisualState(stack, context, "Hash table - Linear Probing"), Inputs(NumOptions) {
	initOptions();
	initDetails();
}

void HashState::initOptions() {
	mActionsHub.addOption(Create, "Create", [&]() {
		mActionsHub.setCurrentOption(Create);
		mPlayer.reset();
		mPlayer.callInfo("Init a new hash table");
	});
	mActionsHub.addOption(Insert, "Insert", [&]() {
		mActionsHub.setCurrentOption(Insert);
		mPlayer.reset();
		mPlayer.callInfo("Push a new value to hash table");
		//		Inputs[Insert]->randomizeValue();
	});
	mActionsHub.addOption(Delete, "Delete", [&]() {
		mActionsHub.setCurrentOption(Delete);
		mPlayer.reset();
		mPlayer.callInfo("Delete a node from heap by ID");
		//		Inputs[Delete]->setRange(0, mHeap.getSize() - 1);
		//		if (mHeap.getSize() > 0)
		//			Inputs[Delete]->randomizeValue();
		//		else
		//			Inputs[Delete]->clear();
	});
	mActionsHub.addOption(Search, "Search", [&]() {
		mActionsHub.setCurrentOption(Search);
		mPlayer.reset();
		mPlayer.callInfo("Search for a value in hash table");
	});
}

void HashState::initDetails() {}

void HashState::draw() {
	VisualState::draw();
}

bool HashState::update(sf::Time dt) {
	bool result = true;
	result |= VisualState::update(dt);
	return result;
}

bool HashState::handleEvent(const sf::Event& event) {
	VisualState::handleEvent(event);
	return false;
}

std::pair<std::vector<Animation>, std::string> HashState::getSteps(unsigned int option) {
	return VisualState::getSteps(option);
}

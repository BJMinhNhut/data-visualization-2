//
// Created by MINH NHUT on 8/18/2023.
//

#include "TrieState.hpp"

TrieState::TrieState(StateStack& stack, State::Context context)
    : VisualState(stack, context, "Trie"),
      Inputs(NumOptions),
      mTrie(*context.fonts, *context.colors) {
	mTrie.setTargetPosition(context.window->getSize().x / 2.f + 200.f, 180.f,
	                        Trie::Transition::None);
	initOptions();
}

void TrieState::initOptions() {
	mActionsHub.addOption(Create, "Create", [&]() {
		mActionsHub.setCurrentOption(Create);
		mPlayer.reset();
		mPlayer.callInfo("Init a new trie");
	});
	mActionsHub.addOption(Insert, "Insert", [&]() {
		mActionsHub.setCurrentOption(Insert);
		mPlayer.reset();
		mPlayer.callInfo("Insert a new value to trie");
		//		Inputs[Insert]->randomizeValue();
	});
	mActionsHub.addOption(Delete, "Delete", [&]() {
		mActionsHub.setCurrentOption(Delete);
		mPlayer.reset();
		mPlayer.callInfo("Delete a value from trie");
		//		if (mTree.getSize() > 0)
		//			Inputs[Delete]->setValue(mTree.getRandomElement());
		//		else
		//			Inputs[Delete]->randomizeValue();
	});
	mActionsHub.addOption(Search, "Search", [&]() {
		mActionsHub.setCurrentOption(Search);
		mPlayer.reset();
		mPlayer.callInfo("Search for a value in trie");
		//		if (mTree.getSize() > 0)
		//			Inputs[Search]->setValue(mTree.getRandomElement());
		//		else
		//			Inputs[Search]->randomizeValue();
	});
}

void TrieState::draw() {
	VisualState::draw();
	getContext().window->draw(mTrie);
}

bool TrieState::update(sf::Time dt) {
	bool result = true;
	result |= VisualState::update(dt);
	mTrie.update(dt);
	return result;
}

bool TrieState::handleEvent(const sf::Event& event) {
	VisualState::handleEvent(event);
	return false;
}
std::pair<std::vector<Animation>, std::string> TrieState::getSteps(unsigned int option) {
	return VisualState::getSteps(option);
}

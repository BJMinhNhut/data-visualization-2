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
	initCreate();
	initInsert();
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
		Inputs[Insert]->randomize();
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

void TrieState::initCreate() {
	// Create
	auto emptyButton = std::make_shared<GUI::Button>(GUI::Button::Small, *getContext().fonts,
	                                                 *getContext().textures, *getContext().colors);
	emptyButton->setCallback([&]() {
		mTrie.clear();
		mPlayer.callInfo("Created an empty trie.");
	});
	emptyButton->setPosition(250.f, 590.f - 60.f);
	emptyButton->setText("Empty");
	mActionsHub.packOptionGUI(Create, emptyButton);

	auto randomButton = std::make_shared<GUI::Button>(GUI::Button::Small, *getContext().fonts,
	                                                  *getContext().textures, *getContext().colors);
	randomButton->setCallback([&]() {
		mTrie.randomize();
		mPlayer.callInfo("Created a trie with random elements, numString = " +
		                 std::to_string(mTrie.count()));
	});
	randomButton->setPosition(250.f, 590.f);
	randomButton->setText("Random");
	mActionsHub.packOptionGUI(Create, randomButton);

	auto fileButton = std::make_shared<GUI::Button>(GUI::Button::Small, *getContext().fonts,
	                                                *getContext().textures, *getContext().colors);
	fileButton->setCallback([&]() {
		std::string fileDir;
		if (selectedTextFile(fileDir))
			mTrie.loadFromFile(fileDir);
		mPlayer.callInfo("Created a trie with elements loaded from file, numString = " +
		                 std::to_string(mTrie.count()));
	});
	fileButton->setPosition(250.f, 590.f + 60.f);
	fileButton->setText("Load file");
	mActionsHub.packOptionGUI(Create, fileButton);
}

void TrieState::initInsert() {
	// Insert
	auto stringLabel = std::make_shared<GUI::Label>(GUI::Label::Small, "String",
	                                                *getContext().fonts, *getContext().colors);
	stringLabel->setPosition(250.f, 555.f);
	stringLabel->alignCenter();
	mActionsHub.packOptionGUI(Insert, stringLabel);

	Inputs[Insert] = std::make_shared<GUI::InputStr>(*getContext().fonts, *getContext().textures,
	                                                 *getContext().colors);
	Inputs[Insert]->setPosition(250.f, 590.f);
	Inputs[Insert]->setLengthLimit(Trie::MAX_LENGTH);
	mActionsHub.packOptionGUI(Insert, Inputs[Insert]);
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
	try {
		mTrie.clearHighlight();
		switch (option) {
			case Insert:
				switch (Inputs[Insert]->validate()) {
					case GUI::InputStr::Success:
						return mTrie.insertAnimation(Inputs[Insert]->getString());
					case GUI::InputStr::InvalidLength:
						throw std::out_of_range("String too long, maximum length is " +
						                        std::to_string(Inputs[Insert]->getLengthLimit()));
					case GUI::InputStr::InvalidCharacter:
						throw std::runtime_error("String characters must be uppercase");
				}
				break;

				//			case Delete:
				//				if (Inputs[Delete]->validate() != GUI::InputNum::Success)
				//					throw std::out_of_range("Value must be in range " +
				//					                        Inputs[Delete]->getStringRange());
				//				return mTree.deleteAnimation(Inputs[Delete]->getValue());
				//			case Search:
				//				if (Inputs[Search]->validate() != GUI::InputNum::Success)
				//					throw std::out_of_range("Value must be in range " +
				//					                        Inputs[Search]->getStringRange());
				//				return mTree.searchAnimation(Inputs[Search]->getValue());
			default:
				return VisualState::getSteps(option);
		}
	} catch (const std::exception& err) {
		mPlayer.callError(err.what());
	}
	return VisualState::getSteps(option);
}

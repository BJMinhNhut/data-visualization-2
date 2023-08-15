//
// Created by MINH NHUT on 8/14/2023.
//

#include "HashState.hpp"
#include "GUI/Panel.hpp"

HashState::HashState(StateStack& stack, State::Context context)
    : VisualState(stack, context, "Hash Table - Linear Probing"),
      Inputs(NumOptions),
      mHashTable(*context.fonts, *context.colors) {
	initOptions();
	initCreate();
	initInsert();
	initSearch();

	mHashTable.setTargetPosition(500.f, 200.f, SceneNode::None);
}

void HashState::initOptions() {
	mActionsHub.addOption(Create, "Create", [&]() {
		mActionsHub.setCurrentOption(Create);
		mPlayer.reset();
		mPlayer.callInfo("Init a new hash table");
		Inputs[Create]->setValue((int)mHashTable.getSize());
	});
	mActionsHub.addOption(Insert, "Insert", [&]() {
		mActionsHub.setCurrentOption(Insert);
		mPlayer.reset();
		mPlayer.callInfo("Push a new value to hash table");
		Inputs[Insert]->randomizeValue();
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

void HashState::initCreate() {
	// Create
	auto sizeLabel = std::make_shared<GUI::Label>(GUI::Label::Small, "Size", *getContext().fonts,
	                                              *getContext().colors);
	sizeLabel->setPosition(250.f, 590.f - 90.f);
	sizeLabel->alignCenter();
	mActionsHub.packOptionGUI(Create, sizeLabel);

	Inputs[Create] = std::make_shared<GUI::Input>(*getContext().fonts, *getContext().textures,
	                                              *getContext().colors);
	Inputs[Create]->setPosition(250.f, 590.f - 55.f);
	Inputs[Create]->setRange(2, (int)HashTable::MAX_SIZE);
	mActionsHub.packOptionGUI(Create, Inputs[Create]);

	auto horizon =
	    std::make_shared<GUI::Panel>(200.f, 0.f, getContext().colors->get(Colors::UIPrimary),
	                                 getContext().colors->get(Colors::UIBorder));
	horizon->setPosition(150.f, 590.f - 15.f);
	mActionsHub.packOptionGUI(Create, horizon);

	auto randomButton = std::make_shared<GUI::Button>(GUI::Button::Small, *getContext().fonts,
	                                                  *getContext().textures, *getContext().colors);
	randomButton->setCallback([&]() {
		if (Inputs[Create]->validate() == GUI::Input::Success) {
			mHashTable.setSize(Inputs[Create]->getValue());
			mHashTable.randomize();
			mPlayer.callInfo("Created a hash table with random elements, size = " +
			                 std::to_string(mHashTable.getSize()));
		} else
			mPlayer.callError("Size must be in range " + Inputs[Create]->getStringRange());
	});
	randomButton->setPosition(250.f, 590.f + 25.f);
	randomButton->setText("Random");
	mActionsHub.packOptionGUI(Create, randomButton);

	auto fileButton = std::make_shared<GUI::Button>(GUI::Button::Small, *getContext().fonts,
	                                                *getContext().textures, *getContext().colors);
	fileButton->setCallback([&]() {
		if (Inputs[Create]->validate() == GUI::Input::Success) {
			std::string fileDir;
			mHashTable.setSize(Inputs[Create]->getValue());
			if (selectedTextFile(fileDir))
				mHashTable.loadFromFile(fileDir);
			mPlayer.callInfo("Created a hash table with elements loaded from file, size = " +
			                 std::to_string(mHashTable.getSize()));
		} else
			mPlayer.callError("Size must be in range " + Inputs[Create]->getStringRange());
	});
	fileButton->setPosition(250.f, 590.f + 75.f);
	fileButton->setText("Load file");
	mActionsHub.packOptionGUI(Create, fileButton);
}

void HashState::initInsert() {
	// Insert
	auto valueLabel = std::make_shared<GUI::Label>(GUI::Label::Small, "Value", *getContext().fonts,
	                                               *getContext().colors);
	valueLabel->setPosition(250.f, 555.f);
	valueLabel->alignCenter();
	mActionsHub.packOptionGUI(Insert, valueLabel);

	Inputs[Insert] = std::make_shared<GUI::Input>(*getContext().fonts, *getContext().textures,
	                                              *getContext().colors);
	Inputs[Insert]->setPosition(250.f, 590.f);
	Inputs[Insert]->setRange(HashTable::MIN_VALUE, HashTable::MAX_VALUE);
	mActionsHub.packOptionGUI(Insert, Inputs[Insert]);
}

void HashState::initSearch() {
	// Search
	auto valueLabel = std::make_shared<GUI::Label>(GUI::Label::Small, "Value", *getContext().fonts,
	                                               *getContext().colors);
	valueLabel->setPosition(250.f, 555.f);
	valueLabel->alignCenter();
	mActionsHub.packOptionGUI(Search, valueLabel);

	Inputs[Search] = std::make_shared<GUI::Input>(*getContext().fonts, *getContext().textures,
	                                              *getContext().colors);
	Inputs[Search]->setPosition(250.f, 590.f);
	Inputs[Search]->setRange(HashTable::MIN_VALUE, HashTable::MAX_VALUE);
	mActionsHub.packOptionGUI(Search, Inputs[Search]);
}

void HashState::draw() {
	VisualState::draw();
	getContext().window->draw(mHashTable);
}

bool HashState::update(sf::Time dt) {
	bool result = true;
	result |= VisualState::update(dt);
	mHashTable.update(dt);
	return result;
}

bool HashState::handleEvent(const sf::Event& event) {
	VisualState::handleEvent(event);
	return false;
}

std::pair<std::vector<Animation>, std::string> HashState::getSteps(unsigned int option) {
	try {
		mHashTable.clearHighlight();
		switch (option) {
			case Insert:
				if (Inputs[Insert]->validate() != GUI::Input::Success)
					throw std::out_of_range("Value must be in range " +
					                        Inputs[Insert]->getStringRange());
				return mHashTable.insertAnimation(Inputs[Insert]->getValue());
			case Delete:
				break;
			case Search:
				if (Inputs[Search]->validate() != GUI::Input::Success)
					throw std::out_of_range("Value must be in range " +
					                        Inputs[Search]->getStringRange());
				return mHashTable.searchAnimation(Inputs[Search]->getValue());
			default:
				return VisualState::getSteps(option);
		}
	} catch (const std::exception& err) {
		mPlayer.callError(err.what());
	}
	return VisualState::getSteps(option);
}

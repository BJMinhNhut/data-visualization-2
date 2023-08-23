//
// Created by MINH NHUT on 8/23/2023.
//

#include "Tree234State.hpp"

#include "Template/Random.hpp"

Tree234State::Tree234State(StateStack& stack, State::Context context)
    : VisualState(stack, context, "2-3-4 Tree"),
      Inputs(NumOptions),
      mTree(*getContext().fonts, *getContext().colors) {
	mTree.setTargetPosition(context.window->getSize().x / 2.f + 200.f, 180.f,
	                        Tree234::Transition::None);
	initOptions();
	initCreate();
	initInsert();
	initSearch();
	initDelete();
}

void Tree234State::initOptions() {
	mActionsHub.addOption(Create, "Create", [&]() {
		mActionsHub.setCurrentOption(Create);
		//		mTree.flush();
		mPlayer.reset();
		mPlayer.callInfo("Init a new AVL tree");
	});
	mActionsHub.addOption(Insert, "Insert", [&]() {
		mActionsHub.setCurrentOption(Insert);
		//		mTree.flush();
		mPlayer.reset();
		mPlayer.callInfo("Insert a new value to AVL tree");
		Inputs[Insert]->randomizeValue();
	});
	mActionsHub.addOption(Delete, "Delete", [&]() {
		mActionsHub.setCurrentOption(Delete);
		//		mTree.flush();
		mPlayer.reset();
		mPlayer.callInfo("Delete a value from AVL tree");
		//		if (mTree.getSize() > 0)
		//			Inputs[Delete]->setValue(mTree.getRandomElement());
		//		else
		//			Inputs[Delete]->randomizeValue();
	});
	mActionsHub.addOption(Search, "Search", [&]() {
		mActionsHub.setCurrentOption(Search);
		//		mTree.flush();
		mPlayer.reset();
		mPlayer.callInfo("Search for a value in AVL tree");
		//		if (mTree.getSize() > 0)
		//			Inputs[Search]->setValue(mTree.getRandomElement());
		//		else
		//			Inputs[Search]->randomizeValue();
	});
}

void Tree234State::initCreate() {
	// Create
	auto emptyButton = std::make_shared<GUI::Button>(GUI::Button::Small, *getContext().fonts,
	                                                 *getContext().textures, *getContext().colors);
	emptyButton->setCallback([&]() {
		//		mTree.clear();
		//		mPlayer.callInfo("Created an empty AVL tree.");
	});
	emptyButton->setPosition(250.f, 590.f - 60.f);
	emptyButton->setText("Empty");
	mActionsHub.packOptionGUI(Create, emptyButton);

	auto randomButton = std::make_shared<GUI::Button>(GUI::Button::Small, *getContext().fonts,
	                                                  *getContext().textures, *getContext().colors);
	randomButton->setCallback([&]() {
		//		mTree.randomize();
		//		mPlayer.callInfo("Created an AVL tree with random elements, size = " +
		//		                 std::to_string(mTree.getSize()));
	});
	randomButton->setPosition(250.f, 590.f);
	randomButton->setText("Random");
	mActionsHub.packOptionGUI(Create, randomButton);

	auto fileButton = std::make_shared<GUI::Button>(GUI::Button::Small, *getContext().fonts,
	                                                *getContext().textures, *getContext().colors);
	fileButton->setCallback([&]() {
		//		std::string fileDir;
		//		if (selectedTextFile(fileDir))
		//			mTree.loadFromFile(fileDir);
		//		mPlayer.callInfo("Created an AVL tree with elements loaded from file, size = " +
		//		                 std::to_string(mTree.getSize()));
	});
	fileButton->setPosition(250.f, 590.f + 60.f);
	fileButton->setText("Load file");
	mActionsHub.packOptionGUI(Create, fileButton);
}

void Tree234State::initInsert() {
	// Insert
	auto valueLabel = std::make_shared<GUI::Label>(GUI::Label::Small, "Value", *getContext().fonts,
	                                               *getContext().colors);
	valueLabel->setPosition(250.f, 555.f);
	valueLabel->alignCenter();
	mActionsHub.packOptionGUI(Insert, valueLabel);

	Inputs[Insert] = std::make_shared<GUI::InputNum>(*getContext().fonts, *getContext().textures,
	                                                 *getContext().colors);
	Inputs[Insert]->setPosition(250.f, 590.f);
	//	Inputs[Insert]->setRange(AVLTree::MIN_VALUE, AVLTree::MAX_VALUE);
	mActionsHub.packOptionGUI(Insert, Inputs[Insert]);
}

void Tree234State::initSearch() {
	// Search
	auto valueLabel = std::make_shared<GUI::Label>(GUI::Label::Small, "Value", *getContext().fonts,
	                                               *getContext().colors);
	valueLabel->setPosition(250.f, 555.f);
	valueLabel->alignCenter();
	mActionsHub.packOptionGUI(Search, valueLabel);

	Inputs[Search] = std::make_shared<GUI::InputNum>(*getContext().fonts, *getContext().textures,
	                                                 *getContext().colors);
	Inputs[Search]->setPosition(250.f, 590.f);
	//	Inputs[Search]->setRange(AVLTree::MIN_VALUE, AVLTree::MAX_VALUE);
	mActionsHub.packOptionGUI(Search, Inputs[Search]);
}

void Tree234State::initDelete() {
	// Search
	auto valueLabel = std::make_shared<GUI::Label>(GUI::Label::Small, "Value", *getContext().fonts,
	                                               *getContext().colors);
	valueLabel->setPosition(250.f, 555.f);
	valueLabel->alignCenter();
	mActionsHub.packOptionGUI(Delete, valueLabel);

	Inputs[Delete] = std::make_shared<GUI::InputNum>(*getContext().fonts, *getContext().textures,
	                                                 *getContext().colors);
	Inputs[Delete]->setPosition(250.f, 590.f);
	//	Inputs[Delete]->setRange(AVLTree::MIN_VALUE, AVLTree::MAX_VALUE);
	mActionsHub.packOptionGUI(Delete, Inputs[Delete]);
}

void Tree234State::draw() {
	VisualState::draw();
	getContext().window->draw(mTree);
}

bool Tree234State::update(sf::Time dt) {
	bool result = true;
	result |= VisualState::update(dt);
	mTree.update(dt);
	return result;
}

bool Tree234State::handleEvent(const sf::Event& event) {
	VisualState::handleEvent(event);

	if (event.type == sf::Event::KeyReleased) {
		if (event.key.code == sf::Keyboard::Space)
			mTree.insert(1);
	}
	return false;
}

std::pair<std::vector<Animation>, std::string> Tree234State::getSteps(unsigned int option) {
	try {
		//		mTree.clearHighlight();
		//		switch (option) {
		//			case Insert:
		//				if (Inputs[Insert]->validate() != GUI::InputNum::Success)
		//					throw std::out_of_range("Value must be in range " +
		//					                        Inputs[Insert]->getStringRange());
		//				return mTree.insertAnimation(Inputs[Insert]->getValue());
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
		//			default:
		//				return VisualState::getSteps(option);
		//		}
	} catch (const std::exception& err) {
		mPlayer.callError(err.what());
	}
	return VisualState::getSteps(option);
}

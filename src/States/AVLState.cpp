//
// Created by MINH NHUT on 8/15/2023.
//

#include "AVLState.hpp"
#include "Template/Random.hpp"

AVLState::AVLState(StateStack& stack, State::Context context)
    : VisualState(stack, context, "AVL Tree"),
      Inputs(NumOptions),
      mTree(*getContext().fonts, *getContext().colors) {
	mTree.setTargetPosition(context.window->getSize().x / 2.f + 200.f, 180.f,
	                        AVLNode::Transition::None);
	initOptions();
	initCreate();
}

void AVLState::initOptions() {
	mActionsHub.addOption(Create, "Create", [&]() {
		mActionsHub.setCurrentOption(Create);
		mPlayer.reset();
		mPlayer.callInfo("Init a new AVL tree");
	});
	mActionsHub.addOption(Insert, "Insert", [&]() {
		mActionsHub.setCurrentOption(Insert);
		mPlayer.reset();
		mPlayer.callInfo("Insert a new value to heap");
		//		Inputs[Insert]->randomizeValue();
	});
	mActionsHub.addOption(Delete, "Delete", [&]() {
		mActionsHub.setCurrentOption(Delete);
		mPlayer.reset();
		mPlayer.callInfo("Delete a value from heap");
		//		Inputs[Delete]->setRange(AVLTree::MIN_VALUE, AVLTree::MAX_VALUE);
	});
	mActionsHub.addOption(Search, "Search", [&]() {
		mActionsHub.setCurrentOption(Search);
		mPlayer.reset();
		mPlayer.callInfo("Search for a value in hash table");
	});
}

void AVLState::initCreate() {
	// Create
	auto randomButton = std::make_shared<GUI::Button>(GUI::Button::Small, *getContext().fonts,
	                                                  *getContext().textures, *getContext().colors);
	randomButton->setCallback([&]() {
		mTree.randomize();
		mPlayer.callInfo("Created an AVL tree with random elements, size = " +
		                 std::to_string(mTree.getSize()));
	});
	randomButton->setPosition(250.f, 590.f - 30.f);
	randomButton->setText("Random");
	mActionsHub.packOptionGUI(Create, randomButton);

	auto fileButton = std::make_shared<GUI::Button>(GUI::Button::Small, *getContext().fonts,
	                                                *getContext().textures, *getContext().colors);
	fileButton->setCallback([&]() {
		std::string fileDir;
		if (selectedTextFile(fileDir))
			mTree.loadFromFile(fileDir);
		mPlayer.callInfo("Created an AVL tree with elements loaded from file, size = " +
		                 std::to_string(mTree.getSize()));
	});
	fileButton->setPosition(250.f, 590.f + 30.f);
	fileButton->setText("Load file");
	mActionsHub.packOptionGUI(Create, fileButton);
}

void AVLState::draw() {
	VisualState::draw();
	getContext().window->draw(mTree);
}

bool AVLState::update(sf::Time dt) {
	bool result = true;
	result |= VisualState::update(dt);
	mTree.update(dt);
	return result;
}

bool AVLState::handleEvent(const sf::Event& event) {
	VisualState::handleEvent(event);

	if (event.type == sf::Event::KeyReleased) {
		if (event.key.code == sf::Keyboard::I)
			mTree.insert(Random::getInt(AVLTree::MIN_VALUE, AVLTree::MAX_VALUE));
		else if (event.key.code == sf::Keyboard::Left)
			mTree.rotateLeft();
		else if (event.key.code == sf::Keyboard::Right)
			mTree.rotateRight();
	}
	return false;
}

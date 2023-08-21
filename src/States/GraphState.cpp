//
// Created by MINH NHUT on 8/21/2023.
//

#include "GraphState.hpp"

GraphState::GraphState(StateStack& stack, State::Context context)
    : VisualState(stack, context, "Graph"), mGraph(*context.fonts, *context.colors) {
	mGraph.setTargetPosition(context.window->getSize().x / 2.f + 200.f, 180.f,
	                         Graph::Transition::None);
	initOptions();
	initCreate();
}

void GraphState::initOptions() {
	mActionsHub.addOption(Create, "Create", [&]() {
		mActionsHub.setCurrentOption(Create);
		mPlayer.reset();
		mPlayer.callInfo("Init a new graph");
	});
}

void GraphState::initCreate() {
	// Create
	auto randomButton = std::make_shared<GUI::Button>(GUI::Button::Small, *getContext().fonts,
	                                                  *getContext().textures, *getContext().colors);
	randomButton->setCallback([&]() {
		mGraph.randomize(24, 24);
		mPlayer.callInfo("Created a graph with random elements, size = " +
		                 std::to_string(mGraph.getSize()));
	});
	randomButton->setPosition(250.f, 590.f);
	randomButton->setText("Random");
	mActionsHub.packOptionGUI(Create, randomButton);

	//	auto fileButton = std::make_shared<GUI::Button>(GUI::Button::Small, *getContext().fonts,
	//	                                                *getContext().textures, *getContext().colors);
	//	fileButton->setCallback([&]() {
	//		std::string fileDir;
	//		if (selectedTextFile(fileDir))
	//			mTree.loadFromFile(fileDir);
	//		mPlayer.callInfo("Created an AVL tree with elements loaded from file, size = " +
	//		                 std::to_string(mTree.getSize()));
	//	});
	//	fileButton->setPosition(250.f, 590.f + 60.f);
	//	fileButton->setText("Load file");
	//	mActionsHub.packOptionGUI(Create, fileButton);
}

void GraphState::draw() {
	VisualState::draw();
	getContext().window->draw(mGraph);
}

bool GraphState::update(sf::Time dt) {
	bool result = true;
	result |= VisualState::update(dt);
	mGraph.update(dt);
	return result;
}

bool GraphState::handleEvent(const sf::Event& event) {
	VisualState::handleEvent(event);
	return false;
}

std::pair<std::vector<Animation>, std::string> GraphState::getSteps(unsigned int option) {
	return VisualState::getSteps(option);
}
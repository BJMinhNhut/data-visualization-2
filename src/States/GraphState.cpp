//
// Created by MINH NHUT on 8/21/2023.
//

#include "GraphState.hpp"
#include "GUI/Panel.hpp"

GraphState::GraphState(StateStack& stack, State::Context context)
    : VisualState(stack, context, "Graph"), mGraph(*context.fonts, *context.colors) {
	mGraph.setTargetPosition(context.window->getSize().x / 2.f + 200.f, 150.f,
	                         Graph::Transition::None);
	initOptions();
	initCreate();
}

void GraphState::initOptions() {}

void GraphState::initCreate() {
	// Create
	auto sizeLabel = std::make_shared<GUI::Label>(GUI::Label::Small, "Nodes", *getContext().fonts,
	                                              *getContext().colors);
	sizeLabel->setPosition(190.f, 590.f - 80.f);
	sizeLabel->alignCenter();
	mActionsHub.packOptionGUI(Create, sizeLabel);

	auto nodesInput = std::make_shared<GUI::InputNum>(*getContext().fonts, *getContext().textures,
	                                                  *getContext().colors);
	nodesInput->setPosition(280.f, 590.f - 80.f);
	nodesInput->setRange(2, (int)Graph::MAX_SIZE);
	mActionsHub.packOptionGUI(Create, nodesInput);

	auto edgesLabel = std::make_shared<GUI::Label>(GUI::Label::Small, "Edges", *getContext().fonts,
	                                               *getContext().colors);
	edgesLabel->setPosition(190.f, 590.f - 30.f);
	edgesLabel->alignCenter();
	mActionsHub.packOptionGUI(Create, edgesLabel);

	auto edgesInput = std::make_shared<GUI::InputNum>(*getContext().fonts, *getContext().textures,
	                                                  *getContext().colors);
	edgesInput->setPosition(280.f, 590.f - 30.f);
	edgesInput->setRange(0, (int)Graph::MAX_EDGES);
	mActionsHub.packOptionGUI(Create, edgesInput);

	auto randomButton = std::make_shared<GUI::Button>(GUI::Button::Small, *getContext().fonts,
	                                                  *getContext().textures, *getContext().colors);
	randomButton->setCallback([&, nodesInput, edgesInput]() {
		if (nodesInput->validate() != GUI::InputNum::Success) {
			mPlayer.callError("Number of nodes must be in range " + nodesInput->getStringRange());
		} else if (edgesInput->validate() != GUI::InputNum::Success) {
			mPlayer.callError("Number of edges must be in range " + edgesInput->getStringRange());
		} else {
			mGraph.randomize(nodesInput->getValue(), edgesInput->getValue());
			mPlayer.callInfo("Created a graph with random elements, size = " +
			                 std::to_string(mGraph.getNumNodes()));
		}
	});
	randomButton->setPosition(250.f, 590.f + 20.f);
	randomButton->setText("Random");
	mActionsHub.packOptionGUI(Create, randomButton);

	auto horizon =
	    std::make_shared<GUI::Panel>(200.f, 0.f, getContext().colors->get(Colors::UIPrimary),
	                                 getContext().colors->get(Colors::UIBorder));
	horizon->setPosition(150.f, 590.f + 50.f);
	mActionsHub.packOptionGUI(Create, horizon);

	auto fileButton = std::make_shared<GUI::Button>(GUI::Button::Small, *getContext().fonts,
	                                                *getContext().textures, *getContext().colors);
	fileButton->setCallback([&]() {
		//			std::string fileDir;
		//			if (selectedTextFile(fileDir))
		//				mTree.loadFromFile(fileDir);
		//			mPlayer.callInfo("Created an AVL tree with elements loaded from file, size = " +
		//			                 std::to_string(mTree.getNumNodes()));
	});
	fileButton->setPosition(250.f, 590.f + 85.f);
	fileButton->setText("Load file");
	mActionsHub.packOptionGUI(Create, fileButton);

	mActionsHub.addOption(Create, "Create", [&, nodesInput, edgesInput]() {
		mActionsHub.setCurrentOption(Create);
		nodesInput->setValue(mGraph.getNumNodes());
		edgesInput->setValue(mGraph.getNumEdges());
		mPlayer.reset();
		mPlayer.callInfo("Init a new graph");
	});
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
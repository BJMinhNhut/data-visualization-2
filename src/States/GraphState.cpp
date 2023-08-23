//
// Created by MINH NHUT on 8/21/2023.
//

#include "GraphState.hpp"
#include "GUI/Button.hpp"
#include "GUI/Label.hpp"
#include "GUI/Panel.hpp"

GraphState::GraphState(StateStack& stack, State::Context context)
    : VisualState(stack, context, "Graph"), mGraph(*context.fonts, *context.colors) {
	mGraph.setTargetPosition(context.window->getSize().x / 2.f + 200.f, 150.f,
	                         Graph::Transition::None);
	initOptions();
	initCreate();
	initComponent();
	initSpanning();
	initDijkstra();
}

void GraphState::initOptions() {
	auto undirectedLabel = std::make_shared<GUI::Label>(GUI::Label::Main, "Undirected",
	                                                    *getContext().fonts, *getContext().colors);
	undirectedLabel->setPosition(20.f, 205.f);
	mDirect.pack(undirectedLabel);

	auto undirectedButton = std::make_shared<GUI::Button>(
	    GUI::Button::Checkbox, *getContext().fonts, *getContext().textures, *getContext().colors);
	undirectedButton->setToggle(true);
	undirectedButton->setCallback([this]() {
		mGraph.setDirected(false);
		mActionsHub.setCurrentOption(None);
		mPlayer.reset();
	});
	undirectedButton->setPosition(150.f, 210.f);
	mDirect.pack(undirectedButton);

	auto directedLabel = std::make_shared<GUI::Label>(GUI::Label::Main, "Directed",
	                                                  *getContext().fonts, *getContext().colors);
	directedLabel->setPosition(200.f, 205.f);
	mDirect.pack(directedLabel);

	auto directedButton = std::make_shared<GUI::Button>(
	    GUI::Button::Checkbox, *getContext().fonts, *getContext().textures, *getContext().colors);
	directedButton->setToggle(true);
	directedButton->setCallback([this]() {
		mGraph.setDirected(true);
		mActionsHub.setCurrentOption(None);
		mPlayer.reset();
	});
	directedButton->setPosition(310.f, 210.f);
	mDirect.pack(directedButton);

	mDirect.activateChild(undirectedButton);

	auto unweightedLabel = std::make_shared<GUI::Label>(GUI::Label::Main, "Unweighted",
	                                                    *getContext().fonts, *getContext().colors);
	unweightedLabel->setPosition(20.f, 265.f);
	mWeight.pack(unweightedLabel);

	auto unweightedButton = std::make_shared<GUI::Button>(
	    GUI::Button::Checkbox, *getContext().fonts, *getContext().textures, *getContext().colors);
	unweightedButton->setToggle(true);
	unweightedButton->setCallback([this]() {
		mGraph.setWeighted(false);
		mActionsHub.setCurrentOption(None);
		mPlayer.reset();
	});
	unweightedButton->setPosition(150.f, 270.f);
	mWeight.pack(unweightedButton);

	auto weightedLabel = std::make_shared<GUI::Label>(GUI::Label::Main, "Weighted",
	                                                  *getContext().fonts, *getContext().colors);
	weightedLabel->setPosition(200.f, 265.f);
	mWeight.pack(weightedLabel);

	auto weightedButton = std::make_shared<GUI::Button>(
	    GUI::Button::Checkbox, *getContext().fonts, *getContext().textures, *getContext().colors);
	weightedButton->setToggle(true);
	weightedButton->setCallback([this]() {
		mGraph.setWeighted(true);
		mActionsHub.setCurrentOption(None);
		mPlayer.reset();
	});
	weightedButton->setPosition(310.f, 270.f);
	mWeight.pack(weightedButton);

	mWeight.activateChild(weightedButton);
}

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
			mPlayer.callInfo("Created a graph with random elements, nodes = " +
			                 std::to_string(mGraph.getNumNodes()) +
			                 ", edges = " + std::to_string(mGraph.getNumEdges()));
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
	fileButton->setCallback([&, nodesInput, edgesInput]() {
		std::string fileDir;
		try {
			if (selectedTextFile(fileDir))
				mGraph.loadFromFile(fileDir);
			mPlayer.callInfo("Created a graph with random elements, nodes = " +
			                 std::to_string(mGraph.getNumNodes()) +
			                 ", edges = " + std::to_string(mGraph.getNumEdges()));
			nodesInput->setValue(mGraph.getNumNodes());
			edgesInput->setValue(mGraph.getNumEdges());
		} catch (std::exception& err) {
			mPlayer.callError(err.what());
		}
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

void GraphState::initComponent() {
	mActionsHub.addOption(Component, "C.Component", [&]() {
		mActionsHub.setCurrentOption(Component);
		mPlayer.reset();
		mPlayer.callInfo("Find connected components of the graph.");
	});
}

void GraphState::initSpanning() {
	mActionsHub.addOption(Spanning, "MST (Kruskal)", [&]() {
		mActionsHub.setCurrentOption(Spanning);
		mPlayer.reset();
		mPlayer.callInfo("Find minimum spanning tree of the graph.");
	});
}

void GraphState::initDijkstra() {
	mActionsHub.addOption(Dijkstra, "Dijkstra", [&]() {
		mActionsHub.setCurrentOption(Dijkstra);
		mPlayer.reset();
		mPlayer.callInfo(
		    "Find single shortest paths from a node of the graph to the others using Dijkstra.");
	});
}

void GraphState::draw() {
	VisualState::draw();
	getContext().window->draw(mGraph);
	getContext().window->draw(mDirect);
	getContext().window->draw(mWeight);
}

bool GraphState::update(sf::Time dt) {
	bool result = true;
	result |= VisualState::update(dt);
	mGraph.update(dt);
	mDirect.update(dt);
	mWeight.update(dt);
	return result;
}

bool GraphState::handleEvent(const sf::Event& event) {
	VisualState::handleEvent(event);
	mDirect.handleEvent(event);
	mWeight.handleEvent(event);
	return false;
}

std::pair<std::vector<Animation>, std::string> GraphState::getSteps(unsigned int option) {
	try {
		mGraph.clearHighlight();
		switch (option) {
			case Component:
				return mGraph.CCAnimation();
			case Spanning:
				return mGraph.MSTAnimation();
			case Dijkstra:
				return mGraph.DijkstraAnimation(0);
			default:
				return VisualState::getSteps(option);
		}
	} catch (const std::exception& err) {
		mPlayer.callError(err.what());
	}
	return VisualState::getSteps(option);
}
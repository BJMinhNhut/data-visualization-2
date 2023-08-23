//
// Created by MINH NHUT on 8/21/2023.
//

#ifndef DATAVISUALIZATION2_GRAPHSTATE_HPP
#define DATAVISUALIZATION2_GRAPHSTATE_HPP

#include "DataStructures/Graph/Graph.hpp"
#include "GUI/InputNum.hpp"
#include "VisualState.hpp"

class GraphState : public VisualState {
   public:
	GraphState(StateStack& stack, Context context);

	void draw() override;

	bool update(sf::Time dt) override;

	bool handleEvent(const sf::Event& event) override;

	std::pair<std::vector<Animation>, std::string> getSteps(unsigned int option) override;

   private:
	void initOptions();
	void initCreate();
	void initComponent();
	void initSpanning();
	void initDijkstra();

   private:
	enum Option {
		None,
		Create,
		Component,
		Spanning,
		Dijkstra,
		NumOptions,
	};
	Graph mGraph;
	GUI::Container mDirect, mWeight;
};

#endif  //DATAVISUALIZATION2_GRAPHSTATE_HPP

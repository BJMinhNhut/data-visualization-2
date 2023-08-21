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
	void initCreate();
	void initComponent();

   private:
	enum Option {
		None,
		Create,
		Component,
		Dijkstra,
		Spanning,
		NumOptions,
	};
	Graph mGraph;
};

#endif  //DATAVISUALIZATION2_GRAPHSTATE_HPP

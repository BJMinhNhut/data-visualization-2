//
// Created by MINH NHUT on 8/11/2023.
//

#ifndef DATAVISUALIZATION2_MINHEAPSTATE_HPP
#define DATAVISUALIZATION2_MINHEAPSTATE_HPP

#include "DataStructures/Heap/MinHeap.hpp"
#include "GUI/InputNum.hpp"
#include "VisualState.hpp"

class MinHeapState : public VisualState {
   public:
	MinHeapState(StateStack& stack, Context context);

	void draw() override;

	bool update(sf::Time dt) override;

	bool handleEvent(const sf::Event& event) override;

	std::pair<std::vector<Animation>, std::string> getSteps(unsigned int option) override;

   private:
	void initOptions();
	void initDetails();

   private:
	enum Option {
		None,
		Create,
		Push,
		Delete,
		Top,
		Size,
		NumOptions,
	};
	MinHeap mHeap;
	std::vector<GUI::InputNum::Ptr> Inputs;
};

#endif  //DATAVISUALIZATION2_MINHEAPSTATE_HPP

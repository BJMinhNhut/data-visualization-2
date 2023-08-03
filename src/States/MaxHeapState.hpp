//
// Created by MINH NHUT on 7/28/2023.
//

#ifndef DATAVISUALIZATION2_MAXHEAPSTATE_HPP
#define DATAVISUALIZATION2_MAXHEAPSTATE_HPP

#include "DataStructures/Heap/Heap.hpp"
#include "GUI/Input.hpp"
#include "VisualState.hpp"

class MaxHeapState : public VisualState {
   public:
	MaxHeapState(StateStack& stack, Context context);

	void draw() override;

	bool update(sf::Time dt) override;

	bool handleEvent(const sf::Event& event) override;

   private:
	void initOptions();
	void initDetails();
	void initActions();

   private:
	enum Option {
		None,
		Create,
		Push,
		Pop,
		Top,
		Size,
		NumOptions,
	};
	Heap mHeap;
	std::vector<GUI::Input::Ptr> Inputs;
};

#endif  //DATAVISUALIZATION2_MAXHEAPSTATE_HPP

//
// Created by MINH NHUT on 7/28/2023.
//

#ifndef DATAVISUALIZATION2_MAXHEAPSTATE_HPP
#define DATAVISUALIZATION2_MAXHEAPSTATE_HPP

#include "DataStructures/Heap/Heap.hpp"
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

   private:
	enum Option {
		None,
		Create,
		Push,
		Pop,
		Top,
		Size,
	};
	Heap mHeap;
};

#endif  //DATAVISUALIZATION2_MAXHEAPSTATE_HPP

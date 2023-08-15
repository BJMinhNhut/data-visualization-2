//
// Created by MINH NHUT on 8/15/2023.
//

#ifndef DATAVISUALIZATION2_AVLSTATE_HPP
#define DATAVISUALIZATION2_AVLSTATE_HPP

#include "GUI/Input.hpp"
#include "VisualState.hpp"

class AVLState : public VisualState {
   public:
	AVLState(StateStack& stack, Context context);

	void draw() override;

	bool update(sf::Time dt) override;

	bool handleEvent(const sf::Event& event) override;

   private:
	void initOptions();
	void initCreate();
	void initInsert();
	void initSearch();
	void initDelete();

   private:
	enum Option {
		None,
		Create,
		Insert,
		Delete,
		Search,
		NumOptions,
	};
	std::vector<GUI::Input::Ptr> Inputs;
};

#endif  //DATAVISUALIZATION2_AVLSTATE_HPP

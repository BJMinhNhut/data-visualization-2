//
// Created by MINH NHUT on 8/23/2023.
//

#ifndef DATAVISUALIZATION2_TREE234STATE_HPP
#define DATAVISUALIZATION2_TREE234STATE_HPP

#include "DataStructures/Tree234/Tree234.hpp"
#include "GUI/InputNum.hpp"
#include "VisualState.hpp"

class Tree234State : public VisualState {
   public:
	Tree234State(StateStack& stack, Context context);

	void draw() override;

	bool update(sf::Time dt) override;

	bool handleEvent(const sf::Event& event) override;

	std::pair<std::vector<Animation>, std::string> getSteps(unsigned int option) override;

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
	std::vector<GUI::InputNum::Ptr> Inputs;
	Tree234 mTree;
};

#endif  //DATAVISUALIZATION2_TREE234STATE_HPP

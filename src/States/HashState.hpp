//
// Created by MINH NHUT on 8/14/2023.
//

#ifndef DATAVISUALIZATION2_HASHSTATE_HPP
#define DATAVISUALIZATION2_HASHSTATE_HPP

#include "DataStructures/HashTable/HashTable.hpp"
#include "GUI/Input.hpp"
#include "VisualState.hpp"

class HashState : public VisualState {
   public:
	HashState(StateStack& stack, Context context);

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
	HashTable mHashTable;
	std::vector<GUI::Input::Ptr> Inputs;
};

#endif  //DATAVISUALIZATION2_HASHSTATE_HPP

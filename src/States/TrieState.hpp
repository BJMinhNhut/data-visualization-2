//
// Created by MINH NHUT on 8/18/2023.
//

#ifndef DATAVISUALIZATION2_TRIESTATE_HPP
#define DATAVISUALIZATION2_TRIESTATE_HPP

#include "DataStructures/Trie/Trie.hpp"
#include "GUI/InputStr.hpp"
#include "VisualState.hpp"

class TrieState : public VisualState {
   public:
	TrieState(StateStack& stack, Context context);

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
	std::vector<GUI::InputStr::Ptr> Inputs;
	Trie mTrie;
};

#endif  //DATAVISUALIZATION2_TRIESTATE_HPP

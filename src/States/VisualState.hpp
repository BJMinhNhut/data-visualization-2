//
// Created by MINH NHUT on 7/26/2023.
//

#ifndef DATAVISUALIZATION2_VISUALSTATE_HPP
#define DATAVISUALIZATION2_VISUALSTATE_HPP

#include "Visualizer/AnimationList.hpp"
//#include "GUI/CodeBlock.hpp"
//#include "GUI/Console.hpp"
#include "GUI/Button.hpp"
#include "GUI/Container.hpp"
#include "Template/State.hpp"
#include "Visualizer/ActionsHub.hpp"

#include <SFML/Graphics/Sprite.hpp>

class VisualState : public State {

   public:
	VisualState(StateStack& stack, Context context, const std::string& title = "");

	void draw() override;

	bool update(sf::Time dt) override;

	bool handleEvent(const sf::Event& event) override;

   protected:
	[[nodiscard]] static bool selectedTextFile(std::string& dir);

   private:
	void initGUIBase();

   protected:
	ActionsHub::Ptr mActionsHub;

   private:
	GUI::Container mGUIContainer;
};

#endif  //DATAVISUALIZATION2_VISUALSTATE_HPP

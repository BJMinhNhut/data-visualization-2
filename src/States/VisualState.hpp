//
// Created by MINH NHUT on 7/26/2023.
//

#ifndef DATAVISUALIZATION2_VISUALSTATE_HPP
#define DATAVISUALIZATION2_VISUALSTATE_HPP

//#include "GUI/CodeBlock.hpp"
//#include "GUI/Console.hpp"
#include "GUI/Button.hpp"
#include "GUI/Container.hpp"
#include "Template/State.hpp"
#include "Visualizer/ActionsHub.hpp"
#include "Visualizer/Player.hpp"

#include <SFML/Graphics/RenderWindow.hpp>
#include <SFML/Graphics/Sprite.hpp>

class VisualState : public State {

   public:
	VisualState(StateStack& stack, Context context, const std::string& title = "");

	void draw() override;
	bool update(sf::Time dt) override;
	bool handleEvent(const sf::Event& event) override;

	virtual std::pair<std::vector<Animation>, std::string> getSteps(unsigned int option);

   protected:
	[[nodiscard]] static bool selectedTextFile(std::string& dir);

   private:
	void initGUIBase();

   protected:
	ActionsHub mActionsHub;
	Player mPlayer;

   private:
	GUI::Container mGUIContainer;
};

#endif  //DATAVISUALIZATION2_VISUALSTATE_HPP

//
// Created by MINH NHUT on 7/26/2023.
//

#ifndef DATAVISUALIZATION2_VISUALSTATE_HPP
#define DATAVISUALIZATION2_VISUALSTATE_HPP

#include "Template/AnimationList.hpp"
//#include "GUI/CodeBlock.hpp"
//#include "GUI/Console.hpp"
#include "GUI/Container.hpp"
#include "States.hpp"

#include <SFML/Graphics/Sprite.hpp>

class VisualState : public State {

public:
    VisualState(StateStack &stack, Context context,
                const std::string &title = "");

    void draw() override;

    bool update(sf::Time dt) override;

    bool handleEvent(const sf::Event &event) override;

protected:
    void callError(const std::string &text);

    void callInfo(const std::string &text);

    void cleanLog();

    void addAnimation(
            const std::string &description,
            const std::vector<int> &highlightLineID,
            const std::function<void()> &forward = []() {},
            const std::function<void()> &backward = []() {});

    void clearAnimation();

    void loadCode(const std::string &code);

    void clearCode();

/*    std::shared_ptr<GUI::Button> createNewGUIButton(
            GUI::Button::Type type, sf::Vector2f position,
            std::string label, GUI::Button::Callback callback,
            bool toggle = false);*/

private:
    void initGUIButtons();

private:
    GUI::Container mGUIContainer;
//    GUI::Console::Ptr GUIConsole;
//    GUI::ProgressBar::Ptr GUIProgressBar;
//    GUI::CodeBlock::Ptr GUICodeBlock;

    // Graphics
    sf::Sprite mBackgroundSprite;
};


#endif //DATAVISUALIZATION2_VISUALSTATE_HPP

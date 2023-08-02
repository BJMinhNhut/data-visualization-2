//
// Created by MINH NHUT on 7/26/2023.
//

#include "VisualState.hpp"
#include "Template/Constants.hpp"
#include "GUI/Button.hpp"
#include "GUI/Label.hpp"
#include "GUI/Panel.hpp"
#include "GUI/Sprite.hpp"
#include "Template//ResourceHolder.hpp"
#include "Template/Utility.hpp"

#include <SFML/Graphics/RenderWindow.hpp>
#include <Template/portable-file-dialogs.h>

#include <iostream>

VisualState::VisualState(StateStack &stack, Context context,
                         const std::string &title)
        : State(stack, context),
          mGUIContainer(),
          mActionsHub(*context.textures, *context.fonts, *context.colors) {
    initGUIBase();

    auto titleBar = std::make_shared<GUI::Sprite>(
            context.textures->get(Textures::TitleBar));
    titleBar->setPosition(800.f, 30.f);
    mGUIContainer.pack(titleBar);

    auto titleLabel = std::make_shared<GUI::Label>(
            GUI::Label::Bold, title, *context.fonts, *context.colors);
    titleLabel->setPosition(titleBar->getPosition());
    titleLabel->alignCenter();
    mGUIContainer.pack(titleLabel);
}

std::string VisualState::selectedTextFile() {
    // File open dialog
    auto dialog = pfd::open_file("Select a text file", pfd::path::home(), {
            "Text Files (.txt)", "*.txt"
    });

// Do something while waiting for user input
    while (!dialog.ready(1000))
        std::cout << "Waited 1 second for user input...\n";

    std::cout << "Selected file: " << dialog.result()[0] << '\n';
    return dialog.result()[0];
}

void VisualState::initGUIBase() {
    auto background = std::make_shared<GUI::Sprite>(
            getContext().textures->get(Textures::Background));
    background->setPosition(getContext().window->getSize().x / 2.f, getContext().window->getSize().y / 2.f);
    mGUIContainer.pack(background);

    auto backButton = std::make_shared<GUI::Button>(
            GUI::Button::Back, *getContext().fonts, *getContext().textures,
            *getContext().colors);
    backButton->setPosition(610u, 30u);
    backButton->setCallback([this]() {
        requestStackPop();
        requestStackPush(States::DataMenu);
    });
    mGUIContainer.pack(backButton);

    auto homeButton = std::make_shared<GUI::Button>(
            GUI::Button::Home, *getContext().fonts, *getContext().textures,
            *getContext().colors);
    homeButton->setPosition(990u, 30u);
    homeButton->setCallback([this]() {
        requestStackPop();
        requestStackPush(States::Menu);
    });
    mGUIContainer.pack(homeButton);

    mActionsHub.setPosition(0.f, 100.f);
}

void VisualState::draw() {
    sf::RenderWindow &window = *getContext().window;
    window.setView(window.getDefaultView());

    window.draw(mGUIContainer);
    window.draw(mActionsHub);
}

bool VisualState::update(sf::Time dt) {
    mGUIContainer.update(dt);
    mActionsHub.update(dt);
    return true;
}

bool VisualState::handleEvent(const sf::Event &event) {
    mGUIContainer.handleEvent(event);
    mActionsHub.handleEvent(event);
    return false;
}

/*
 * TODO: Animation Structure
 *  - [] Each GUI component has their class (Console, Controller, CodeBlock,...)
 *  - [] GUI::Controller: Play/Pause/Replay/..,
 *  - [] AnimationList inside GUI::Controller
 *  - [] AnimationList keep pointer to Console and CodeBlock
 *  - [] Animation include Console Log text and Highlight lines.
 *  - [] When running AnimationList, it loads Log text and HighlightLines to corresponding pointer.
 *  - [] Main Data Structure return AnimationList to load into GUI:Controller
 *  - [x] File dialog call, return user's file name
 */


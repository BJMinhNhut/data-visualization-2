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
          mBackgroundSprite(context.textures->get(Textures::Background)) {

    auto titleBar = std::make_shared<GUI::Sprite>(
            context.textures->get(Textures::TitleBar));
    titleBar->setPosition(800.f, 30.f);
    mGUIContainer.pack(titleBar);

    auto titleLabel = std::make_shared<GUI::Label>(
            GUI::Label::Bold, title, *context.fonts, *context.colors);
    titleLabel->setPosition(titleBar->getPosition());
    titleLabel->alignCenter();
    mGUIContainer.pack(titleLabel);

    initGUIButtons();
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

void VisualState::initGUIButtons() {
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
}

void VisualState::callError(const std::string &text) {
//    GUIConsole->log(GUI::Console::Error, text);
}

void VisualState::callInfo(const std::string &text) {
//    GUIConsole->log(GUI::Console::Info, text);
}

void VisualState::cleanLog() {
//    GUIConsole->clean();
}

void VisualState::loadCode(const std::string &code) {
//    GUICodeBlock->loadCode(code);
}

void VisualState::clearCode() {
//    GUICodeBlock->loadCode("");
}

void VisualState::draw() {
    sf::RenderWindow &window = *getContext().window;
    window.setView(window.getDefaultView());

    window.draw(mBackgroundSprite);
    window.draw(mGUIContainer);
}

bool VisualState::update(sf::Time dt) {
    mGUIContainer.update(dt);
    return true;
}

bool VisualState::handleEvent(const sf::Event &event) {
    mGUIContainer.handleEvent(event);
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


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

    initGUIPanels();
    initGUIButtons();
    initConsole();
}

void VisualState::initGUIPanels() {
    auto codePanel = std::make_shared<GUI::Panel>(
            500.f, 300.f, getContext().colors->get(Colors::UISecondary),
            getContext().colors->get(Colors::UIBorder));
    codePanel->setPosition(800.f,
                           getContext().window->getSize().y - 450.f);

    auto progressPanel = std::make_shared<GUI::Panel>(
            500.f, 100.f, getContext().colors->get(Colors::UIPrimary),
            getContext().colors->get(Colors::UIBorder));
    progressPanel->setPosition(
            800.f, getContext().window->getSize().y - 150.f);

    auto consolePanel = std::make_shared<GUI::Panel>(
            500.f, 100.f, getContext().colors->get(Colors::UISecondary),
            getContext().colors->get(Colors::UIBorder));
    consolePanel->setPosition(
            300.f, getContext().window->getSize().y - 450.f);

    auto commandPanel = std::make_shared<GUI::Panel>(
            200.f, 300.f, getContext().colors->get(Colors::UIPrimary),
            getContext().colors->get(Colors::UIBorder));
    commandPanel->setPosition(
            300.f, getContext().window->getSize().y - 350.f);

    auto executePanel = std::make_shared<GUI::Panel>(
            300.f, 300.f, getContext().colors->get(Colors::UIPrimary),
            getContext().colors->get(Colors::UIBorder));
    executePanel->setPosition(
            500.f, getContext().window->getSize().y - 350.f);

    mGUIContainer.pack(consolePanel);
    mGUIContainer.pack(executePanel);
    mGUIContainer.pack(commandPanel);
    mGUIContainer.pack(codePanel);
    mGUIContainer.pack(progressPanel);
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
            GUI::Button::Back, *getContext().fonts, *getContext().textures,
            *getContext().colors);
    homeButton->setPosition(990u, 30u);
    homeButton->setCallback([this]() {
        requestStackPop();
        requestStackPush(States::Menu);
    });
    mGUIContainer.pack(homeButton);
}

void VisualState::initConsole() {
//    GUIConsole = std::make_shared<GUI::Console>(*getContext().fonts,
//                                                *getContext().colors);
//    GUIConsole->setPosition(315.f,
//                            getContext().window->getSize().y - 440.f);
//    mGUIContainer.pack(GUIConsole);
//
//    GUIProgressBar = std::make_shared<GUI::ProgressBar>(
//            *getContext().colors, sf::Vector2f(500.f, 5.f));
//    GUIProgressBar->setPosition(
//            800.f, getContext().window->getSize().y - 155.f);
//    mGUIContainer.pack(GUIProgressBar);
//
//    GUICodeBlock = std::make_shared<GUI::CodeBlock>(
//            *getContext().fonts, *getContext().colors);
//    GUICodeBlock->setPosition(
//            800.f, getContext().window->getSize().y - 450.f);
//    mGUIContainer.pack(GUICodeBlock);
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
 *  - [] GUI::Controller: Play/Pause/Replay/..,
 *  - [] AnimationList inside GUI::Controller
 *  - [] AnimationList keep pointer to Console and CodeBlock
 *  - [] Animation include Console Log text and Highlight lines.
 *  - [] When running AnimationList, it loads Log text and HighlightLines to corresponding pointer.
 *  - [] Main Data Structure return AnimationList to load into GUI:Controller
 */


//
// Created by MINH NHUT on 7/15/2023.
//

#include "DataState.hpp"
#include "GUI/Button.hpp"
#include "GUI/Label.hpp"
#include "GUI/Sprite.hpp"
#include "Template/Utility.hpp"

#include <SFML/Graphics/RenderWindow.hpp>

#include <memory>

DataState::DataState(StateStack &stack, Context context)
        : State(stack, context),
          mGUIContainer(),
          mBackgroundSprite(context.textures->get(Textures::Background)),
          mTitle(context.textures->get(Textures::Title)) {

    Utility::centerOrigin(mTitle);
    mTitle.setPosition(context.window->getSize().x / 2.f,
                       context.window->getSize().y / 4.f);

    auto backButton = std::make_shared<GUI::Button>(
            GUI::Button::Back, *getContext().fonts,
            *getContext().textures, *getContext().colors);
    backButton->setPosition(610u, 30u);
    backButton->setCallback([this]() {
        requestStackPop();
        requestStackPush(States::Menu);
    });
    mGUIContainer.pack(backButton);

    auto titleBar = std::make_shared<GUI::Sprite>(
            context.textures->get(Textures::TitleBar));
    titleBar->setPosition(800.f, 30.f);
    mGUIContainer.pack(titleBar);

    auto titleLabel = std::make_shared<GUI::Label>(
            GUI::Label::Bold, "Data Structure Menu", *context.fonts,
            *getContext().colors);
    titleLabel->setPosition(titleBar->getPosition());
    titleLabel->alignCenter();
    mGUIContainer.pack(titleLabel);

    auto HashButton = std::make_shared<GUI::Button>(
            GUI::Button::MenuHash, *context.fonts, *context.textures,
            *context.colors);
    HashButton->setPosition(
            context.window->getSize().x / 2.f - 275.f, 450.f);
    HashButton->setCallback([this]() {
//        requestStackPop();
//        requestStackPush(States::VisualDynamicArray);
    });
    mGUIContainer.pack(HashButton);

    auto AVLButton = std::make_shared<GUI::Button>(
            GUI::Button::MenuAVL, *context.fonts, *context.textures,
            *context.colors);
    AVLButton->setPosition(
            context.window->getSize().x / 2.f, 450.f);
    AVLButton->setCallback([this]() {
//        requestStackPop();
//        requestStackPush(States::VisualStaticArray);
    });
    mGUIContainer.pack(AVLButton);
//
    auto Tree234Button = std::make_shared<GUI::Button>(
            GUI::Button::Menu234, *context.fonts, *context.textures,
            *context.colors);
    Tree234Button->setPosition(context.window->getSize().x / 2.f + 275.f,
                           450.f);
    Tree234Button->setCallback([this]() {
//        requestStackPop();
//        requestStackPush(States::VisualSLL);
    });
    mGUIContainer.pack(Tree234Button);
//
//    auto DLLButton = std::make_shared<GUI::Button>(
//            GUI::Button::MenuDLL, *context.fonts, *context.textures,
//            *context.colors);
//    DLLButton->setPosition(context.window->getSize().x / 2.f, 580.f);
//    DLLButton->setCallback([this]() {
//        requestStackPop();
//        requestStackPush(States::VisualDLL);
//    });
//    mGUIContainer.pack(DLLButton);
//
//    auto CLLButton = std::make_shared<GUI::Button>(
//            GUI::Button::MenuCLL, *context.fonts, *context.textures,
//            *context.colors);
//    CLLButton->setPosition(context.window->getSize().x / 2.f + 280.f,
//                           580.f);
//    CLLButton->setCallback([this]() {
//        requestStackPop();
//        requestStackPush(States::VisualCLL);
//    });
//    mGUIContainer.pack(CLLButton);
//
//    auto StackButton = std::make_shared<GUI::Button>(
//            GUI::Button::MenuStack, *context.fonts, *context.textures,
//            *context.colors);
//    StackButton->setPosition(
//            context.window->getSize().x / 2.f - 140.f, 750.f);
//    StackButton->setCallback([this]() {
//        requestStackPop();
//        requestStackPush(States::VisualStack);
//    });
//    mGUIContainer.pack(StackButton);
//
    auto GraphButton = std::make_shared<GUI::Button>(
            GUI::Button::MenuGraph, *context.fonts, *context.textures,
            *context.colors);
    GraphButton->setPosition(
            context.window->getSize().x / 2.f + 375.f, 630.f);
    GraphButton->setCallback([this]() {
//        requestStackPop();
//        requestStackPush(States::VisualQueue);
    });
    mGUIContainer.pack(GraphButton);
}

void DataState::draw() {
    sf::RenderWindow &window = *getContext().window;
    window.setView(window.getDefaultView());

    window.draw(mBackgroundSprite);
    window.draw(mTitle);
    window.draw(mGUIContainer);
}

bool DataState::update(sf::Time dt) {
    return true;
}

bool DataState::handleEvent(const sf::Event &event) {
    mGUIContainer.handleEvent(event);
    return false;
}
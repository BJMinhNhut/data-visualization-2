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

//    auto StaticButton = std::make_shared<GUI::Button>(
//            GUI::Button::MenuStatic, *context.fonts, *context.textures,
//            *context.colors);
//    StaticButton->setPosition(
//            context.window->getSize().x / 2.f - 140.f, 410.f);
//    StaticButton->setCallback([this]() {
//        requestStackPop();
//        requestStackPush(States::VisualStaticArray);
//    });
//    mGUIContainer.pack(StaticButton);
//
//    auto DynamicButton = std::make_shared<GUI::Button>(
//            GUI::Button::MenuDynamic, *context.fonts, *context.textures,
//            *context.colors);
//    DynamicButton->setPosition(
//            context.window->getSize().x / 2.f + 140.f, 410.f);
//    DynamicButton->setCallback([this]() {
//        requestStackPop();
//        requestStackPush(States::VisualDynamicArray);
//    });
//    mGUIContainer.pack(DynamicButton);
//
//    auto SLLButton = std::make_shared<GUI::Button>(
//            GUI::Button::MenuSLL, *context.fonts, *context.textures,
//            *context.colors);
//    SLLButton->setPosition(context.window->getSize().x / 2.f - 280.f,
//                           580.f);
//    SLLButton->setCallback([this]() {
//        requestStackPop();
//        requestStackPush(States::VisualSLL);
//    });
//    mGUIContainer.pack(SLLButton);
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
//    auto QueueButton = std::make_shared<GUI::Button>(
//            GUI::Button::MenuQueue, *context.fonts, *context.textures,
//            *context.colors);
//    QueueButton->setPosition(
//            context.window->getSize().x / 2.f + 140.f, 750.f);
//    QueueButton->setCallback([this]() {
//        requestStackPop();
//        requestStackPush(States::VisualQueue);
//    });
//    mGUIContainer.pack(QueueButton);
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
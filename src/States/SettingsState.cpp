//
// Created by MINH NHUT on 7/4/2023.
//

#include "SettingsState.hpp"
#include "Template/Constants.hpp"
#include "GUI/Button.hpp"
#include "GUI/Label.hpp"
#include "GUI/Panel.hpp"
#include "GUI/Sprite.hpp"
#include "Template/Utility.hpp"

#include <SFML/Graphics/RenderWindow.hpp>

SettingsState::SettingsState(StateStack &stack, Context context)
        : State(stack, context),
          mGUIContainer(),
          themeContainer(),
          mSettings(getSettings()),
          mBackgroundSprite(context.textures->get(Textures::Background)) {

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

    auto titleLabel =
            std::make_shared<GUI::Label>(GUI::Label::Bold, "Settings",
                                         *context.fonts, *context.colors);
    titleLabel->setPosition(titleBar->getPosition());
    titleLabel->alignCenter();
    mGUIContainer.pack(titleLabel);

    auto panel = std::make_shared<GUI::Panel>(
            500.f, 200.f, context.colors->get(Colors::UISecondary),
            context.colors->get(Colors::UIBorder));
    panel->setPosition(800.f - 250.f, 450.f - 100.f);
    mGUIContainer.pack(panel);

    auto themeLabel = std::make_shared<GUI::Label>(
            GUI::Label::Bold, "Theme", *context.fonts, *context.colors);
    themeLabel->setPosition(800.f, 370.f);
    themeLabel->alignCenter();
    mGUIContainer.pack(themeLabel);

    auto applyButton = std::make_shared<GUI::Button>(
            GUI::Button::Big, *context.fonts, *context.textures,
            *context.colors);
    applyButton->setText("Apply");
    applyButton->setCallback([&]() {
        if (getSettings() != mSettings) {
            if (mSettings.theme == Settings::Themes::Light)
                Utility::loadLightTheme(*getContext().textures, *getContext().colors);
            else
                Utility::loadDarkTheme(*getContext().textures, *getContext().colors);
            updateSettings(mSettings);
            requestStackPop();
            requestStackPush(States::Settings);
        }
    });
    applyButton->setPosition(920.f, 510.f);
    mGUIContainer.pack(applyButton);

    auto lightLabel = std::make_shared<GUI::Label>(
            GUI::Label::Main, "Light", *context.fonts, *context.colors);
    lightLabel->setPosition(700.f, 405.f);
    themeContainer.pack(lightLabel);

    auto lightButton = std::make_shared<GUI::Button>(
            GUI::Button::Checkbox, *context.fonts, *context.textures,
            *context.colors);
    lightButton->setToggle(true);
    lightButton->setCallback(
            [this]() { mSettings.theme = Settings::Themes::Light; });
    lightButton->setPosition(770.f, 410.f);
    themeContainer.pack(lightButton);

    auto darkLabel = std::make_shared<GUI::Label>(
            GUI::Label::Main, "Dark", *context.fonts, *context.colors);
    darkLabel->setPosition(810.f, 405.f);
    themeContainer.pack(darkLabel);

    auto darkButton = std::make_shared<GUI::Button>(
            GUI::Button::Checkbox, *context.fonts, *context.textures,
            *context.colors);
    darkButton->setToggle(true);
    darkButton->setCallback(
            [this]() { mSettings.theme = Settings::Themes::Dark; });
    darkButton->setPosition(880.f, 410.f);
    themeContainer.pack(darkButton);

    if (mSettings.theme == Settings::Themes::Light) {
        themeContainer.activateChild(lightButton);
    } else
        themeContainer.activateChild(darkButton);
}

void SettingsState::draw() {
    sf::RenderWindow &window = *getContext().window;
    window.setView(window.getDefaultView());

    window.draw(mBackgroundSprite);
    window.draw(mGUIContainer);
    window.draw(themeContainer);
}

bool SettingsState::update(sf::Time dt) {
    return true;
}

bool SettingsState::handleEvent(const sf::Event &event) {
    mGUIContainer.handleEvent(event);
    themeContainer.handleEvent(event);
    return false;
}
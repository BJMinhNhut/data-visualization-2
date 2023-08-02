//
// Created by MINH NHUT on 8/2/2023.
//

#include "ActionsHub.hpp"
#include "GUI/Label.hpp"
#include "GUI/Panel.hpp"

#include <SFML/Graphics/RenderTarget.hpp>
#include <SFML/Graphics/RenderStates.hpp>

const int ActionsHub::MAX_ACTIONS = 5;

ActionsHub::ActionsHub(const TextureHolder &textures, const FontHolder &fonts, const ColorHolder &colors) :
        mCurrentOption(0), mGUIContainer(), mGUICommands(1),
        mTextures(textures), mFonts(fonts), mColors(colors) {

    auto optionPanel = std::make_shared<GUI::Panel>(
            150.f, 250, colors.get(Colors::UIPrimary),
            colors.get(Colors::UIBorder));
    optionPanel->setPosition(0, 50.f);
    mGUIContainer.pack(optionPanel);

    auto detailPanel = std::make_shared<GUI::Panel>(
            200.f, 250.f, colors.get(Colors::UISecondary),
            colors.get(Colors::UIBorder));
    detailPanel->setPosition(
            150, 50.f);
    mGUIContainer.pack(detailPanel);

    auto titlePanel = std::make_shared<GUI::Panel>(
            350.f, 50.f, colors.get(Colors::UIPrimary), colors.get(Colors::UIBorder));
    mGUIContainer.pack(titlePanel);

    auto title = std::make_shared<GUI::Label>(GUI::Label::Bold, "Actions",
                                              fonts, colors);
    title->setPosition(175.f, 25.f);
    title->alignCenter();
    mGUIContainer.pack(title);
}

void ActionsHub::draw(sf::RenderTarget &target, sf::RenderStates states) const {
    states.transform *= getTransform();
    target.draw(mGUIContainer, states);
    target.draw(mGUICommands[mCurrentOption], states);
}

bool ActionsHub::update(sf::Time dt) {
    return true;
}

bool ActionsHub::handleEvent(const sf::Event &event) {
    return false;
}
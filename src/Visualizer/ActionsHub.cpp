//
// Created by MINH NHUT on 8/2/2023.
//

#include "ActionsHub.hpp"
#include "GUI/Label.hpp"
#include "GUI/Panel.hpp"

#include <SFML/Graphics/RenderStates.hpp>
#include <SFML/Graphics/RenderTarget.hpp>

const int ActionsHub::MAX_ACTIONS = 5;

ActionsHub::ActionsHub(const TextureHolder& textures, const FontHolder& fonts,
                       const ColorHolder& colors)
    : mCurrentOption(0),
      mGUIContainer(),
      mGUICommands(MAX_ACTIONS),
      mTextures(textures),
      mFonts(fonts),
      mColors(colors) {

	auto detailPanel = std::make_shared<GUI::Panel>(200.f, 250.f, colors.get(Colors::UISecondary),
	                                                colors.get(Colors::UIBorder));
	detailPanel->setPosition(150, 150.f);
	mGUIContainer.pack(detailPanel);

	auto optionPanel = std::make_shared<GUI::Panel>(150.f, 250, colors.get(Colors::UIPrimary),
	                                                colors.get(Colors::UIBorder));
	optionPanel->setPosition(0, 150.f);
	mGUIContainer.pack(optionPanel);

	auto titlePanel = std::make_shared<GUI::Panel>(350.f, 50.f, colors.get(Colors::UIPrimary),
	                                               colors.get(Colors::UIBorder));
	titlePanel->setPosition(0.f, 100.f);
	mGUIContainer.pack(titlePanel);

	auto title = std::make_shared<GUI::Label>(GUI::Label::Bold, "Actions", fonts, colors);
	title->setPosition(175.f, 125.f);
	title->alignCenter();
	mGUIContainer.pack(title);
}

void ActionsHub::addOption(int option, const std::string& title,
                           const GUI::Button::Callback& callback) {
	auto button = std::make_shared<GUI::Button>(GUI::Button::Command, mFonts, mTextures, mColors);
	button->setToggle(true);
	button->setCallback(callback);
	button->setPosition(75.f, 125.f + 50.f * (float)option);
	button->setText(title);
	mGUIContainer.pack(button);
}

void ActionsHub::setCurrentOption(int option) {
	mCurrentOption = option;
	mGUICommands[option].reset();
}

void ActionsHub::draw(sf::RenderTarget& target, sf::RenderStates states) const {
	states.transform *= getTransform();
	target.draw(mGUIContainer, states);
	target.draw(mGUICommands[mCurrentOption], states);
}

bool ActionsHub::update(sf::Time dt) {
	mGUIContainer.update(dt);
	return true;
}

bool ActionsHub::handleEvent(const sf::Event& event) {
	mGUIContainer.handleEvent(event);
	return false;
}

unsigned int ActionsHub::getCurrentOption() const {
	return mCurrentOption;
}
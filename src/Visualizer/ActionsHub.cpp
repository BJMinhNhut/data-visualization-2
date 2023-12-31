//
// Created by MINH NHUT on 8/2/2023.
//

#include "ActionsHub.hpp"
#include "GUI/Label.hpp"
#include "GUI/Panel.hpp"

#include <SFML/Graphics/RenderStates.hpp>
#include <SFML/Graphics/RenderTarget.hpp>
#include <SFML/Window/Event.hpp>

#include <cmath>
#include <utility>

const int ActionsHub::MAX_ACTIONS = 5;

ActionsHub::ActionsHub(const TextureHolder& textures, const FontHolder& fonts,
                       const ColorHolder& colors)
    : mCurrentOption(0),
      mGUIContainer(),
      mGUICommands(MAX_ACTIONS + 1),
      mTextures(textures),
      mFonts(fonts),
      mColors(colors) {

	auto detailPanel = std::make_shared<GUI::Panel>(200.f, 240.f, colors.get(Colors::UISecondary),
	                                                colors.get(Colors::UIBorder));
	detailPanel->setPosition(150, 470.f);
	mGUIContainer.pack(detailPanel);

	auto optionPanel = std::make_shared<GUI::Panel>(150.f, 240.f, colors.get(Colors::UIPrimary),
	                                                colors.get(Colors::UIBorder));
	optionPanel->setPosition(0, 470.f);
	mGUIContainer.pack(optionPanel);
}

void ActionsHub::addOption(int option, const std::string& title, GUI::Button::Callback callback) {
	static const float HEIGHT = 45.f;
	auto button = std::make_shared<GUI::Button>(GUI::Button::Command, mFonts, mTextures, mColors);
	button->setToggle(true);
	button->setCallback(std::move(callback));
	button->setPosition(75.f, 470.f - std::floor(HEIGHT / 2.f) + 10.f + HEIGHT * (float)option);
	button->setText(title);
	mGUIContainer.pack(button);
}

void ActionsHub::packOptionGUI(int option, GUI::Component::Ptr component) {
	mGUICommands[option].pack(std::move(component));
}

void ActionsHub::setCurrentOption(int option) {
	if (option == 0)
		mGUIContainer.reset();
	mGUICommands[getCurrentOption()].reset();
	mCurrentOption = option;
}

unsigned int ActionsHub::getCurrentOption() const {
	return mCurrentOption;
}

void ActionsHub::draw(sf::RenderTarget& target, sf::RenderStates states) const {
	states.transform *= getTransform();
	target.draw(mGUIContainer, states);
	target.draw(mGUICommands[mCurrentOption], states);
}

bool ActionsHub::update(sf::Time dt) {
	mGUIContainer.update(dt);
	mGUICommands[mCurrentOption].update(dt);
	return true;
}

bool ActionsHub::handleEvent(const sf::Event& event) {
	mGUIContainer.handleEvent(event);
	mGUICommands[mCurrentOption].handleEvent(event);

	return false;
}
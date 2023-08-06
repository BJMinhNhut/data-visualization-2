//
// Created by MINH NHUT on 8/6/2023.
//

#include "Player.hpp"
#include "GUI/Panel.hpp"

#include <SFML/Graphics/RenderStates.hpp>
#include <SFML/Graphics/RenderTarget.hpp>

const std::vector<std::pair<std::string, float>> Player::mSpeedMap(
    {{"x0.5", 0.5f}, {"x1.0", 1.f}, {"x2.0", 2.f}, {"x5.0", 5.f}});

Player::Player(const TextureHolder& textures, const FontHolder& fonts, const ColorHolder& colors)
    : mTextures(textures), mFonts(fonts), mColors(colors), mGUIContainer(), mSpeedID(1) {
	auto codePanel = std::make_shared<GUI::Panel>(350.f, 270.f, colors.get(Colors::UISecondary),
	                                              colors.get(Colors::UIBorder));
	codePanel->setPosition(0.f, 100.f);
	mGUIContainer.pack(codePanel);

	auto consolePanel = std::make_shared<GUI::Panel>(350.f, 100.f, colors.get(Colors::UISecondary),
	                                                 colors.get(Colors::UIBorder));
	consolePanel->setPosition(0.f, 370.f);
	mGUIContainer.pack(consolePanel);

	auto playerPanel = std::make_shared<GUI::Panel>(350.f, 100.f, colors.get(Colors::UIPrimary),
	                                                colors.get(Colors::UIBorder));
	playerPanel->setPosition(0.f, 710.f);
	mGUIContainer.pack(playerPanel);

	mConsole = std::make_shared<GUI::Console>(fonts, colors, 30);
	mConsole->setPosition(consolePanel->getPosition() + sf::Vector2f(10.f, 10.f));
	mConsole->log(GUI::Console::Info, "");
	mGUIContainer.pack(mConsole);

	mCodeBlock = std::make_shared<GUI::CodeBlock>(fonts, colors);
	mCodeBlock->setPosition(codePanel->getPosition());
	mGUIContainer.pack(mCodeBlock);
}

void Player::loadCode(const std::string& code) {
	mCodeBlock->loadCode(code);
}

void Player::clearCode() {
	mCodeBlock->loadCode("");
}

void Player::callError(const std::string& text) {
	mConsole->log(GUI::Console::Error, text);
}

void Player::callInfo(const std::string& text) {
	mConsole->log(GUI::Console::Info, text);
}

void Player::cleanLog() {
	mConsole->clean();
}

void Player::draw(sf::RenderTarget& target, sf::RenderStates states) const {
	states.transform *= getTransform();
	target.draw(mGUIContainer, states);
}

void Player::update(sf::Time dt) {
	mGUIContainer.update(dt);
}

void Player::handleEvent(const sf::Event& event) {
	mGUIContainer.handleEvent(event);
}
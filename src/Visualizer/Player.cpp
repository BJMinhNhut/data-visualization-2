//
// Created by MINH NHUT on 8/6/2023.
//

#include "Player.hpp"
#include "GUI/Panel.hpp"

#include <SFML/Graphics/RenderStates.hpp>
#include <SFML/Graphics/RenderTarget.hpp>

#include <cmath>
#include <iostream>

const std::vector<std::pair<std::string, float>> Player::mSpeedMap(
    {{"x0.5", 0.5f}, {"x1.0", 1.f}, {"x2.0", 2.f}, {"x5.0", 5.f}, {"x10", 10.f}});

Player::Player(const TextureHolder& textures, const FontHolder& fonts, const ColorHolder& colors,
               const std::function<void()>& playCallback)
    : mGUIContainer(),
      mSpeedID(1),
      ControllerGUI(numStates),
      playButtons(numStates),
      mConsole(std::make_shared<GUI::Console>(fonts, colors, 30)),
      mCodeBlock(std::make_shared<GUI::CodeBlock>(fonts, colors)),
      mAnimationList(mCodeBlock, mConsole) {

	// CodeBlock
	auto codePanel = std::make_shared<GUI::Panel>(350.f, 270.f, colors.get(Colors::UISecondary),
	                                              colors.get(Colors::UIBorder));
	codePanel->setPosition(0.f, 100.f);
	mGUIContainer.pack(codePanel);

	mCodeBlock->setPosition(codePanel->getPosition());
	mGUIContainer.pack(mCodeBlock);

	// Console
	auto consolePanel = std::make_shared<GUI::Panel>(350.f, 100.f, colors.get(Colors::UISecondary),
	                                                 colors.get(Colors::UIBorder));
	consolePanel->setPosition(0.f, 370.f);
	mGUIContainer.pack(consolePanel);

	mConsole->setPosition(consolePanel->getPosition() + sf::Vector2f(10.f, 10.f));
	mConsole->log(GUI::Console::Info, "");
	mGUIContainer.pack(mConsole);

	// Player
	auto playerPanel = std::make_shared<GUI::Panel>(350.f, 100.f, colors.get(Colors::UIPrimary),
	                                                colors.get(Colors::UIBorder));
	playerPanel->setPosition(0.f, 710.f);
	mGUIContainer.pack(playerPanel);

	const sf::Vector2f PLAYER_CENTER =
	    playerPanel->getPosition() +
	    sf::Vector2f(std::round(350.f / 2.f) - 25.f, std::round(100.f / 2.f));

	playButtons[Play] = std::make_shared<GUI::Button>(GUI::Button::Play, fonts, textures, colors);
	playButtons[Play]->setPosition(PLAYER_CENTER);
	playButtons[Play]->setCallback(playCallback);
	ControllerGUI[Play].pack(playButtons[Play]);

	playButtons[Pause] = std::make_shared<GUI::Button>(GUI::Button::Pause, fonts, textures, colors);
	playButtons[Pause]->setPosition(PLAYER_CENTER);
	playButtons[Pause]->setCallback([&]() { mAnimationList.pause(); });
	ControllerGUI[Pause].pack(playButtons[Pause]);

	playButtons[Replay] =
	    std::make_shared<GUI::Button>(GUI::Button::Replay, fonts, textures, colors);
	playButtons[Replay]->setPosition(PLAYER_CENTER);
	playButtons[Replay]->setCallback([&]() {
		mAnimationList.goToFront();
		mAnimationList.play();
	});
	ControllerGUI[Replay].pack(playButtons[Replay]);

	auto front = std::make_shared<GUI::Button>(GUI::Button::DoubleArrow, fonts, textures, colors);
	front->setPosition(PLAYER_CENTER + sf::Vector2f(-90.f, 0.f));
	mGUIContainer.pack(front);

	auto previous = std::make_shared<GUI::Button>(GUI::Button::Arrow, fonts, textures, colors);
	previous->setPosition(PLAYER_CENTER + sf::Vector2f(-52.f, 0.f));
	previous->setRotation(180);
	mGUIContainer.pack(previous);

	auto next = std::make_shared<GUI::Button>(GUI::Button::Arrow, fonts, textures, colors);
	next->setPosition(PLAYER_CENTER + sf::Vector2f(52.f, 0.f));
	mGUIContainer.pack(next);

	auto back = std::make_shared<GUI::Button>(GUI::Button::DoubleArrow, fonts, textures, colors);
	back->setPosition(PLAYER_CENTER + sf::Vector2f(90.f, 0.f));
	back->setRotation(180);
	mGUIContainer.pack(back);

	// Speed
	mSpeed =
	    std::make_shared<GUI::Label>(GUI::Label::Mono, mSpeedMap[mSpeedID].first, fonts, colors);
	mSpeed->setPosition(PLAYER_CENTER + sf::Vector2f(150.f, 0.f));
	mSpeed->alignCenter();
	mGUIContainer.pack(mSpeed);

	auto speedUp = std::make_shared<GUI::Button>(GUI::Button::SmallArrow, fonts, textures, colors);
	speedUp->setPosition(mSpeed->getPosition() + sf::Vector2f(0.f, -20.f));
	speedUp->setCallback([&] { increaseSpeed(); });
	speedUp->rotate(180);
	mGUIContainer.pack(speedUp);

	auto speedDown =
	    std::make_shared<GUI::Button>(GUI::Button::SmallArrow, fonts, textures, colors);
	speedDown->setPosition(mSpeed->getPosition() + sf::Vector2f(0.f, 20.f));
	speedDown->setCallback([&] { decreaseSpeed(); });
	mGUIContainer.pack(speedDown);
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

Player::State Player::getCurrentState() const {
	if (mAnimationList.isPlaying())
		return Pause;
	if (mAnimationList.isFinished())
		return Replay;
	return Play;
}

void Player::loadAnimation(const std::vector<Animation>& list, const std::string& code) {
	mCodeBlock->loadCode(code);
	mAnimationList.clear();
	for (auto& animation : list)
		mAnimationList.push(animation);
}

void Player::increaseSpeed() {
	if (mSpeedID + 1 < mSpeedMap.size()) {
		mSpeedID++;
		mSpeed->setText(mSpeedMap[mSpeedID].first);
		mAnimationList.setSpeed(mSpeedMap[mSpeedID].second);
	}
}

void Player::decreaseSpeed() {
	if (mSpeedID > 0) {
		mSpeedID--;
		mSpeed->setText(mSpeedMap[mSpeedID].first);
		mAnimationList.setSpeed(mSpeedMap[mSpeedID].second);
	}
}

void Player::draw(sf::RenderTarget& target, sf::RenderStates states) const {
	states.transform *= getTransform();
	target.draw(mGUIContainer, states);
	target.draw(ControllerGUI[getCurrentState()], states);
}

void Player::update(sf::Time dt) {
	mGUIContainer.update(dt);
	ControllerGUI[getCurrentState()].update(dt);
}

void Player::handleEvent(const sf::Event& event) {
	mGUIContainer.handleEvent(event);
	ControllerGUI[getCurrentState()].handleEvent(event);

	if (event.type == sf::Event::KeyReleased) {
		if (event.key.code == sf::Keyboard::Enter) {
			playButtons[getCurrentState()]->activate();
		}
	}
}
void Player::highlight(const std::vector<int>& lineIDs) {
	mCodeBlock->setHighlight(lineIDs);
}

//
// Created by MINH NHUT on 8/3/2023.
//

#include "Input.hpp"
#include "Template/Random.hpp"
#include "Template/Utility.hpp"

#include <SFML/Graphics/RenderStates.hpp>
#include <SFML/Graphics/RenderTarget.hpp>
#include <SFML/System/Time.hpp>
#include <SFML/Window/Event.hpp>

#include <iostream>

namespace GUI {
const sf::Time Input::CURSOR_LIFE = sf::milliseconds(400);
const int Input::MAX_LENGTH = 1000;
const int Input::DISPLAY_LENGTH = 9;

Input::Input(const FontHolder& fonts, const TextureHolder& textures, const ColorHolder& colors)
    : mNormalTexture(textures.get(Textures::InputNormal)),
      mSelectedTexture(textures.get(Textures::InputSelected)),
      mPressedTexture(textures.get(Textures::InputActivated)),
      mText("", fonts.get(Fonts::Mono), 18),
      cursorDrawable(true),
      mCursor(sf::Vector2f(2.f, 16.f)),
      cursorCountdown(CURSOR_LIFE),
      mSprite(mNormalTexture),
      mMaxValue(0),
      mMinValue(0),
      mValue(0) {

	mText.setFillColor(colors.get(Colors::Text));
	alignText();

	Utility::centerOrigin(mSprite);

	mCursor.setFillColor(colors.get(Colors::Text));
	mCursor.setOrigin(-2.f, 0.f);
}

void Input::setValue(const int& value) {
	assert(value >= mMinValue && value <= mMaxValue);
	mValue = value;
	buffer = std::to_string(mValue);
	mText.setString(buffer);
	alignText();
}

void Input::setRange(const int& minValue, const int& maxValue) {
	assert(minValue <= maxValue);
	mMinValue = minValue;
	mMaxValue = maxValue;
}

void Input::randomizeValue() {
	setValue(Random::getInt(mMinValue, mMaxValue));
}

void Input::clear() {
	std::string().swap(buffer);
	mText.setString(buffer);
	mValue = 0;
}

std::pair<int, int> Input::getRange() const {
	return std::make_pair(mMinValue, mMaxValue);
}

std::string Input::getStringRange() const {
	return '[' + std::to_string(mMinValue) + ',' + std::to_string(mMaxValue);
}

int Input::getValue() const {
	return mValue;
}

bool Input::isSelectable() const {
	return true;
}

void Input::select() {
	Component::select();
	mSprite.setTexture(mSelectedTexture, true);
}

void Input::deselect() {
	Component::deselect();
	mSprite.setTexture(mNormalTexture, true);
}

void Input::activate() {
	Component::activate();
#ifdef SFML_DEBUG
	std::cout << "Input activated\n";
#endif
	mSprite.setTexture(mPressedTexture, true);
}

void Input::deactivate() {
#ifdef SFML_DEBUG
	std::cout << "Input deactivated\n";
#endif
	Component::deactivate();

	// Reset texture to right one depending on if we are selected or not.
	if (isSelected())
		mSprite.setTexture(mSelectedTexture, true);
	else
		mSprite.setTexture(mNormalTexture, true);
}

bool Input::update(sf::Time dt) {
	if (isActive()) {
		cursorCountdown += dt;

		if (cursorCountdown > CURSOR_LIFE) {
			cursorDrawable ^= 1;
			cursorCountdown = sf::milliseconds(0.f);
		}
	} else
		cursorDrawable = false;
	return true;
}

bool Input::handleEvent(const sf::Event& event) {
	if (event.type == sf::Event::KeyPressed || event.type == sf::Event::TextEntered) {

		if (event.type == sf::Event::TextEntered) {
			// handle text input
#ifdef SFML_DEBUG
			std::cout << "text hit!\n";
#endif
			char mChar = static_cast<char>(event.text.unicode);
			if (isAllowed(mChar) && buffer.length() < MAX_LENGTH) {
				buffer.push_back(mChar);
			}
		} else if (event.type == sf::Event::KeyPressed) {
			if (event.key.code == sf::Keyboard::BackSpace) {
				// pop back buffer
				if (!buffer.empty())
					buffer.pop_back();
			}
		}

		if (validate() == Success) {
			mValue = stoi(buffer);
			buffer = std::to_string(mValue);
			mText.setString(buffer);
		} else
			mText.setString(buffer.substr(std::max(0, (int)buffer.length() - DISPLAY_LENGTH),
			                              std::min((int)buffer.length(), DISPLAY_LENGTH)));

		alignText();
	}
	return true;
}

bool Input::contains(sf::Vector2i point) const {
	sf::IntRect bounds(getPosition().x - mSprite.getGlobalBounds().width / 2.f,
	                   getPosition().y - mSprite.getGlobalBounds().height / 2.f,
	                   mSprite.getGlobalBounds().width, mSprite.getGlobalBounds().height);

	return bounds.contains(point);
}

void Input::draw(sf::RenderTarget& target, sf::RenderStates states) const {
	states.transform *= getTransform();
	target.draw(mSprite, states);
	target.draw(mText, states);

	if (cursorDrawable)
		target.draw(mCursor, states);
}

Input::ValidationResult Input::validate() const {
	if (!validateCharacter())
		return InvalidCharacter;
	try {
		int temp = stoi(buffer);
		if (temp < mMinValue || temp > mMaxValue)
			return InvalidValue;
	} catch (std::exception& err) {
		return InvalidLength;
	}
	return Success;
}

bool Input::validateCharacter() const {
	for (char mChar : buffer)
		if (!isAllowed(mChar)) {
			std::cerr << int(mChar) << " is not allowed\n";
			return false;
		}
	return true;
}

bool Input::isAllowed(const char& ch) {
	return std::isdigit(ch);  // positive integer only
}

void Input::alignText() {
	Utility::centerOrigin(mText);
	unsigned int lastIndex = mText.getString().getSize();

	if (mText.getString().isEmpty())
		mCursor.setPosition(0.f, -9.f);
	else
		mCursor.setPosition(mText.findCharacterPos((int)lastIndex - 1) + sf::Vector2f(10.f, 4.f));
}

}  // namespace GUI
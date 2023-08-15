//
// Created by MINH NHUT on 8/12/2023.
//

#include "ProgressBar.hpp"

#include <SFML/Graphics/RenderStates.hpp>
#include <SFML/Graphics/RenderTarget.hpp>

namespace GUI {
ProgressBar::ProgressBar(const ColorHolder& colors, const sf::Vector2f& size)
    : mLength(0), mProgress(0), mSize(size), mBar() {
	mBar.setFillColor(colors.get(Colors::Blue));
	updateBar();
}

bool ProgressBar::isSelectable() const {
	return false;
}

void ProgressBar::setLength(const int& length) {
	mLength = length;
	mProgress = std::min(mLength, mProgress);
	updateBar();
}

void ProgressBar::setProgress(const int& progress) {
	mProgress = progress;
	updateBar();
}

void ProgressBar::handleEvent(const sf::Event& event) {}

void ProgressBar::updateBar() {
	float width = static_cast<float>(mProgress + 1) / static_cast<float>(mLength) * mSize.x;
	mBar.setSize(sf::Vector2f(width, mSize.y));
}

void ProgressBar::draw(sf::RenderTarget& target, sf::RenderStates states) const {
	states.transform *= getTransform();
	if (mLength > 0)
		target.draw(mBar, states);
}

}  // namespace GUI
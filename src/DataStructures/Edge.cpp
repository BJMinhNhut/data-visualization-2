//
// Created by MINH NHUT on 7/31/2023.
//

#include "Edge.hpp"
#include "PolyNode.hpp"
#include "Template/Constants.hpp"
#include "Template/ResourceHolder.hpp"
#include "Template/Utility.hpp"

#include <SFML/Graphics/RenderStates.hpp>
#include <SFML/Graphics/RenderTarget.hpp>

#include <cmath>
#include <iostream>

const float Edge::THICKNESS = 2.f;

Edge::Edge(PolyNode* from, PolyNode* to, int type, const FontHolder& fonts,
           const ColorHolder& colors)
    : mFrom(from),
      mTo(to),
      mType(type),
      mUpdate(true),
      mColors(colors),
      mFonts(fonts),
      mText("", fonts.get(Fonts::Mono), 18u) {
	setColor(Colors::UIBorder);
}

void Edge::update(sf::Time dt) {
	if (mUpdate) {
		sf::Color color = mLine.getFillColor();
		mLine = getLineShape(mTo->getWorldPosition() - mFrom->getWorldPosition());
		mLine.setFillColor(color);
		if (mType & Edge::Directed) {
			mArrow = getArrowShape(mTo->getWorldPosition() - mFrom->getWorldPosition());
			mArrow.setFillColor(color);
		}
		if (mType & Edge::Weighted) {
			mText.setFillColor(color);
			mText.setPosition(getWeightPosition());
		}
		mUpdate = false;
	}
}

void Edge::draw(sf::RenderTarget& target, sf::RenderStates states) const {
	target.draw(mLine, states);
	if (mType & Directed)
		target.draw(mArrow, states);
	if (mType & Weighted)
		target.draw(mText, states);
}

sf::RectangleShape Edge::getLineShape(sf::Vector2f line) {
	float lineLength = sqrt(line.x * line.x + line.y * line.y) - mTo->getRadius();
	sf::RectangleShape rect(sf::Vector2f(lineLength, THICKNESS));
	sf::FloatRect bounds = rect.getLocalBounds();
	rect.setOrigin(0, std::floor(bounds.top + bounds.height / 2.f));

	float angle = atan2(line.y, line.x) / Constants::PI * 180.f;
	rect.rotate(angle);
	return rect;
}

sf::ConvexShape Edge::getArrowShape(sf::Vector2f line) {
	float lineLength = sqrt(line.x * line.x + line.y * line.y) - mTo->getRadius();
	static const float ARROW_EDGE = 10.f;
	float arrowLength = sqrt(3.f) / 2.f * ARROW_EDGE;

	sf::ConvexShape arrowTip(3);
	arrowTip.setPoint(0, sf::Vector2f(lineLength - arrowLength, ARROW_EDGE / 2.f));
	arrowTip.setPoint(1, sf::Vector2f(lineLength, 0.f));
	arrowTip.setPoint(2, sf::Vector2f(lineLength - arrowLength, -ARROW_EDGE / 2.f));

	float angle = atan2(line.y, line.x) / Constants::PI * 180.f;
	arrowTip.rotate(angle);
	return arrowTip;
}

sf::Vector2f Edge::getWeightPosition() {
	static const float OFF_SET = 15.f;
	sf::Vector2f delta = mTo->getWorldPosition() - mFrom->getWorldPosition();
	float x = (delta.x) / 2.f, y = (delta.y) / 2.f;
	sf::Vector2f mid(x, y);
	sf::Vector2f norm = sf::Vector2f(-y, x) / Utility::getNorm(mid) * OFF_SET;
	sf::Vector2f position(mid + norm);
	position.x = std::round(position.x);
	position.y = std::round(position.y);
	return position;
}

void Edge::setColor(Colors::ID color) {
	mLine.setFillColor(mColors.get(color));
	mText.setFillColor(mLine.getFillColor());
}

void Edge::setWeight(int weight) {
	mText.setString(std::to_string(weight));
	Utility::centerOrigin(mText);
}

void Edge::setType(int type) {
	mType = type;
}

void Edge::callUpdate() {
	mUpdate = true;
}

PolyNode* Edge::getTo() const {
	return mTo;
}

PolyNode* Edge::getFrom() const {
	return mFrom;
}

//
// Created by MINH NHUT on 7/27/2023.
//

#include "CircleNode.hpp"
#include "Template/Utility.hpp"
#include "Template/ResourceHolder.hpp"

#include <SFML/Graphics/RenderStates.hpp>
#include <SFML/Graphics/RenderTarget.hpp>


CircleNode::CircleNode(const FontHolder &fonts, const ColorHolder &colors)
        : mValue(0),
          mText(std::to_string(mValue), fonts.get(Fonts::Main), 20u),
          mCircle(30.f) {
    mText.setFillColor(colors.get(Colors::Text));
    Utility::centerOrigin(mText);

    mCircle.setFillColor(colors.get(Colors::UIPrimary));
    mCircle.setOutlineColor(colors.get(Colors::UIBorder));
    mCircle.setOutlineThickness(1.f);
    Utility::centerOrigin(mCircle);
}

void CircleNode::updateCurrent(sf::Time dt) {}

void CircleNode::drawCurrent(sf::RenderTarget &target,
                             sf::RenderStates states) const {
    target.draw(mCircle, states);
    target.draw(mText, states);
}

int CircleNode::getValue() const {
    return mValue;
}

void CircleNode::setValue(const int &value) {
    setScale(0.f, 0.f);
    mValue = value;
    mText.setString(std::to_string(mValue));
    Utility::centerOrigin(mText);
}

void CircleNode::setCircle(const sf::CircleShape &circle) {
    mCircle = circle;
}
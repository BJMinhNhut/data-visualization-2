//
// Created by MINH NHUT on 7/31/2023.
//

#include "Edge.hpp"
#include "Template/Constants.hpp"
#include "PolyNode.hpp"

#include <SFML/Graphics/RenderStates.hpp>
#include <SFML/Graphics/RenderTarget.hpp>

#include <iostream>
#include <cmath>

const float Edge::THICKNESS = 2.f;

Edge::Edge(PolyNode *from, PolyNode *to, EdgeType type, const sf::Color &color) :
        mFrom(from), mTo(to), mType(type), mUpdate(true) {
    mLine.setFillColor(color);
}

void Edge::updateCurrent(sf::Time dt) {
    if (mUpdate) {
        mLine = getLineShape(mTo->getWorldPosition() - mFrom->getWorldPosition());
        mUpdate = false;
    }
}

void Edge::drawCurrent(sf::RenderTarget &target, sf::RenderStates states) const {
    if (mType == EdgeType::Undirected) {
        target.draw(mLine, states);
    }
}

sf::RectangleShape Edge::getLineShape(sf::Vector2f line) {
    float lineLength = sqrt(line.x * line.x + line.y * line.y);
    sf::RectangleShape rect(sf::Vector2f(lineLength, THICKNESS));
    sf::FloatRect bounds = rect.getLocalBounds();
    rect.setOrigin(0, std::floor(bounds.top + bounds.height / 2.f));

    float angle = atan2(line.y, line.x) / Constants::PI * 180.f;
    rect.rotate(angle);
    return rect;
}

void Edge::callUpdate() {
    mUpdate = true;
}

PolyNode *Edge::getTo() const {
    return mTo;
}

PolyNode *Edge::getFrom() const {
    return mFrom;
}





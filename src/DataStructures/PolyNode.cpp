//
// Created by MINH NHUT on 7/27/2023.
//

#include "PolyNode.hpp"
#include "Template/Utility.hpp"
#include "Template/ResourceHolder.hpp"

#include <SFML/Graphics/RenderStates.hpp>
#include <SFML/Graphics/RenderTarget.hpp>

PolyNode::PolyNode(const FontHolder &fonts, const ColorHolder &colors)
        : mText("", fonts.get(Fonts::Mono), 18u),
          mPolygon(22.f) {
    mText.setFillColor(colors.get(Colors::Text));
    Utility::centerOrigin(mText);

    mPolygon.setFillColor(colors.get(Colors::UIPrimary));
    mPolygon.setOutlineColor(colors.get(Colors::UIBorder));
    mPolygon.setOutlineThickness(2.f);
    Utility::centerOrigin(mPolygon);
}

void PolyNode::updateCurrent(sf::Time dt) {}

void PolyNode::drawCurrent(sf::RenderTarget &target,
                           sf::RenderStates states) const {
    target.draw(mPolygon, states);
    target.draw(mText, states);
}

std::string PolyNode::getData() const {
    return mText.getString();
}

int PolyNode::getIntData() const {
    std::string data(mText.getString());
    assert(std::all_of(data.begin(), data.end(), ::isdigit) && data.length() < 32);
    return stoi(data);
}

void PolyNode::setData(const std::string &data) {
    mText.setString(data);
    Utility::centerOrigin(mText);
}

void PolyNode::setPoint(const int &points) {
    mPolygon.setPointCount(points);
}
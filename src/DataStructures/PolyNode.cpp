//
// Created by MINH NHUT on 7/27/2023.
//

#include "PolyNode.hpp"
#include "Template/Utility.hpp"
#include "Template/ResourceHolder.hpp"

#include <SFML/Graphics/RenderStates.hpp>
#include <SFML/Graphics/RenderTarget.hpp>

#include <iostream>

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
    return stoi(data);
}

void PolyNode::setData(const std::string &data) {
    mText.setString(data);
    Utility::centerOrigin(mText);
}

void PolyNode::setData(const int &data) {
    mText.setString(std::to_string(data));
    Utility::centerOrigin(mText);
}

void PolyNode::setPoint(const int &points) {
    mPolygon.setPointCount(points);
}

void PolyNode::addEdgeOut(PolyNode *to, const sf::Color &color) {
    Edge *edge = new Edge(this, to, Edge::EdgeType::Undirected, color);
    attachChild(Edge::Ptr(edge));
    outEdges.push_back(edge);
    to->addEdgeIn(edge);
}

void PolyNode::addEdgeIn(Edge *edge) {
    inEdges.push_back(edge);
}

void PolyNode::removeEdgeOut(PolyNode *to) {
    for (auto itr = outEdges.begin(); itr != outEdges.end(); ++itr) {
        if ((*itr)->getTo() == to) {
            to->removeEdgeIn(*itr);
            detachChild(*(*itr));
            outEdges.erase(itr);
            return;
        }
    }
}

void PolyNode::removeEdgeIn(Edge *edge) {
    for (auto itr = inEdges.begin(); itr != inEdges.end(); ++itr) {
        if (*itr == edge) {
            inEdges.erase(itr);
            return;
        }
    }
}

void PolyNode::setPosition(float x, float y) {
    SceneNode::setPosition(x, y);
    for (auto edge: inEdges) edge->callUpdate();
    for (auto edge: outEdges) edge->callUpdate();
}
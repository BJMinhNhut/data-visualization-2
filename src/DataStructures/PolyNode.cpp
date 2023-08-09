//
// Created by MINH NHUT on 7/27/2023.
//

#include "PolyNode.hpp"
#include "Template/ResourceHolder.hpp"
#include "Template/Utility.hpp"

#include <SFML/Graphics/RenderStates.hpp>
#include <SFML/Graphics/RenderTarget.hpp>

#include <iostream>

PolyNode::PolyNode(const FontHolder& fonts, const ColorHolder& colors)
    : mText("", fonts.get(Fonts::Mono), 18u), mPolygon(22.f), mColors(colors) {
	mText.setFillColor(colors.get(Colors::Text));
	Utility::centerOrigin(mText);

	mPolygon.setFillColor(colors.get(Colors::UIPrimary));
	mPolygon.setOutlineColor(colors.get(Colors::UIBorder));
	mPolygon.setOutlineThickness(2.f);
	Utility::centerOrigin(mPolygon);
}

void PolyNode::updateCurrent(sf::Time dt) {
	for (auto& edge : outEdges)
		edge->update(dt);
	for (auto& edge : inEdges)
		edge->update(dt);
}

void PolyNode::drawCurrent(sf::RenderTarget& target, sf::RenderStates states) const {
	for (auto& edge : outEdges)
		target.draw(*edge, states);
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

void PolyNode::setData(const std::string& data) {
	mText.setString(data);
	Utility::centerOrigin(mText);
}

void PolyNode::setData(const int& data) {
	mText.setString(std::to_string(data));
	Utility::centerOrigin(mText);
}

void PolyNode::swapData(PolyNode* node) {
	std::string temp = this->getData();
	this->setData(node->getData());
	node->setData(temp);
}

void PolyNode::setPoint(const int& points) {
	mPolygon.setPointCount(points);
}

void PolyNode::addEdgeOut(PolyNode* to) {
	auto edge = std::make_shared<Edge>(this, to, Edge::EdgeType::Undirected, mColors);
	outEdges.push_back(edge);
	to->addEdgeIn(edge);
}

void PolyNode::addEdgeIn(const Edge::Ptr& edge) {
	inEdges.push_back(edge);
}

void PolyNode::removeEdgeOut(PolyNode* to) {
	for (auto itr = outEdges.begin(); itr != outEdges.end(); ++itr) {
		if ((*itr)->getTo() == to) {
			to->removeEdgeIn(*itr);
			outEdges.erase(itr);
			return;
		}
	}
}

void PolyNode::removeEdgeIn(const Edge::Ptr& edge) {
	for (auto itr = inEdges.begin(); itr != inEdges.end(); ++itr) {
		if (*itr == edge) {
			inEdges.erase(itr);
			return;
		}
	}
}

void PolyNode::removeAllEdges() {
	for (auto& edge : inEdges)
		edge->getFrom()->removeEdgeOut(this);
	for (auto& edge : outEdges)
		edge->getTo()->removeEdgeIn(edge);
	std::vector<Edge::Ptr>().swap(inEdges);
	std::vector<Edge::Ptr>().swap(outEdges);
}

void PolyNode::setPosition(float pX, float pY) {
	SceneNode::setPosition(pX, pY);
	for (auto& edge : inEdges)
		edge->callUpdate();
	for (auto& edge : outEdges)
		edge->callUpdate();
}

void PolyNode::setPosition(sf::Vector2f position) {
	SceneNode::setPosition(position);
	for (auto& edge : inEdges)
		edge->callUpdate();
	for (auto& edge : outEdges)
		edge->callUpdate();
}
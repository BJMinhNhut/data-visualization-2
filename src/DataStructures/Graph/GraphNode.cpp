//
// Created by MINH NHUT on 8/20/2023.
//

#include "GraphNode.hpp"
#include "Template/Utility.hpp"

#include <cmath>
#include <iostream>

const float GraphNode::REPULSE = 5000000.f;
const float GraphNode::ATTRACT = 2000.f;
const float GraphNode::LENGTH_LIMIT = 175.f;
const float GraphNode::LEFT(-520.f), GraphNode::RIGHT(520.f);
const float GraphNode::TOP(0.f), GraphNode::BOTTOM(600.f);

GraphNode::GraphNode(const FontHolder& fonts, const ColorHolder& colors)
    : PolyNode(fonts, colors), mVelocity(0.f, 0.f), mAdj() {
	setRadius(18.f);
}

void GraphNode::setVelocity(sf::Vector2f velocity) {
	mVelocity = velocity;
}

void GraphNode::makeAdjacent(GraphNode* node) {
	mAdj.push_back(node);
}

sf::Vector2f GraphNode::getRepulsion(const GraphNode& node) const {
	sf::Vector2f delta = getPosition() - node.getPosition();
	float norm = Utility::getNorm(delta);
	return (delta / norm) / (float)pow(norm, 2) * REPULSE;
}

bool GraphNode::isAdjacent(const GraphNode& node) const {
	for (auto& cur : mAdj)
		if (cur == &node)
			return true;
	return false;
}

sf::Vector2f GraphNode::getTotalAttraction() const {
	sf::Vector2f mAttract(0.f, 0.f);
	for (auto& node : mAdj) {
		mAttract += getAttraction(*node);
	}
	return mAttract;
}

sf::Vector2f GraphNode::getAttraction(const GraphNode& node) const {
	sf::Vector2f delta = node.getPosition() - getPosition();
	float norm = Utility::getNorm(delta);
	return (delta / norm) * std::log(norm / LENGTH_LIMIT) * ATTRACT - getRepulsion(node);
}

const std::vector<GraphNode*>& GraphNode::getAdj() const {
	return mAdj;
}

void GraphNode::updateCurrent(sf::Time dt) {
	PolyNode::updateCurrent(dt);
	sf::Vector2f newPosition = getPosition() + mVelocity * dt.asSeconds();

	newPosition.x = std::min(newPosition.x, RIGHT);
	newPosition.x = std::max(newPosition.x, LEFT);
	newPosition.y = std::min(newPosition.y, BOTTOM);
	newPosition.y = std::max(newPosition.y, TOP);

	newPosition.y = std::round(newPosition.y);
	newPosition.x = std::round(newPosition.x);

	setTargetPosition(newPosition, Transition::None);
}

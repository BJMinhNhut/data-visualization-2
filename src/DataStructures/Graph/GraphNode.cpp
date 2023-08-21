//
// Created by MINH NHUT on 8/20/2023.
//

#include "GraphNode.hpp"
#include "Template/Utility.hpp"

#include <cmath>
#include <iostream>

const float GraphNode::REPULSE = 4000000.f;
const float GraphNode::ATTRACT = 2000.f;
const float GraphNode::LENGTH_LIMIT = 90.f;

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
	if (norm > 2.f * LENGTH_LIMIT)
		return {0.f, 0.f};
	return (delta / norm) / (float)pow(norm, 2.4) * REPULSE;
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

void GraphNode::updateCurrent(sf::Time dt) {
	PolyNode::updateCurrent(dt);
	setPosition(getPosition() + mVelocity * dt.asSeconds());
	setTargetPosition(getPosition(), Transition::None);
}

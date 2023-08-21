//
// Created by MINH NHUT on 8/21/2023.
//

#include "Graph.hpp"
#include "Template/Random.hpp"
#include "Template/Utility.hpp"

#include <cmath>
#include <iostream>

const int Graph::MAX_SIZE = 24;
const int Graph::MAX_EDGES = 100;
const int Graph::UPDATE_LOOPS = 10000;
const float Graph::FORCE_EPSILON = 1e-3;
const float Graph::COOL_DOWN = 0.999f;

Graph::Edge::Edge(int from, int to, int weight) : from(from), to(to), weight(weight) {}

Graph::Graph(const FontHolder& fonts, const ColorHolder& colors)
    : mNodes(),
      mFonts(fonts),
      mColors(colors),
      mTime(UPDATE_LOOPS + 1),
      mCoolDown(1.f),
      mMaxForce(100.f) {
	randomize(24, 30);
}

void Graph::clear() {
	for (auto& node : mNodes) {
		detachChild(*node);
	}
	std::vector<GraphNode*>().swap(mNodes);
}

void Graph::randomize(int nodes, int edges) {
	build(nodes);
	std::vector<Edge>().swap(mEdges);
	std::vector<std::pair<int, int>> candidates;
	for (int i = 0; i < mNodes.size(); ++i)
		for (int j = i + 1; j < mNodes.size(); ++j)
			if (j != i) {
				candidates.emplace_back(i, j);
			}
	Random::shuffle(candidates);
	for (int i = 0; i < edges; ++i) {
		if (i >= candidates.size())
			break;
		auto& [u, v] = candidates[i];
		addEdge(u, v);
	}
}

void Graph::build(int nodes) {
	assert(nodes > 0 && nodes < MAX_SIZE);
	clear();
	mNodes.resize(nodes);
	int mSqrt = std::max(1, (int)sqrt(nodes));
	for (int i = 0; i < nodes; ++i) {
		mNodes[i] = new GraphNode(mFonts, mColors);
		mNodes[i]->setData(i);
		int row = i / mSqrt, col = i % mSqrt;
		mNodes[i]->setTargetPosition(-300.f + 120.f * (float)col + (float)Random::getInt(-10, 10),
		                             50.f + 120.f * (float)row + (float)Random::getInt(-10, 10),
		                             Transition::None);
		attachChild(GraphNode::Ptr(mNodes[i]));
	}
	rearrange();
}

void Graph::addEdge(int from, int to) {
	assert(from >= 0 && from < mNodes.size());
	assert(to >= 0 && to < mNodes.size());
	assert(from != to);
	assert(mEdges.size() < MAX_EDGES);
	mNodes[from]->addEdgeOut(mNodes[to]);
	mNodes[from]->makeAdjacent(mNodes[to]);
	mNodes[to]->makeAdjacent(mNodes[from]);
	mEdges.emplace_back(from, to, 0);
}

void Graph::rearrange() {
	mTime = 0;
	mCoolDown = 1.f;
	mMaxForce = 100.f;
}

int Graph::getNumNodes() const {
	return (int)mNodes.size();
}

int Graph::getNumEdges() const {
	return (int)mEdges.size();
}

void Graph::updateCurrent(sf::Time dt) {
	if (mTime > UPDATE_LOOPS || mMaxForce < FORCE_EPSILON)
		return;
	mMaxForce = 0.f;
	for (auto& u : mNodes) {
		sf::Vector2f mForce(0.f, 0.f);
		for (auto& v : mNodes)
			if (u != v)
				mForce += u->getRepulsion(*v);
		mForce += u->getTotalAttraction();
		mForce *= mCoolDown;
		mMaxForce = std::max(std::fabs(Utility::getNorm(mForce)), mMaxForce);
		u->setVelocity(mForce);
		mCoolDown *= COOL_DOWN;
	}
	mTime += dt.asMilliseconds();
}
//
// Created by MINH NHUT on 8/21/2023.
//

#include "Graph.hpp"
#include "Template/Random.hpp"
#include "Template/Utility.hpp"

#include <cmath>
#include <fstream>
#include <iostream>
#include <sstream>

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
	randomize(15, 20);
}

void Graph::clear() {
	for (auto& node : mNodes) {
		detachChild(*node);
	}
	std::vector<GraphNode*>().swap(mNodes);
	std::vector<Edge>().swap(mEdges);
}

void Graph::clearHighlight() {
	for (auto& node : mNodes) {
		node->highlight(PolyNode::None);
		node->setLabel("");
	}
}

void Graph::randomize(int nodes, int edges) {
	build(nodes);
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

void Graph::loadFromFile(const std::string& fileDir) {
	std::ifstream fileStream(fileDir);
	std::vector<int> elements;
	std::string token;
	int nodes;
	std::vector<Edge> edgeList;
	try {
		if (!(fileStream >> nodes))
			throw 1;
		std::cout << "nodes : " << nodes << '\n';
		for (int i = 0; i < nodes; ++i) {
			for (int j = 0; j < nodes; ++j) {
				int weight;
				if (!(fileStream >> weight))
					throw 1;
				if (weight != 0) {
					edgeList.emplace_back(i, j, weight);
				}
			}
		}
	} catch (...) {
		throw std::logic_error("File format is invalid");
	}
	if (nodes <= 0 || nodes > MAX_SIZE)
		throw std::logic_error("Number of nodes must be in range [2, " + std::to_string(MAX_SIZE) +
		                       "]");
	else if (mEdges.size() > MAX_EDGES) {
		throw std::logic_error("Number of edges must be in range [0, " + std::to_string(MAX_EDGES) +
		                       "]");
	} else {
		for (auto& [from, to, weight] : edgeList) {
			if (from < 0 || from >= nodes || to < 0 || to >= nodes)
				throw std::logic_error("Nodes index must be in range [0, " +
				                       std::to_string(nodes - 1) + "]");
		}
		build(nodes);
		for (auto& [from, to, weight] : edgeList) {
			addEdge(from, to);
		}
	}
	fileStream.close();
}

void Graph::build(int nodes) {
	assert(nodes > 0 && nodes <= MAX_SIZE);
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
	assert(mEdges.size() < MAX_EDGES);

	if (from != to) {
		mNodes[from]->addEdgeOut(mNodes[to]);
		mNodes[from]->makeAdjacent(mNodes[to]);
		mNodes[to]->makeAdjacent(mNodes[from]);
	}

	mEdges.emplace_back(from, to, 0);
}

void Graph::rearrange() {
	mTime = 0;
	mCoolDown = 1.f;
	mMaxForce = 100.f;
}

std::pair<std::vector<Animation>, std::string> Graph::CCAnimation() {
	std::vector<Animation> list;
	std::vector<int> components(mNodes.size(), -1);
	int numCC = 0;
	for (int i = 0; i < mNodes.size(); ++i) {
		if (components[i] == -1) {
			components[i] = numCC++;
			DFS(*mNodes[i], components);
		}
	}
	list.push_back(Animation(
	    {}, "Graph contains " + std::to_string(numCC) + " connected components. Complexity O(V+E).",
	    [&, components]() {
		    for (auto& node : mNodes) {
			    int id = node->getIntData();
			    node->setLabel(components[id]);
			    if (components[id] % 2)
				    node->highlight(PolyNode::Secondary);
		    }
	    },
	    [&]() { clearHighlight(); }));

	return std::make_pair(list, "");
}

void Graph::DFS(const GraphNode& node, std::vector<int>& components) {
	int curID = node.getIntData();
	for (auto& next : node.getAdj()) {
		int id = next->getIntData();
		if (components[id] == -1) {
			components[id] = components[curID];
			DFS(*next, components);
		}
	}
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
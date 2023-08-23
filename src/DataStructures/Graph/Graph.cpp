//
// Created by MINH NHUT on 8/21/2023.
//

#include "Graph.hpp"
#include "DisjointSet.hpp"
#include "Template/Random.hpp"
#include "Template/Utility.hpp"

#include <cmath>
#include <fstream>
#include <iostream>
#include <sstream>

const int Graph::MAX_SIZE = 24;
const int Graph::MAX_EDGES = 100;
const int Graph::MAX_WEIGHT = 50;
const int Graph::UPDATE_LOOPS = 8000;
const float Graph::FORCE_EPSILON = 1e-3;
const float Graph::COOL_DOWN = 0.9995f;

Graph::EdgeTuple::EdgeTuple(int from, int to, int weight) : from(from), to(to), weight(weight) {}

bool Graph::EdgeTuple::operator<(const Graph::EdgeTuple& edge) const {
	return this->weight < edge.weight;
}

Graph::Graph(const FontHolder& fonts, const ColorHolder& colors)
    : mNodes(),
      mFonts(fonts),
      mColors(colors),
      mTime(UPDATE_LOOPS + 1),
      mCoolDown(1.f),
      mMaxForce(100.f),
      mCurrentOptions(0) {
	randomize(15, 20);
}

void Graph::clear() {
	for (auto& node : mNodes) {
		detachChild(*node);
	}
	std::vector<GraphNode*>().swap(mNodes);
	std::vector<EdgeTuple>().swap(mEdges);
}

void Graph::clearHighlight() {
	for (auto& node : mNodes) {
		node->highlight(PolyNode::None);
		node->clearEdgeHighlights();
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
		addEdge(u, v, Random::getInt(1, MAX_WEIGHT));
	}
}

void Graph::loadFromFile(const std::string& fileDir) {
	std::ifstream fileStream(fileDir);
	std::vector<int> elements;
	std::string token;
	int nodes;
	std::vector<EdgeTuple> edgeList;
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
			addEdge(from, to, weight);
		}
	}
	fileStream.close();
}

void Graph::build(int nodes) {
	assert(nodes > 0 && nodes <= MAX_SIZE);
	clear();
	mNodes.resize(nodes);
	int mSqrt = std::max(1, (int)sqrt(nodes));

	// randomize id
	std::vector<int> ids(nodes);
	std::iota(ids.begin(), ids.end(), 0);
	Random::shuffle(ids);

	for (int i = 0; i < nodes; ++i) {
		mNodes[ids[i]] = new GraphNode(mFonts, mColors);
		mNodes[ids[i]]->setData(ids[i]);
		int row = i / mSqrt, col = i % mSqrt;
		mNodes[ids[i]]->setTargetPosition(
		    -300.f + 120.f * (float)col + (float)Random::getInt(-10, 10),
		    50.f + 120.f * (float)row + (float)Random::getInt(-10, 10), Transition::None);
		attachChild(GraphNode::Ptr(mNodes[ids[i]]));
	}
	rearrange();
}

void Graph::addEdge(int from, int to, int weight) {
	assert(from >= 0 && from < mNodes.size());
	assert(to >= 0 && to < mNodes.size());
	assert(mEdges.size() < MAX_EDGES);
	assert(weight >= 0 && weight <= MAX_WEIGHT);

	if (from != to) {
		mNodes[from]->addEdgeOut(mNodes[to], mCurrentOptions);
		mNodes[from]->setEdgeWeight(mNodes[to], weight);
		mNodes[from]->makeAdjacent(mNodes[to]);
		mNodes[to]->makeAdjacent(mNodes[from]);
	}

	mEdges.emplace_back(from, to, weight);
}

void Graph::setDirected(bool isDirected) {
	if (mCurrentOptions & Edge::Directed)
		mCurrentOptions ^= Edge::Directed;
	if (isDirected)
		mCurrentOptions ^= Edge::Directed;

	for (auto& node : mNodes) {
		for (auto& next : node->getAdj()) {
			node->setEdgeType(next, mCurrentOptions);
		}
	}
	clearHighlight();
}

void Graph::setWeighted(bool isWeighted) {
	if (mCurrentOptions & Edge::Weighted)
		mCurrentOptions ^= Edge::Weighted;
	if (isWeighted) {
		mCurrentOptions ^= Edge::Weighted;
	}
	for (auto& node : mNodes) {
		for (auto& next : node->getAdj()) {
			node->setEdgeType(next, mCurrentOptions);
		}
	}
	clearHighlight();
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
			    node->setLabel("Comp. " + std::to_string(components[id]));
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

std::pair<std::vector<Animation>, std::string> Graph::MSTAnimation() {
	std::vector<Animation> list;

	std::vector<EdgeTuple> temp(mEdges);
	std::vector<EdgeTuple> usedEdges;
	std::sort(temp.begin(), temp.end());

	DisjointSet dsu(mNodes.size());
	int totalWeight = 0;
	for (auto& edge : temp) {
		if (dsu.unite(edge.from, edge.to)) {
			usedEdges.push_back(edge);
			totalWeight += edge.weight;
		}
	}

	if (!(mCurrentOptions & Edge::Weighted))
		totalWeight = (int)mNodes.size() - 1;

	list.push_back(Animation(
	    {},
	    "Minimum spanning tree/forest has total weight " + std::to_string(totalWeight) +
	        ". Complexity O(ElogV).",
	    [&, usedEdges]() {
		    for (auto& edge : mEdges) {
			    mNodes[edge.from]->highlightEdge(mNodes[edge.to], false);
		    }
		    for (auto& edge : usedEdges) {
			    mNodes[edge.from]->highlightEdge(mNodes[edge.to]);
		    }
	    },
	    [&]() { clearHighlight(); }));

	return std::make_pair(list, "");
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
//
// Created by MINH NHUT on 8/21/2023.
//

#ifndef DATAVISUALIZATION2_GRAPH_HPP
#define DATAVISUALIZATION2_GRAPH_HPP

#include "GraphNode.hpp"
#include "Template/ColorHolder.hpp"
#include "Template/ResourceIdentifiers.hpp"
#include "Template/SceneNode.hpp"
#include "Visualizer/Animation.hpp"

class Graph : public SceneNode {
   public:
	static const int MAX_SIZE;
	static const int MAX_EDGES;
	struct Edge {
		int from, to, weight;

		explicit Edge(int from = 0, int to = 0, int weight = 0);

		bool operator<(const Edge& edge) const;
	};

   public:
	Graph(const FontHolder& fonts, const ColorHolder& colors);

	void clear();
	void clearHighlight();
	void loadFromFile(const std::string& fileDir);
	void randomize(int nodes, int edges);
	void build(int nodes);
	void addEdge(int from, int to);

	std::pair<std::vector<Animation>, std::string> CCAnimation();
	std::pair<std::vector<Animation>, std::string> MSTAnimation();

	int getNumNodes() const;
	int getNumEdges() const;

   private:
	void rearrange();
	void DFS(const GraphNode& node, std::vector<int>& components);
	void updateCurrent(sf::Time dt) override;

   private:
	static const int UPDATE_LOOPS;
	static const float FORCE_EPSILON;
	static const float COOL_DOWN;

	float mMaxForce, mCoolDown;
	int mTime;
	const ColorHolder& mColors;
	const FontHolder& mFonts;
	std::vector<GraphNode*> mNodes;
	std::vector<Edge> mEdges;
};

#endif  //DATAVISUALIZATION2_GRAPH_HPP

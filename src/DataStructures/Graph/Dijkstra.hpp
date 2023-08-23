//
// Created by MINH NHUT on 8/23/2023.
//

#ifndef DATAVISUALIZATION2_DIJKSTRA_HPP
#define DATAVISUALIZATION2_DIJKSTRA_HPP

#include <tuple>
#include <vector>

/*
 * Algorithm is directed
 */
class Dijkstra {
   public:
	static const int INF;

   public:
	Dijkstra(int nodes, int start);

	void addEdge(int from, int to, int weight);
	void run();

	[[nodiscard]] int getDistance(int node) const;
	[[nodiscard]] int getTraverse(int node) const;

   private:
	bool mRun;
	int mNodes, mStart;
	std::vector<std::vector<std::pair<int, int>>> mAdj;
	std::vector<int> mDist, mTraverse;
};

#endif  //DATAVISUALIZATION2_DIJKSTRA_HPP

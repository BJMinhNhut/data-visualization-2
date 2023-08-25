//
// Created by MINH NHUT on 8/23/2023.
//

#include "Dijkstra.hpp"

#include <cassert>
#include <iostream>
#include <queue>

const int Dijkstra::INF = 1e5;

Dijkstra::Dijkstra(int nodes, int start) : mNodes(nodes), mStart(start), mRun(false) {
	mAdj.resize(nodes);
	mDist.assign(nodes, INF);
	mTraverse.assign(nodes, -1);
}

void Dijkstra::addEdge(int from, int to, int weight) {
	//	std::cout << "edge: " << from << ' ' << to << ' ' << weight << '\n';
	mAdj[from].emplace_back(to, weight);
}

void Dijkstra::run() {
	std::priority_queue<std::pair<int, int>, std::vector<std::pair<int, int>>, std::greater<>>
	    mQueue;
	mDist[mStart] = 0;
	mQueue.emplace(0, mStart);
	while (!mQueue.empty()) {
		auto [dist, node] = mQueue.top();
		mQueue.pop();
		if (dist != mDist[node])
			continue;
		//		std::cout << node << " deg: " << mAdj[node].size() << '\n';
		for (auto [next, weight] : mAdj[node]) {
			int newDist = mDist[node] + weight;
			//			std::cout << node << ' ' << dist << ' ' << next << ' ' << newDist << '\n';
			if (newDist < mDist[next]) {
				mDist[next] = newDist;
				mTraverse[next] = node;
				mQueue.emplace(newDist, next);
			}
		}
	}
	mRun = true;
}

int Dijkstra::getDistance(int node) const {
	assert(mRun == true);
	return mDist[node];
}

int Dijkstra::getTraverse(int node) const {
	assert(mRun == true);
	return mTraverse[node];
}

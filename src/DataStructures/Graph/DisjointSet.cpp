//
// Created by MINH NHUT on 8/22/2023.
//

#include "DisjointSet.hpp"
#include <algorithm>
#include <numeric>

DisjointSet::DisjointSet(unsigned int size) : mParent(size), mSize(size) {
	std::fill(mSize.begin(), mSize.end(), 1);
	std::iota(mParent.begin(), mParent.end(), 0);
}

int DisjointSet::getRoot(int u) {
	if (mParent[u] == u)
		return u;
	return mParent[u] = getRoot(mParent[u]);
}

bool DisjointSet::unite(int u, int v) {
	u = getRoot(u), v = getRoot(v);
	if (u == v)
		return false;
	if (mSize[u] < mSize[v])
		std::swap(u, v);
	mSize[u] += mSize[v];
	mParent[v] = u;
	return true;
}

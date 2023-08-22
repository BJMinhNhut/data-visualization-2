//
// Created by MINH NHUT on 8/22/2023.
//

#ifndef DATAVISUALIZATION2_DISJOINTSET_HPP
#define DATAVISUALIZATION2_DISJOINTSET_HPP

#include <vector>

class DisjointSet {
   public:
	DisjointSet(unsigned int size);

	int getRoot(int u);

	bool unite(int u, int v);

   private:
	std::vector<int> mParent, mSize;
};

#endif  //DATAVISUALIZATION2_DISJOINTSET_HPP

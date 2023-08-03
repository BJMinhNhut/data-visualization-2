//
// Created by MINH NHUT on 7/28/2023.
//

#ifndef DATAVISUALIZATION2_HEAP_HPP
#define DATAVISUALIZATION2_HEAP_HPP

#include "../PolyNode.hpp"
#include "Template/SceneNode.hpp"

#include <vector>

/*
 * TODO: Heap features
 *  - [x] Binary Tree style nodes alignment
 *  - [] Comparison definition
 *  - [x] Randomize data
 *  - [] AnimationList generation
 */

class Heap : public SceneNode {
   public:
	static const unsigned int MAX_SIZE;
	static const sf::Vector2f TREE_OFF_SET;
	static const int MIN_VALUE;
	static const int MAX_VALUE;
	enum NodeSide { Right, Left };

   public:
	Heap(const FontHolder&, const ColorHolder&);

	void randomize();

	void loadFromFile(const std::string& fileDir);

	void push(const int& value);

	[[nodiscard]] int top() const;

	void pop();

   private:
	void loadArray(const std::vector<int>& array);

	void clear(const int& root = 0);

	[[nodiscard]] static inline int parent(const int& index);

	void alignBinaryTree();

	void heapifyUp(int index);

	void heapifyDown();

   private:
	const ColorHolder& mColors;
	const FontHolder& mFonts;
	std::vector<PolyNode*> mNodes;

	struct Height {
		int left, right;

		Height(int left, int right);

		void updateLeft(const Height& child);
		void updateRight(const Height& child);
	};

	std::vector<Height> height;
};

#endif  //DATAVISUALIZATION2_HEAP_HPP

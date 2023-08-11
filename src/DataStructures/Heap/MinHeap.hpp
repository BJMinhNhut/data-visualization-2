//
// Created by MINH NHUT on 8/11/2023.
//

#ifndef DATAVISUALIZATION2_MINHEAP_HPP
#define DATAVISUALIZATION2_MINHEAP_HPP

#include "../PolyNode.hpp"
#include "Template/SceneNode.hpp"
#include "Visualizer/Animation.hpp"

#include <vector>

class MinHeap : public SceneNode {
   public:
	static const unsigned int MAX_SIZE;
	static const sf::Vector2f TREE_OFF_SET;
	static const int MIN_VALUE;
	static const int MAX_VALUE;
	enum NodeSide { Right, Left };

   public:
	MinHeap(const FontHolder&, const ColorHolder&);

	void randomize();

	void loadFromFile(const std::string& fileDir);

	std::pair<std::vector<Animation>, std::string> pushAnimation(const int& value);
	std::pair<std::vector<Animation>, std::string> deleteAnimation(const int& id);
	std::pair<std::vector<Animation>, std::string> getTopAnimation();
	std::pair<std::vector<Animation>, std::string> getSizeAnimation();

	[[nodiscard]] int top() const;

	void clearHighlight();

	int getSize() const;

   private:
	void alignBinaryTree();

	void push(const int& value);
	void remove(const int& index);
	void heapifyUp(int index);
	void heapifyDown();

	void loadArray(const std::vector<int>& array);
	void clear(const int& root = 0);

	void purePush(const int& value);
	void purePop();

	[[nodiscard]] static inline int parent(const int& index);

	void dump(PolyNode* node);

	void updateCurrent(sf::Time dt) override;

   private:
	const ColorHolder& mColors;
	const FontHolder& mFonts;
	std::vector<PolyNode*> mNodes;
	PolyNode* mBin;

	struct Height {
		int left, right;

		Height(int left, int right);

		void updateLeft(const Height& child);
		void updateRight(const Height& child);
	};

	std::vector<Height> height;
};

#endif  //DATAVISUALIZATION2_MINHEAP_HPP

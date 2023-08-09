//
// Created by MINH NHUT on 7/28/2023.
//

#include "Heap.hpp"
#include "HeapCode.hpp"
#include "Template/Random.hpp"
#include "Template/Utility.hpp"

#include <SFML/Graphics/RenderStates.hpp>
#include <SFML/Graphics/RenderTarget.hpp>

#include <fstream>
#include <iostream>
#include <queue>

const sf::Vector2f Heap::TREE_OFF_SET(35.f, 100.f);
const unsigned int Heap::MAX_SIZE(31);
const int Heap::MAX_VALUE(999);
const int Heap::MIN_VALUE(0);

Heap::Height::Height(int left, int right) : left(left), right(right) {}

void Heap::Height::updateLeft(const Heap::Height& child) {
	left = std::max(child.left, child.right) + 1;
}

void Heap::Height::updateRight(const Heap::Height& child) {
	right = std::max(child.left, child.right) + 1;
}

Heap::Heap(const FontHolder& fonts, const ColorHolder& colors)
    : mNodes(), mFonts(fonts), mColors(colors), height(), mBin(nullptr) {
	randomize();
}

void Heap::randomize() {
	std::vector<int> elements(Random::getArray(1, Heap::MAX_SIZE, MIN_VALUE, MAX_VALUE));
	loadArray(elements);
}

void Heap::loadFromFile(const std::string& fileDir) {
	std::ifstream fileStream(fileDir);
	std::vector<int> elements;
	std::string token;
	int value;
	while (fileStream >> token && elements.size() < MAX_SIZE) {
		try {
			value = std::stoi(token);
			if (value < MIN_VALUE || value > MAX_VALUE)
				throw std::exception();
			std::cout << "Token [" << token << "] read\n";
			elements.push_back(value);
		} catch (std::exception& e) {
			std::cerr << "Token [" << token << "] is not convertible\n";
		}
	}
	fileStream.close();
	loadArray(elements);
}

std::pair<std::vector<Animation>, std::string> Heap::pushAnimation(const int& value) {
	const std::string& code = HeapCode::Max::Push;
	std::vector<Animation> list;
	list.push_back(Animation({}, "Push " + std::to_string(value) + " to heap"));
	list.push_back(Animation(
	    {0, 1}, "Push " + std::to_string(value) + " to the back of heap",
	    [&, value]() {
		    purePush(value);
		    mNodes.back()->highlight(PolyNode::Primary);
	    },
	    [&]() { purePop(); }));

	int index = (int)mNodes.size();
	int last = -1;
	int curValue = value;
	while (true) {
		int parentID = parent(index);
		int parValue = mNodes[parentID]->getIntData();

		if (index > 0 && curValue > parValue) {
			list.push_back(Animation(
			    {2},
			    "Node is not root, " + std::to_string(parValue) + " < " + std::to_string(curValue),
			    [&, index, parentID, last]() {
				    if (last >= 0)
					    mNodes[last]->highlight(PolyNode::None);
				    mNodes[index]->highlight(PolyNode::Primary);
				    mNodes[parentID]->highlight(PolyNode::Secondary);
			    },
			    [&, index, parentID, last]() {
				    if (last >= 0)
					    mNodes[last]->highlight(PolyNode::Primary);
				    mNodes[index]->highlight(PolyNode::Secondary);
				    mNodes[parentID]->highlight(PolyNode::None);
			    }));
			list.push_back(Animation(
			    {3, 4}, "Swap two nodes and move to parent",
			    [&, index, parentID]() {
				    mNodes[index]->swapData(mNodes[parentID]);
				    mNodes[parentID]->highlight(PolyNode::Primary);
				    mNodes[index]->highlight(PolyNode::Secondary);
			    },
			    [&, index, parentID]() {
				    mNodes[index]->swapData(mNodes[parentID]);
				    mNodes[parentID]->highlight(PolyNode::Secondary);
				    mNodes[index]->highlight(PolyNode::Primary);
			    }));
			last = index;
			index = parentID;
		} else {
			if (index == 0)
				list.push_back(Animation(
				    {2}, "Node is root",
				    [&, index, last]() {
					    mNodes[index]->highlight(PolyNode::Primary);
					    mNodes[last]->highlight(PolyNode::None);
				    },
				    [&, index, last]() {
					    mNodes[index]->highlight(PolyNode::None);
					    mNodes[last]->highlight(PolyNode::Primary);
				    }));
			else
				list.push_back(Animation(
				    {2}, std::to_string(parValue) + " >= " + std::to_string(curValue),
				    [&, parentID, last]() {
					    if (last >= 0)
						    mNodes[last]->highlight(PolyNode::None);
					    mNodes[parentID]->highlight(PolyNode::Secondary);
				    },
				    [&, index, parentID, last]() {
					    if (last >= 0)
						    mNodes[last]->highlight(PolyNode::Secondary);
					    mNodes[index]->highlight(PolyNode::Primary);
					    mNodes[parentID]->highlight(PolyNode::None);
				    }));
			list.push_back(Animation(
			    {}, "Finish push, complexity is O(logN)",
			    [&, index, parentID]() {
				    mNodes[index]->highlight(PolyNode::None);
				    if (index > 0)
					    mNodes[parentID]->highlight(PolyNode::None);
			    },
			    [&, index, parentID]() {
				    mNodes[index]->highlight(PolyNode::Primary);
				    if (index > 0)
					    mNodes[parentID]->highlight(PolyNode::Secondary);
			    }));
			break;
		}
	}

	return make_pair(list, code);
}

std::pair<std::vector<Animation>, std::string> Heap::getTopAnimation() {
	const std::string& code = HeapCode::Top;
	std::vector<Animation> list;
	if (mNodes.empty())
		throw std::out_of_range("Heap is empty");
	list.push_back(Animation(
	    {0}, "Heap top: A[0] = " + mNodes[0]->getData(),
	    [&]() { mNodes[0]->highlight(PolyNode::Primary); },
	    [&]() { mNodes[0]->highlight(PolyNode::None); }));
	return std::make_pair(list, code);
}

std::pair<std::vector<Animation>, std::string> Heap::getSizeAnimation() {
	const std::string& code = HeapCode::Top;
	std::vector<Animation> list;
	list.push_back(Animation(
	    {0}, "Heap size = " + std::to_string(mNodes.size()),
	    [&]() {
		    for (auto& node : mNodes)
			    node->highlight(PolyNode::Primary);
	    },
	    [&]() {
		    for (auto& node : mNodes)
			    node->highlight(PolyNode::None);
	    }));
	return std::make_pair(list, code);
}

void Heap::loadArray(const std::vector<int>& array) {
	clear();
	for (int v : array)
		push(v);
}

void Heap::clear(const int& root) {
	if (mNodes.empty())
		return;
	int leftNode = root * 2 + 1, rightNode = root * 2 + 2;
	if (leftNode < mNodes.size()) {
		clear(leftNode);
		mNodes[root]->detachChild(*mNodes[leftNode]);
	}
	if (rightNode < mNodes.size()) {
		clear(rightNode);
		mNodes[root]->detachChild(*mNodes[rightNode]);
	}
	if (root == 0) {
		detachChild(*mNodes[0]);
		std::vector<PolyNode*>().swap(mNodes);
		std::vector<Height>().swap(height);
	}
}

void Heap::clearHighlight() {
	for (auto& node : mNodes)
		node->highlight(PolyNode::None);
}

void Heap::alignBinaryTree() {
	fill(height.begin(), height.end(), Height(0, 0));
	for (int id = (int)mNodes.size() - 1; id > 0; --id) {
		int parentID = parent(id);

		if (id % 2 == Right)
			height[parentID].updateRight(height[id]);
		else
			height[parentID].updateLeft(height[id]);

		float xOffset;
		if (id % 2 == Right)
			xOffset = float(1 << height[id].left) * TREE_OFF_SET.x;
		else
			xOffset = -float(1 << height[id].right) * TREE_OFF_SET.x;
		mNodes[id]->setTargetPosition(xOffset, TREE_OFF_SET.y, Transition::Smooth);
	}
}

void Heap::push(const int& value) {
	if (mNodes.size() == MAX_SIZE) {
		std::cerr << "Heap maximum size reached!\n";
		return;
	}

	purePush(value);
	heapifyUp((int)mNodes.size() - 1);
}

void Heap::purePush(const int& value) {
	std::cout << "Heap push: " << value << '\n';

	auto* newNode = new PolyNode(mFonts, mColors);
	newNode->setData(value);

	if (mNodes.empty())
		attachChild(PolyNode::Ptr(newNode));
	else {
		int nodeParent = parent((int)mNodes.size());
		mNodes[nodeParent]->addEdgeOut(newNode);
		mNodes[nodeParent]->attachChild(PolyNode::Ptr(newNode));
	}
	mNodes.push_back(newNode);
	height.emplace_back(0, 0);
	alignBinaryTree();
}

void Heap::purePop() {
	dump(mNodes.back());
	mNodes.pop_back();
	height.pop_back();
	alignBinaryTree();
}

int Heap::top() const {
	if (mNodes.empty()) {
		std::cerr << "Heap is empty!\n";
		return -1;
	}

	return mNodes[0]->getIntData();
}

void Heap::remove(const int& index) {
	assert(index >= 0 && index < mNodes.size());
	// up heap phase
	mNodes[index]->setData(mNodes[0]->getIntData() + 1);
	heapifyUp(index);

	// down heap phase
	mNodes[0]->setData(mNodes.back()->getData());

	if (mNodes.size() > 1) {
		int nodeParent = parent((int)mNodes.size() - 1);
		mNodes[nodeParent]->removeEdgeOut(mNodes[mNodes.size() - 1]);
		mNodes[nodeParent]->detachChild(*mNodes[mNodes.size() - 1]);
	} else
		detachChild(*mNodes[mNodes.size() - 1]);

	mNodes.pop_back();
	height.pop_back();
	heapifyDown();

	alignBinaryTree();
}

int Heap::getSize() const {
	return (int)mNodes.size();
}

void Heap::heapifyUp(int index) {
	assert(index < mNodes.size());
	while (index > 0) {
		int curValue = mNodes[index]->getIntData();
		int parValue = mNodes[parent(index)]->getIntData();
		if (curValue > parValue) {
			int temp = curValue;
			mNodes[index]->setData(parValue);
			mNodes[parent(index)]->setData(temp);
			index = parent(index);
		} else
			break;
	}
}

void Heap::heapifyDown() {
	int index = 0;
	while (index < mNodes.size()) {
		int leftChild = index * 2 + 1;
		int rightChild = index * 2 + 2;
		int largest = index;

		if (leftChild < mNodes.size() &&
		    mNodes[largest]->getIntData() < mNodes[leftChild]->getIntData())
			largest = leftChild;
		if (rightChild < mNodes.size() &&
		    mNodes[largest]->getIntData() < mNodes[rightChild]->getIntData())
			largest = rightChild;
		if (largest != index) {
			std::string temp = mNodes[index]->getData();
			mNodes[index]->setData(mNodes[largest]->getData());
			mNodes[largest]->setData(temp);
			index = largest;
		} else
			break;
	}
}

int Heap::parent(const int& index) {
	return (index - 1) / 2;
}

void Heap::dump(PolyNode* node) {
	node->removeAllEdges();
	node->setTargetScale(0.f, 0.f, Transition::Smooth);
	mBin = node;
}

void Heap::updateCurrent(sf::Time dt) {
	if (mBin != nullptr && mBin->getScale().x < SceneNode::EPS) {
		detachChild(*mBin);
		mBin = nullptr;
	}
}
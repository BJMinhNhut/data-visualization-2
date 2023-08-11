//
// Created by MINH NHUT on 7/28/2023.
//

#include "MaxHeap.hpp"
#include "HeapCode.hpp"
#include "Template/Random.hpp"
#include "Template/Utility.hpp"

#include <SFML/Graphics/RenderStates.hpp>
#include <SFML/Graphics/RenderTarget.hpp>

#include <fstream>
#include <iostream>
#include <queue>

const sf::Vector2f MaxHeap::TREE_OFF_SET(35.f, 100.f);
const unsigned int MaxHeap::MAX_SIZE(31);
const int MaxHeap::MAX_VALUE(999);
const int MaxHeap::MIN_VALUE(1);

MaxHeap::Height::Height(int left, int right) : left(left), right(right) {}

void MaxHeap::Height::updateLeft(const MaxHeap::Height& child) {
	left = std::max(child.left, child.right) + 1;
}

void MaxHeap::Height::updateRight(const MaxHeap::Height& child) {
	right = std::max(child.left, child.right) + 1;
}

MaxHeap::MaxHeap(const FontHolder& fonts, const ColorHolder& colors)
    : mNodes(), mFonts(fonts), mColors(colors), height(), mBin(nullptr) {
	randomize();
}

void MaxHeap::randomize() {
	std::vector<int> elements(Random::getArray(1, MaxHeap::MAX_SIZE, MIN_VALUE, MAX_VALUE));
	loadArray(elements);
}

void MaxHeap::loadFromFile(const std::string& fileDir) {
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

std::pair<std::vector<Animation>, std::string> MaxHeap::pushAnimation(const int& value) {
	const std::string& code = HeapCode::Max::Push;
	std::vector<Animation> list;
	if (mNodes.size() == MAX_SIZE)
		throw std::length_error("Heap maximum size reached");
	list.push_back(Animation({}, "Push " + std::to_string(value) + " to heap"));
	list.push_back(Animation(
	    {0, 1}, "Push " + std::to_string(value) + " to the back of heap",
	    [&, value]() {
		    purePush(value);
		    mNodes.back()->highlight(PolyNode::Primary);
	    },
	    [&]() { purePop(); }));

	/* up heap */
	{
		int index = (int)mNodes.size();
		int last = -1;
		int curValue = value;
		while (true) {
			int parentID = parent(index);
			int parValue = mNodes[parentID]->getIntData();

			if (index > 0 && parValue < curValue) {
				list.push_back(Animation(
				    {2},
				    "Node is not root, " + std::to_string(parValue) + " < " +
				        std::to_string(curValue),
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
				    {3}, "Swap two nodes and move to parent",
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
						    if (last >= 0)
							    mNodes[last]->highlight(PolyNode::None);
					    },
					    [&, index, last]() {
						    mNodes[index]->highlight(PolyNode::None);
						    if (last >= 0)
							    mNodes[last]->highlight(PolyNode::Primary);
					    }));
				else {
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
				}
				list.push_back(Animation(
				    {}, "Finish push, complexity is O(logN)",
				    [&, index, parentID]() {
					    mNodes[index]->highlight(PolyNode::Primary);
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
	}

	return make_pair(list, code);
}

std::pair<std::vector<Animation>, std::string> MaxHeap::deleteAnimation(const int& id) {
	if (id < 0 || id >= mNodes.size())
		throw std::out_of_range("Index must be in range [0, " + std::to_string(mNodes.size()) +
		                        "]");

	// Create a temporary heap
	std::vector<int> values(mNodes.size());
	for (int i = 0; i < mNodes.size(); ++i)
		values[i] = mNodes[i]->getIntData();

	const std::string& code = HeapCode::Max::Delete;
	std::vector<Animation> list;
	list.push_back(Animation(
	    {}, "Delete node at index " + std::to_string(id) + " from heap",
	    [&, id]() { mNodes[id]->highlight(PolyNode::Primary); },
	    [&, id]() { mNodes[id]->highlight(PolyNode::None); }));

	std::string backup = std::to_string(values[id]);
	list.push_back(Animation(
	    {0},
	    "Assign A[" + std::to_string(id) + "] with a value more prior than A[0], start heapify up",
	    [&, id]() {
		    mNodes[id]->setData(mNodes[0]->getIntData() + 1);
		    mNodes[0]->highlight(PolyNode::Secondary);
		    mNodes[id]->highlight(PolyNode::Primary);
	    },
	    [&, id, backup]() {
		    mNodes[id]->setData(backup);
		    mNodes[id]->highlight(PolyNode::Primary);
		    mNodes[0]->highlight(PolyNode::None);
	    }));
	values[id] = values[0] + 1;

	// up Heap
	{
		int index = id;
		int last = 0;
		int curValue = values[id];
		while (true) {
			int parentID = parent(index);
			int parValue = values[parentID];

			if (index > 0 && parValue < curValue) {
				list.push_back(Animation(
				    {1},
				    "Node is not root, " + std::to_string(parValue) + " < " +
				        std::to_string(curValue),
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
				    {2}, "Swap two nodes and move to parent",
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
				std::swap(values[index], values[parentID]);
				last = index;
				index = parentID;
			} else {
				if (index == 0)
					list.push_back(Animation(
					    {1}, "Node is root",
					    [&, index, last]() {
						    mNodes[index]->highlight(PolyNode::Primary);
						    if (last >= 0)
							    mNodes[last]->highlight(PolyNode::None);
					    },
					    [&, index, last]() {
						    mNodes[index]->highlight(PolyNode::None);
						    if (last >= 0)
							    mNodes[last]->highlight(PolyNode::Primary);
					    }));
				else
					list.push_back(Animation(
					    {1}, std::to_string(parValue) + " >= " + std::to_string(curValue),
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
				break;
			}
		}
	}

	backup = std::to_string(values[0]);
	std::cout << "backup " << backup << '\n';
	list.push_back(Animation(
	    {3}, "Assign A[0] with A[size-1]",
	    [&]() {
		    mNodes[0]->setData(mNodes.back()->getData());
		    mNodes[0]->highlight(PolyNode::Primary);
		    mNodes.back()->highlight(PolyNode::Secondary);
	    },
	    [&, backup]() {
		    mNodes[0]->setData(backup);
		    mNodes[0]->highlight(PolyNode::None);
		    mNodes.back()->highlight(PolyNode::None);
	    }));
	values[0] = values.back();

	backup = std::to_string(values.back());
	list.push_back(Animation(
	    {4}, "Remove A[size-1], decrease size", [&]() { purePop(); },
	    [&, backup] { purePush(stoi(backup)); }));
	values.pop_back();

	/* down heap */
	{
		int index = 0;
		int last = -1;
		while (index < values.size()) {
			int leftChild = index * 2 + 1;
			int rightChild = index * 2 + 2;
			int largest = index;

			if (leftChild < values.size() && values[largest] < values[leftChild])
				largest = leftChild;
			if (rightChild < values.size() && values[largest] < values[rightChild])
				largest = rightChild;
			if (largest != index) {
				list.push_back(Animation(
				    {5},
				    "Largest child of A[" + std::to_string(index) + "] is A[" +
				        std::to_string(largest) + "]",
				    [&, index, largest, last]() {
					    if (last != -1)
						    mNodes[last]->highlight(PolyNode::None);
					    mNodes[index]->highlight(PolyNode::Primary);
					    mNodes[largest]->highlight(PolyNode::Secondary);
				    },
				    [&, index, largest, last]() {
					    if (last != -1)
						    mNodes[last]->highlight(PolyNode::Secondary);
					    mNodes[index]->highlight(PolyNode::Primary);
					    mNodes[largest]->highlight(PolyNode::None);
				    }));
				list.push_back(Animation(
				    {6, 7},
				    "Swap A[" + std::to_string(index) + "] with A[" + std::to_string(largest) +
				        "], then move to A[" + std::to_string(largest) + "]",
				    [&, index, largest, last]() {
					    mNodes[index]->swapData(mNodes[largest]);
					    mNodes[index]->highlight(PolyNode::Secondary);
					    mNodes[largest]->highlight(PolyNode::Primary);
				    },
				    [&, index, largest]() {
					    mNodes[index]->swapData(mNodes[largest]);
					    mNodes[index]->highlight(PolyNode::Primary);
					    mNodes[largest]->highlight(PolyNode::Secondary);
				    }));
				std::swap(values[largest], values[index]);
				last = index;
				index = largest;
			} else {
				list.push_back(Animation(
				    {5}, "Node has no larger child",
				    [&, index, last]() {
					    mNodes[index]->highlight(PolyNode::Primary);
					    if (last >= 0)
						    mNodes[last]->highlight(PolyNode::None);
				    },
				    [&, index, last]() {
					    mNodes[index]->highlight(PolyNode::None);
					    if (last >= 0)
						    mNodes[last]->highlight(PolyNode::Primary);
				    }));
				break;
			}
		}
		list.push_back(
		    Animation({}, "Finish deletion, complexity is O(logN)", [&]() { clearHighlight(); }));
	}

	return std::make_pair(list, code);
}

std::pair<std::vector<Animation>, std::string> MaxHeap::getTopAnimation() {
	const std::string& code = HeapCode::Top;
	std::vector<Animation> list;
	if (mNodes.empty())
		throw std::out_of_range("Heap is empty");
	list.push_back(Animation(
	    {0}, "Heap top: A[0] = " + mNodes[0]->getData() + ", complexity is O(1)",
	    [&]() { mNodes[0]->highlight(PolyNode::Primary); },
	    [&]() { mNodes[0]->highlight(PolyNode::None); }));
	return std::make_pair(list, code);
}

std::pair<std::vector<Animation>, std::string> MaxHeap::getSizeAnimation() {
	const std::string& code = HeapCode::Size;
	std::vector<Animation> list;
	list.push_back(Animation(
	    {0}, "Heap size = " + std::to_string(mNodes.size()) + ", complexity is O(1)",
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

void MaxHeap::loadArray(const std::vector<int>& array) {
	clear();
	for (int v : array)
		push(v);
}

void MaxHeap::clear(const int& root) {
	if (mNodes.empty())
		return;
	int leftNode = root * 2 + 1, rightNode = root * 2 + 2;
	mNodes[root]->removeAllEdges();
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

void MaxHeap::clearHighlight() {
	for (auto& node : mNodes)
		node->highlight(PolyNode::None);
}

void MaxHeap::alignBinaryTree() {
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

void MaxHeap::push(const int& value) {
	if (mNodes.size() == MAX_SIZE) {
		std::cerr << "MaxHeap maximum size reached!\n";
		return;
	}

	purePush(value);
	heapifyUp((int)mNodes.size() - 1);
}

void MaxHeap::purePush(const int& value) {
	//	std::cout << "MaxHeap push: " << value << '\n';

	auto* newNode = new PolyNode(mFonts, mColors);
	newNode->setData(value);
	newNode->setLabel(mNodes.size());

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

void MaxHeap::purePop() {
	dump(mNodes.back());
	mNodes.pop_back();
	height.pop_back();
	alignBinaryTree();
}

int MaxHeap::top() const {
	if (mNodes.empty()) {
		std::cerr << "MaxHeap is empty!\n";
		return -1;
	}

	return mNodes[0]->getIntData();
}

void MaxHeap::remove(const int& index) {
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

int MaxHeap::getSize() const {
	return (int)mNodes.size();
}

void MaxHeap::heapifyUp(int index) {
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

void MaxHeap::heapifyDown() {
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

int MaxHeap::parent(const int& index) {
	return (index - 1) / 2;
}

void MaxHeap::dump(PolyNode* node) {
	node->removeAllEdges();
	node->setTargetScale(0.f, 0.f, Transition::Smooth);
	mBin = node;
}

void MaxHeap::updateCurrent(sf::Time dt) {
	if (mBin != nullptr && mBin->getScale().x < SceneNode::EPS) {
		detachChild(*mBin);
		mBin = nullptr;
	}
}
//
// Created by MINH NHUT on 8/23/2023.
//

#include "Tree234.hpp"
#include "Code234.hpp"
#include "Template/Random.hpp"

#include <fstream>
#include <iostream>
#include <queue>

const int Tree234::MAX_SIZE = 50;

Tree234::Tree234(const FontHolder& fonts, const ColorHolder& colors)
    : mFonts(fonts), mColors(colors), mRoot(nullptr) {
	randomize();
}

#ifdef SFML_DEBUG
void Tree234::testFeature() {
	mergeDown(mRoot, 0);
}
#endif

void Tree234::randomize() {
	loadArray(Random::getArray(1, MAX_SIZE, Node234::MIN_VALUE, Node234::MAX_VALUE));
}

void Tree234::loadFromFile(const std::string& fileDir) {
	std::ifstream fileStream(fileDir);
	std::vector<int> elements;
	std::string token;
	int value;
	while (fileStream >> token && elements.size() < MAX_SIZE) {
		try {
			value = std::stoi(token);
			if (value < Node234::MIN_VALUE || value > Node234::MAX_VALUE)
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

void Tree234::insert(const int& value) {
	if (mRoot == nullptr) {
		mRoot = new Node234(mFonts, mColors);
		mRoot->insert(value);
		attachChild(Ptr(mRoot));
		return;
	}
	assert(getSize() < MAX_SIZE);
	Node234* cur = mRoot;
	while (cur != nullptr) {
		if (cur->overflow()) {
			cur = split(cur);
			//			std::cout << "Split, new root; " << cur->get(0) << '\n';
		}

		if (cur->isLeaf())
			break;
		else {
			cur = cur->findChild(value);
		}
	}
	assert(cur != nullptr);
	cur->insert(value);
	align();
}

void Tree234::deleteCase1(Node234* node, int value) {
	assert(node->isLeaf());
	assert(node->numData() > 1);
	assert(node->findID(value) != -1);
	node->leafRemove(value);
}

Node234* Tree234::deleteCase2(Node234* node, int value) {
	const std::vector<Node234*>& mChildren = node->getChildList();
	int id = node->findID(value);
	assert(id != -1);
	Node234* mLeft = mChildren[id];
	Node234* mRight = mChildren[id + 1];

	assert(mLeft);
	assert(mRight);

	if (mLeft->numData() > 1) {
		// Case 2.1

	} else if (mRight->numData() > 1) {
		// Case 2.2
	} else {
		// Case 2.3
		return mergeDown(node, id);
	}
	return nullptr;
}

Node234* Tree234::deleteCase3(Node234* node, int value) {
	// Case 3
	Node234 *mChild, *mSibling;  // Get child (the one traverse to), and its sibling
	                             //	if (deleteNode->get(0) <= value) {
	                             //		mChild = deleteNode->getChildList()[1];
	                             //		mSibling = deleteNode->getChildList()[0];
	                             //	} else {
	                             //		mChild = deleteNode->getChildList()[0];
	                             //		mSibling = deleteNode->getChildList()[1];
	                             //	}
	                             //
	                             //	if (mChild->numData() == 1) {
	                             //		if (mSibling->numData() == 1) {
	                             //			// Case 3.1
	                             //			merge(deleteNode);
	                             //		} else {
	                             //			// Case 3.2
	                             //			rotate(deleteNode);
	                             //		}
	                             //	}
	return nullptr;
}

void Tree234::remove(const int& value) {
	Node234* cur = mRoot;
	while (cur != nullptr) {
		if (cur->findID(value) == -1) {
			cur = deleteCase3(cur, value);
		} else {
			if (cur->isLeaf()) {
				deleteCase1(cur, value);
				break;
			} else
				cur = deleteCase2(cur, value);
		}
	}
}

void Tree234::clear() {
	clear(mRoot);
	mRoot = nullptr;
}

void Tree234::clearHighlight() {
	clearHighlight(mRoot);
}

int Tree234::getSize() const {
	if (mRoot == nullptr)
		return 0;
	return mRoot->count();
}

int Tree234::getRandomElement() const {
	assert(mRoot != nullptr);
	std::vector<int> candidates;

	std::queue<Node234*> mQueue;
	mQueue.push(mRoot);
	while (!mQueue.empty()) {
		Node234* cur = mQueue.front();
		mQueue.pop();
		for (int i = 0; i < cur->numData(); ++i)
			candidates.push_back(cur->get(i));
		for (Node234* child : cur->getChildList()) {
			if (child != nullptr)
				mQueue.push(child);
		}
	}
	return candidates[Random::getInt(0, (int)candidates.size() - 1)];
}

std::pair<std::vector<Animation>, std::string> Tree234::insertAnimation(const int& value) {
	const std::string code = Code234::Insert;
	std::vector<Animation> list;

	if (getSize() == MAX_SIZE)
		throw std::logic_error("Tree size limit reached!");

	list.push_back(Animation({}, "Insert " + std::to_string(value) + " to 2-3-4 tree"));

	if (mRoot == nullptr) {
		const std::string altCode = "root = new Node(v)";
		list.push_back(Animation({0}, "Tree is empty, create new root", [&, value]() {
			mRoot = new Node234(mFonts, mColors);
			mRoot->insert(value);
			attachChild(Ptr(mRoot));
		}));
		return std::make_pair(list, altCode);
	}

	Node234* cur = mRoot;
	int depth = 0;
	while (cur != nullptr) {
		if (cur->overflow()) {
			list.push_back(
			    Animation({0}, "Node contains too much data, split it.", [&, value, depth]() {
				    clearHighlight();
				    Node234* node = searchNode(value, depth);
				    node->highlight(Node234::ALL_DATA);
			    }));
			list.push_back(
			    Animation({0}, "Node contains too much data, split it.", [&, value, depth]() {
				    clearHighlight();
				    Node234* node = split(searchNode(value, depth));
				    node->highlight(Node234::ALL_DATA);
				    align();
			    }));
			if (cur == mRoot)
				depth++;
			list.push_back(Animation({2, 3}, "Node is not leaf, go to child.", [&, value, depth]() {
				clearHighlight();
				Node234* node = searchNode(value, depth);
				node->highlight(Node234::ALL_DATA);
			}));
		}
		if (cur->isLeaf()) {
			list.push_back(Animation({1}, "Node is leaf, insert " + std::to_string(value),
			                         [&, value, depth]() {
				                         clearHighlight();
				                         Node234* node = searchNode(value, depth);
				                         node->insert(value);
				                         align();
				                         node->highlight(Node234::ALL_DATA);
			                         }));
			break;
		} else {
			list.push_back(Animation({2, 3}, "Node is not leaf, go to child.", [&, value, depth]() {
				clearHighlight();
				Node234* node = searchNode(value, depth);
				node->highlight(Node234::ALL_DATA);
			}));
			depth++;
			cur = cur->findChild(value);
		}
	}
	list.push_back(Animation({}, "Finish insertion. Complexity O(logn).", [&]() {}));

	return std::make_pair(list, code);
}

std::pair<std::vector<Animation>, std::string> Tree234::deleteAnimation(const int& value) {
	const std::string code = Code234::Delete;
	std::vector<Animation> list;
	list.push_back(Animation({}, "Delete " + std::to_string(value) + " in 2-3-4 tree"));

	Node234* cur = mRoot;
	Node234* last = nullptr;
	while (cur != nullptr) {
		int id = cur->findID(value);
		if (id != -1) {
			list.push_back(Animation(
			    {1, 2, 3},
			    "Current node contains " + std::to_string(value) +
			        ", stop searching. Complexity O(logn).",
			    [&, cur, last, id]() {
				    cur->highlight(1 << id);
				    if (last)
					    last->highlight(0);
			    },
			    [&, cur, last]() {
				    cur->highlight(0);
				    if (last)
					    last->highlight(Node234::ALL_DATA);
			    }));
			return std::make_pair(list, code);
		} else {
			list.push_back(Animation(
			    {1, 4},
			    "Current node doesn't contain " + std::to_string(value) +
			        ". Go to the suitable child.",
			    [&, cur, last]() {
				    cur->highlight(Node234::ALL_DATA);
				    if (last)
					    last->highlight(0);
			    },
			    [&, cur, last]() {
				    cur->highlight(0);
				    if (last)
					    last->highlight(Node234::ALL_DATA);
			    }));
			if (cur->isLeaf())
				break;
			last = cur;
			cur = cur->findChild(value);
		}
	}
	list.push_back(Animation(
	    {0}, "Null node reached, hence " + std::to_string(value) + " is NOT_FOUND\n",
	    [&]() { clearHighlight(); },
	    [&, cur]() {
		    if (cur)
			    cur->highlight(Node234::ALL_DATA);
	    }));

	return std::make_pair(list, code);
}

std::pair<std::vector<Animation>, std::string> Tree234::searchAnimation(const int& value) {
	const std::string code = Code234::Search;
	std::vector<Animation> list;
	list.push_back(Animation({}, "Search for " + std::to_string(value) + " in 2-3-4 tree"));

	Node234* cur = mRoot;
	Node234* last = nullptr;
	while (cur != nullptr) {
		int id = cur->findID(value);
		if (id != -1) {
			list.push_back(Animation(
			    {1, 2, 3},
			    "Current node contains " + std::to_string(value) +
			        ", stop searching. Complexity O(logn).",
			    [&, cur, last, id]() {
				    cur->highlight(1 << id);
				    if (last)
					    last->highlight(0);
			    },
			    [&, cur, last]() {
				    cur->highlight(0);
				    if (last)
					    last->highlight(Node234::ALL_DATA);
			    }));
			return std::make_pair(list, code);
		} else {
			list.push_back(Animation(
			    {1, 4},
			    "Current node doesn't contain " + std::to_string(value) +
			        ". Go to the suitable child.",
			    [&, cur, last]() {
				    cur->highlight(Node234::ALL_DATA);
				    if (last)
					    last->highlight(0);
			    },
			    [&, cur, last]() {
				    cur->highlight(0);
				    if (last)
					    last->highlight(Node234::ALL_DATA);
			    }));
			if (cur->isLeaf())
				break;
			last = cur;
			cur = cur->findChild(value);
		}
	}
	list.push_back(Animation(
	    {0}, "Null node reached, hence " + std::to_string(value) + " is NOT_FOUND\n",
	    [&]() { clearHighlight(); },
	    [&, cur]() {
		    if (cur)
			    cur->highlight(Node234::ALL_DATA);
	    }));

	return std::make_pair(list, code);
}

Node234* Tree234::split(Node234* node) {
	Node234* root = node->getParent();
	int id = root == nullptr ? 0 : root->getChildID(node);
	int pivot;
	Node234 *mLeft(nullptr), *mRight(nullptr);
	node->split(pivot, mLeft, mRight);

	assert(mLeft != nullptr);
	assert(mRight != nullptr);

	attachChild(Ptr(mLeft));
	attachChild(Ptr(mRight));

	if (root == nullptr) {
		root = new Node234(mFonts, mColors);
		attachChild(Ptr(root));
		mRoot = root;
	}

	root->insertSplit(id, pivot, mLeft, mRight);

	mLeft->setPosition(root->getPosition());
	mRight->setPosition(root->getPosition());
	if (root->numData() > 1) {
		mLeft->move(0.f, Node234::OFFSET.y);
		mRight->move(0.f, Node234::OFFSET.y);
	}

	detachChild(*node);
	return root;
}

void Tree234::align() {
	if (mRoot == nullptr)
		return;
	std::vector<std::vector<Node234*>> layers;

	// DFS
	std::queue<Node234*> mQueue;
	mQueue.push(mRoot);
	mRoot->setDepth(0);
	while (!mQueue.empty()) {
		Node234* cur = mQueue.front();
		mQueue.pop();
		if (layers.size() < cur->getDepth() + 1)
			layers.emplace_back();
		layers[cur->getDepth()].push_back(cur);
		//		std::cout << "*" << cur->get(0) << '\n';
		for (auto& node : cur->getChildList()) {
			if (node == nullptr)
				break;
			//			std::cout << node->get(0) << ' ';
			mQueue.push(node);
			node->setDepth(cur->getDepth() + 1);
		}
		//		std::cout << '\n';
	}

	// left-aligned layout
	int leaf = (int)layers.size() - 1;
	float leftBound = 0.f;
	for (int i = 0; i < layers[leaf].size(); ++i) {
		if (i > 0)
			leftBound += Node234::OFFSET.x;

		layers[leaf][i]->calcWidth();
		sf::Vector2f position;
		position = sf::Vector2f(leftBound + layers[leaf][i]->getWidth() / 2.f,
		                        Node234::OFFSET.y * (float)leaf);

		layers[leaf][i]->setTargetPosition(position, Smooth);
		leftBound += layers[leaf][i]->getWidth();
	}
	for (int depth = leaf - 1; depth >= 0; --depth) {
		for (Node234* node : layers[depth]) {

			sf::Vector2f position(0.f, Node234::OFFSET.y * (float)depth);

			const std::vector<Node234*>& children = node->getChildList();
			switch (node->numData()) {
				case 0:
				case 1:
					position.x =
					    (children[0]->getTargetPosition().x + children[1]->getTargetPosition().x) /
					    2.f;
					break;
				case 2:
					position.x = children[1]->getTargetPosition().x;
					break;
				case 3:
					position.x =
					    (children[1]->getTargetPosition().x + children[2]->getTargetPosition().x) /
					    2.f;
					break;
				default:
					assert(false);
			}

			node->setTargetPosition(position, Smooth);
		}
	}

	// centralize nodes
	sf::Vector2f delta(-leftBound / 2.f, 0.f);
	for (int depth = leaf; depth >= 0; --depth) {
		for (auto& node : layers[depth]) {
			node->setTargetPosition(node->getTargetPosition() + delta, Smooth);
		}
	}
}

void Tree234::clear(Node234* node) {
	if (node == nullptr)
		return;
	for (auto& child : node->getChildList()) {
		clear(child);
	}
	detachChild(*node);
}

void Tree234::clearHighlight(Node234* node) {
	if (node == nullptr)
		return;
	for (auto& child : node->getChildList()) {
		clearHighlight(child);
	}
	node->highlight(0);
}

void Tree234::loadArray(const std::vector<int>& array) {
	clear();
	for (int value : array)
		insert(value);
}

Node234* Tree234::searchNode(int value, int depth) {
	Node234* cur = mRoot;
	for (int i = 0; i < depth; ++i) {
		assert(cur != nullptr);
		cur = cur->findChild(value);
	}
	return cur;
}

Node234* Tree234::mergeDown(Node234* node, int id) {
	Node234* freedChild = node->mergeDown(id);
	detachChild(*freedChild);
	Node234* nextTraverse = nullptr;
	if (node->numData() == 0) {
		assert(node == mRoot);
		mRoot = mRoot->getChild(0);
		detachChild(*node);
		nextTraverse = mRoot;
	} else
		nextTraverse = node->getChild(0);
	align();
	return nextTraverse;
}
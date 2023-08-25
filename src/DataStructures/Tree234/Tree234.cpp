//
// Created by MINH NHUT on 8/23/2023.
//

#include "Tree234.hpp"
#include "Code234.hpp"
#include "Template/Random.hpp"

#include <fstream>
#include <iostream>
#include <queue>

const int Tree234::MAX_SIZE = 45;

Tree234::Tree234(const FontHolder& fonts, const ColorHolder& colors)
    : mFonts(fonts), mColors(colors), mRoot(nullptr) {
	randomize();
}

#ifdef SFML_DEBUG
void Tree234::testFeature() {
	mergeDown(mRoot, 1);
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
	std::cout << "case 1\n";
	node->leafRemove(value);
	align();
}

void Tree234::deleteCase1Animation(Node234* node, int value, std::vector<Animation>& list) {

	list.push_back(Animation(
	    {0, 1},
	    std::to_string(value) + " exist in current node, node is leaf, so just delete the value.",
	    [&, value, node]() {
		    std::cout << "case 1\n";
		    assert(node->isLeaf());
		    assert(node->numData() > 1);
		    assert(node->findID(value) != -1);
		    node->leafRemove(value);
		    align();
	    }));
}

Node234* Tree234::deleteCase2(Node234* node, int& value) {
	const std::vector<Node234*>& mChildren = node->getChildList();
	int id = node->findID(value);
	assert(id != -1);
	Node234* mLeft = mChildren[id];
	Node234* mRight = mChildren[id + 1];

	assert(mLeft);
	assert(mRight);
	std::cout << "Case 2 \n";

	if (mLeft->numData() > 1) {
		// Case 2.1
		std::cout << "  v2.1 - pred\n";
		Node234* pred = mLeft->findMax();
		value = pred->get(pred->numData() - 1);  // new value to search & delete recursively
		node->setData(id, value);
		return mLeft;
	} else if (mRight->numData() > 1) {
		// Case 2.2
		std::cout << "  2.2 - succ\n";
		Node234* succ = mRight->findMin();
		value = succ->get(0);
		node->setData(id, value);
		return mRight;
	} else {
		// Case 2.3
		std::cout << "  2.3 - merge\n";
		return mergeDown(node, id);
	}
}

void Tree234::deleteCase2Animation(Node234* node, int& value, std::vector<Animation>& list) {
	const std::vector<Node234*>& mChildren = node->getChildList();
	int id = node->findID(value);
	assert(id != -1);
	Node234* mLeft = mChildren[id];
	Node234* mRight = mChildren[id + 1];

	assert(mLeft);
	assert(mRight);
	std::cout << "Case 2 \n";

	if (mLeft->numData() > 1) {
		// Case 2.1

		list.push_back(Animation(
		    {0, 2, 3, 4},
		    "Left child has extra key, find predecessor from left child, and swap it with current "
		    "key.",
		    [&, value, node, mLeft]() {
			    std::cout << "  v2.1 - pred\n";
			    clearHighlight();
			    int id = node->findID(value);
			    Node234* pred = mLeft->findMax();
			    int newValue =
			        pred->get(pred->numData() - 1);  // new value to search & delete recursively
			    node->setData(id, newValue);
			    node->highlight(1 << id);
			    pred->highlight(1 << (pred->numData() - 1));
		    }));
		Node234* pred = mLeft->findMax();
		value = pred->get(pred->numData() - 1);

	} else if (mRight->numData() > 1) {
		// Case 2.2

		list.push_back(Animation(
		    {0, 2, 3, 4},
		    "Left child has extra key, find predecessor from left child, and swap it with current "
		    "key.",
		    [&, value, node, mRight]() {
			    std::cout << "  2.2 - succ\n";
			    clearHighlight();
			    int id = node->findID(value);
			    Node234* succ = mRight->findMin();
			    int newValue = succ->get(0);
			    node->setData(id, newValue);
			    node->highlight(1 << id);
			    succ->highlight(1 << 0);
		    }));

		Node234* succ = mRight->findMin();
		value = succ->get(0);
	} else {
		// Case 2.3

		list.push_back(Animation(
		    {0, 5}, "Both children have only 1 key each, so merge current key to two of them.",
		    [&, node, value]() {
			    std::cout << "  2.3 - merge\n";
			    clearHighlight();
			    int id = node->findID(value);
			    Node234* tempNode = mergeDown(node, id);
			    tempNode->highlight(Node234::ALL_DATA);
		    }));
	}
}

Node234* Tree234::deleteCase3(Node234* node, int value) {
	// Case 3
	std::cout << "Case 3 " << node->get(0) << ' ' << value << '\n';
	Node234* mChild = node->findChild(value);

	int id = node->getChildID(mChild);

	if (mChild->numData() == 1) {
		for (int sibID = id - 1; sibID <= id + 1; sibID += 2) {
			if (sibID < 0 || sibID > node->numData())
				continue;
			Node234* mSibling = node->getChild(sibID);

			if (mSibling->numData() == 1) {
				// Case 3.1
				std::cout << "  3.1 - merge\n";
				return mergeDown(node, (sibID == id - 1) ? id - 1 : id);
			} else {
				// Case 3.2
				std::cout << "  3.2 - rotate\n";
				if (sibID == id - 1)
					rotateRight(node, id - 1);
				else
					rotateLeft(node, id);
			}
			break;
		}
	}

	return node->findChild(value);
}
void Tree234::deleteCase3Animation(Node234*& node, int value, std::vector<Animation>& list) {
	// Case 3
	std::cout << "Case 3 " << node->get(0) << ' ' << value << '\n';
	Node234* mChild = node->findChild(value);

	int id = node->getChildID(mChild);

	if (mChild->numData() == 1) {
		for (int sibID = id - 1; sibID <= id + 1; sibID += 2) {
			if (sibID < 0 || sibID > node->numData())
				continue;
			Node234* mSibling = node->getChild(sibID);

			if (mSibling->numData() == 1) {
				// Case 3.1

				int mID = (sibID == id - 1) ? id - 1 : id;
				list.push_back(
				    Animation({8}, "Both sibling and child has 1 key, merge them with parent data.",
				              [&, mID, node]() {
					              std::cout << "  3.1 - merge\n";
					              clearHighlight();
					              Node234* temp = mergeDown(node, mID);
					              temp->highlight(Node234::ALL_DATA);
				              }));
				node = node->getChild(mID);
				return;
			} else {
				// Case 3.2

				if (sibID == id - 1) {
					list.push_back(Animation({6, 7}, "Left sibling has extra keys, rotate right.",
					                         [&, id, node]() {
						                         std::cout << "  3.2 - rotate\n";
						                         clearHighlight();
						                         rotateRight(node, id - 1);
						                         node->highlight(Node234::ALL_DATA);
					                         }));
				} else {
					list.push_back(Animation({6, 7}, "Right sibling has extra keys, rotate left.",
					                         [&, id, node]() {
						                         std::cout << "  3.2 - rotate\n";
						                         clearHighlight();
						                         rotateLeft(node, id);
						                         node->highlight(Node234::ALL_DATA);
					                         }));
				}
				node = node->findChild(value);
				return;
			}
		}
	}
	node = node->findChild(value);
}

void Tree234::remove(int value) {
	Node234* cur = mRoot;
	while (cur != nullptr) {
		std::cout << "cur " << cur->getString() << '\n';
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

	int tempValue = value;
	while (cur != nullptr) {
		list.push_back(Animation({0}, "Searching for " + std::to_string(tempValue), [&, cur]() {
			clearHighlight();
			cur->highlight(Node234::ALL_DATA);
		}));

		if (cur->findID(tempValue) == -1) {
			deleteCase3Animation(cur, tempValue, list);
		} else if (cur->isLeaf()) {
			deleteCase1Animation(cur, tempValue, list);
			break;
		} else {
			deleteCase2Animation(cur, tempValue, list);
			cur = cur->findChild(tempValue);
		}
	}

	list.push_back(Animation({},
	                         "Finished delete " + std::to_string(value) + ". Complexity O(logn).",
	                         [&]() { clearHighlight(); }));

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

void Tree234::rotateLeft(Node234* node, int id) {
	std::cout << "rotate left " << id << '\n';
	node->rotateLeft(id);
	align();
}

void Tree234::rotateRight(Node234* node, int id) {
	std::cout << "rotate right " << id << '\n';
	node->rotateRight(id);
	align();
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
	std::cout << "  merge " << node->getString() << ' ' << id << '\n';
	Node234* freedChild = node->mergeDown(id);
	detachChild(*freedChild);
	Node234* nextTraverse = nullptr;
	if (node->numData() == 0) {
		assert(node == mRoot);
		mRoot = mRoot->getChild(id);
		detachChild(*node);
		nextTraverse = mRoot;
	} else
		nextTraverse = node->getChild(id);
	align();
	return nextTraverse;
}

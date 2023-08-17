//
// Created by MINH NHUT on 8/15/2023.
//

#include "AVLTree.hpp"
#include "AVLCode.hpp"
#include "Template/Random.hpp"

#include <algorithm>
#include <fstream>
#include <iostream>

const int AVLTree::MAX_SIZE = 31;
const int AVLTree::MIN_VALUE = 0;
const int AVLTree::MAX_VALUE = 999;
const sf::Vector2f AVLTree::TREE_OFF_SET(35.f, 100.f);

AVLTree::AVLTree(const FontHolder& fonts, const ColorHolder& colors)
    : mFonts(fonts), mColors(colors), mRoot(nullptr), mSize(0), mBin(nullptr) {
	randomize();
}

unsigned int AVLTree::getSize() const {
	return mSize;
}

int AVLTree::getRandomElement() const {
	auto elements = getInOrder(mRoot);
	return elements[Random::getInt(0, (int)elements.size() - 1)]->getIntData();
}

std::pair<std::vector<Animation>, std::string> AVLTree::insertAnimation(const int& value) {
	const std::string& code = AVLCode::Insert;
	std::vector<Animation> list;
	list.push_back(Animation({}, "Insert " + std::to_string(value) + " to AVL tree."));

	if (mRoot == nullptr) {
		list.push_back(Animation(
		    {0},
		    "Tree is empty, insert " + std::to_string(value) +
		        ". Tree is balanced, complexity O(1).",
		    [&, value]() {
			    mRoot = new AVLNode(mFonts, mColors);
			    mRoot->setData(value);
			    mRoot->highlight(PolyNode::Primary);
			    attachChild(AVLNode::Ptr(mRoot));
			    alignAsTree();
		    },
		    [&]() {
			    dump(mRoot);
			    mRoot = nullptr;
			    alignAsTree();
		    }));
		return std::make_pair(list, code);
	}

	/* insert phase */
	AVLNode* last = traverseAnimation(value, list);
	bool goLeft = value < last->getIntData();

	auto* newNode = new AVLNode(mFonts, mColors);
	newNode->setData(value);
	newNode->setTargetScale(0.f, 0.f, None);
	attachChild(AVLNode::Ptr(newNode));

	list.push_back(Animation(
	    {0}, "Null node reached, insert " + std::to_string(value),
	    [&, newNode, last, goLeft]() {
		    newNode->highlight(PolyNode::Primary);

		    if (goLeft)
			    last->attachLeft(newNode);
		    else
			    last->attachRight(newNode);
		    last->highlight(PolyNode::None);

		    alignAsTree();
		    newNode->setPosition(last->getPosition());
		    newNode->setTargetScale(1.f, 1.f, None);
	    },
	    [&, newNode, last, goLeft]() {
		    newNode->setTargetScale(0.f, 0.f, None);
		    if (goLeft) {
			    last->detachLeft();
		    } else {
			    last->detachRight();
		    }
		    last->highlight(PolyNode::Primary);
		    alignAsTree();
	    }));
	list.back().play();

	//	balanceAnimation(newNode, list);

	for (auto itr = list.rbegin(); itr != list.rend(); itr++)
		itr->revert();

	return std::make_pair(list, code);
}

AVLNode* AVLTree::traverseAnimation(const int& value, std::vector<Animation>& list) {
	AVLNode* cur = mRoot;
	AVLNode* last = nullptr;
	while (cur != nullptr) {
		std::string log =
		    std::to_string(value) + ((value < cur->getIntData())
		                                 ? " < current node data, go to left child"
		                                 : " >= current node data, go to right child");
		list.push_back(Animation(
		    {0}, log,
		    [&, cur, last]() {
			    if (last)
				    last->highlight(PolyNode::None);
			    cur->highlight(PolyNode::Primary);
		    },
		    [&, cur, last]() {
			    if (last)
				    last->highlight(PolyNode::Primary);
			    cur->highlight(PolyNode::None);
		    }));
		list.back().play();

		last = cur;
		if (value < cur->getIntData()) {
			cur = cur->getLeft();
		} else {
			cur = cur->getRight();
		}
	}
	return last;
}

void AVLTree::balanceAnimation(AVLNode* node, std::vector<Animation>& list) {
	while (node != nullptr) {
		AVLNode* parent = node->getParent();
		node = parent;
	}
}

std::pair<std::vector<Animation>, std::string> AVLTree::searchAnimation(const int& value) {
	const std::string& code = AVLCode::Search;
	std::vector<Animation> list;
	list.push_back(Animation({}, "Search for " + std::to_string(value) + " in AVL tree."));
	AVLNode* cur = mRoot;
	AVLNode* last = nullptr;
	while (true) {
		if (cur == nullptr) {
			list.push_back(Animation(
			    {0, 1}, "Current node is null, hence " + std::to_string(value) + " is NOT FOUND!",
			    [&, last]() {
				    if (last)
					    last->highlight(PolyNode::None);
			    },
			    [&, last]() {
				    if (last)
					    last->highlight(PolyNode::Primary);
			    }));
			break;
		} else {
			list.push_back(Animation(
			    {0}, "Current node is not null, continue searching",
			    [&, cur, last]() {
				    cur->highlight(PolyNode::Primary);
				    if (last)
					    last->highlight(PolyNode::None);
			    },
			    [&, cur, last]() {
				    cur->highlight(PolyNode::None);
				    if (last)
					    last->highlight(PolyNode::Primary);
			    }));
		}
		if (cur->getIntData() == value) {
			list.push_back(
			    Animation({2, 3}, std::to_string(value) + " is FOUND. Complexity is O(logn)."));
			break;
		} else if (value < cur->getIntData()) {
			list.push_back(Animation(
			    {4, 5}, std::to_string(value) +
			                " < current node data. Proceed to search on the left child."));
			last = cur;
			cur = cur->getLeft();
		} else {
			list.push_back(Animation(
			    {6, 7}, std::to_string(value) +
			                " > current node data. Proceed to search on the right child."));
			last = cur;
			cur = cur->getRight();
		}
	}
	return std::make_pair(list, code);
}

void AVLTree::randomize() {
	loadArray(Random::getArray(10, MAX_SIZE, MIN_VALUE, MAX_VALUE));
}

void AVLTree::loadFromFile(const std::string& fileDir) {
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

void AVLTree::clearHighlight() {
	clearHighlight(mRoot);
}

void AVLTree::insert(const int& value) {
	mRoot = pureInsert(mRoot, value);
	mSize++;
	alignAsTree();
}

void AVLTree::dump(AVLNode* node, Transition type) {
	// TODO: handle dumping new node when mBin is not null
	assert(node != nullptr);
	node->setTargetScale(0.f, 0.f, type);
	mBin = node;
}

void AVLTree::clear(AVLNode* root) {
	if (root == nullptr)
		return;
	clear(root->getLeft());
	clear(root->getRight());
	detachChild(*root);
}

void AVLTree::loadArray(std::vector<int> array) {
	clear(mRoot);
	std::sort(array.begin(), array.end());
	mSize = array.size();
	mRoot = create(array, 0, (int)array.size() - 1);
	alignAsTree();
}

AVLNode* AVLTree::create(const std::vector<int>& array, int left, int right) {
	if (left > right)
		return nullptr;
	auto* root = new AVLNode(mFonts, mColors);
	attachChild(AVLNode::Ptr(root));
	int mid = (left + right) >> 1;
	root->setData(array[mid]);
	root->attachLeft(create(array, left, mid - 1));
	root->attachRight(create(array, mid + 1, right));
	return root;
}

AVLNode* AVLTree::rotateLeft(AVLNode* root) {
	AVLNode* newRoot = root->getRight();
	root->attachRight(newRoot->getLeft());
	newRoot->attachLeft(root);
	return newRoot;
}

AVLNode* AVLTree::rotateRight(AVLNode* root) {
	AVLNode* newRoot = root->getLeft();
	root->attachLeft(newRoot->getRight());
	newRoot->attachRight(root);
	return newRoot;
}

void AVLTree::clearHighlight(AVLNode* root) {
	if (root == nullptr)
		return;
	root->highlight(PolyNode::None);
	clearHighlight(root->getLeft());
	clearHighlight(root->getRight());
}

AVLNode* AVLTree::pureInsert(AVLNode* root, const int& value) {
	if (root == nullptr) {
		auto* newNode = new AVLNode(mFonts, mColors);
		newNode->setData(value);
		attachChild(std::unique_ptr<AVLNode>(newNode));
		return newNode;
	} else if (value < root->getIntData()) {
		root->attachLeft(pureInsert(root->getLeft(), value));
	} else {
		root->attachRight(pureInsert(root->getRight(), value));
	}
	return root;
}

void AVLTree::calculateDepth() {
	mRoot->setDepth(0);
	calculateDepth(mRoot);
}

void AVLTree::alignAsTree() {
	if (mRoot == nullptr)
		return;

	calculateDepth();

	std::vector<AVLNode*> inOrder(getInOrder(mRoot));

	int rootID =
	    static_cast<int>(std::find(inOrder.begin(), inOrder.end(), mRoot) - inOrder.begin());
	for (int i = 0; i < inOrder.size(); ++i) {
		float x = float(i - rootID) * TREE_OFF_SET.x;
		float y = (float)inOrder[i]->getDepth() * TREE_OFF_SET.y;
		inOrder[i]->setTargetPosition(x, y, Smooth);
	}
}

std::vector<AVLNode*> AVLTree::getInOrder(AVLNode* root) const {
	std::vector<AVLNode*> inOrder;
	if (root) {
		if (root->getLeft()) {
			std::vector<AVLNode*> mLeft = getInOrder(root->getLeft());
			inOrder.insert(inOrder.end(), mLeft.begin(), mLeft.end());
		}

		inOrder.push_back(root);

		if (root->getRight()) {
			std::vector<AVLNode*> mRight = getInOrder(root->getRight());
			inOrder.insert(inOrder.end(), mRight.begin(), mRight.end());
		}
	}
	return inOrder;
}

void AVLTree::calculateDepth(AVLNode* root) {
	if (root == nullptr)
		return;

	if (AVLNode* mLeft = root->getLeft()) {
		mLeft->setDepth(root->getDepth() + 1);
		calculateDepth(mLeft);
	}

	if (AVLNode* mRight = root->getRight()) {
		mRight->setDepth(root->getDepth() + 1);
		calculateDepth(mRight);
	}
}

void AVLTree::updateCurrent(sf::Time dt) {
	if (mBin != nullptr && mBin->getScale().x < SceneNode::EPS) {
		detachChild(*mBin);
		mBin = nullptr;
	}
}

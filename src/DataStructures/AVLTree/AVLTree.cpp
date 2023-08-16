//
// Created by MINH NHUT on 8/15/2023.
//

#include "AVLTree.hpp"
#include "Template/Random.hpp"

#include <algorithm>
#include <fstream>
#include <iostream>

const int AVLTree::MAX_SIZE = 32;
const int AVLTree::MIN_VALUE = 0;
const int AVLTree::MAX_VALUE = 999;
const sf::Vector2f AVLTree::TREE_OFF_SET(35.f, 100.f);

AVLTree::AVLTree(const FontHolder& fonts, const ColorHolder& colors)
    : mFonts(fonts), mColors(colors), mRoot(nullptr) {
	randomize();
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

void AVLTree::insert(const int& value) {
	mRoot = pureInsert(mRoot, value);
	alignAsTree();
}

void AVLTree::rotateLeft() {
	mRoot = rotateLeft(mRoot);
	alignAsTree();
}

void AVLTree::rotateRight() {
	mRoot = rotateRight(mRoot);
	alignAsTree();
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

std::vector<AVLNode*> AVLTree::getInOrder(AVLNode* root) {
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

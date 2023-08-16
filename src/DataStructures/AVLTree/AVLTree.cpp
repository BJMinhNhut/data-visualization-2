//
// Created by MINH NHUT on 8/15/2023.
//

#include "AVLTree.hpp"
#include "Template/Random.hpp"

#include <iostream>

const int AVLTree::MAX_SIZE = 32;
const int AVLTree::MIN_VALUE = 0;
const int AVLTree::MAX_VALUE = 999;
const sf::Vector2f AVLTree::TREE_OFF_SET(35.f, 80.f);

AVLTree::AVLTree(const FontHolder& fonts, const ColorHolder& colors)
    : mFonts(fonts), mColors(colors), mRoot(nullptr) {
	for (int i = 0; i < 10; ++i) {
		int value = Random::getInt(MIN_VALUE, MAX_VALUE);
		insert(value);
	}
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

void AVLTree::loadArray(const std::vector<int>& array) {
	for (auto& value : array) {
		mRoot = pureInsert(mRoot, value);
	}
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

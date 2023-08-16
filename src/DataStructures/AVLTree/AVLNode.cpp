//
// Created by MINH NHUT on 8/15/2023.
//

#include "AVLNode.hpp"

#include <iostream>

AVLNode::AVLNode(const FontHolder& fonts, const ColorHolder& colors)
    : PolyNode(fonts, colors), mLeft(nullptr), mRight(nullptr), mHeight(0), mDepth(0) {}

void AVLNode::attachLeft(AVLNode* node) {
	if (mLeft == nullptr) {
		mLeft = node;
		mLeft->setPosition(getPosition());
		mLeft->setDepth(mDepth + 1);
		mHeight = mLeft->getHeight() + 1;
		addEdgeOut(mLeft);
	} else
		assert(mLeft == node);
}

void AVLNode::attachRight(AVLNode* node) {
	if (mRight == nullptr) {
		mRight = node;
		mRight->setPosition(getPosition());
		mRight->setDepth(mDepth + 1);
		mHeight = mRight->getHeight() + 1;
		addEdgeOut(mRight);
	} else
		assert(mRight == node);
}

void AVLNode::setDepth(int depth) {
	mDepth = depth;
}

AVLNode* AVLNode::getLeft() const {
	return mLeft;
}

AVLNode* AVLNode::getRight() const {
	return mRight;
}

int AVLNode::getHeight() const {
	return mHeight;
}

int AVLNode::getDepth() const {
	return mDepth;
}
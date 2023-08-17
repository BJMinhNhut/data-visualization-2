//
// Created by MINH NHUT on 8/15/2023.
//

#include "AVLNode.hpp"

#include <iostream>

AVLNode::AVLNode(const FontHolder& fonts, const ColorHolder& colors)
    : PolyNode(fonts, colors), mLeft(nullptr), mRight(nullptr), mHeight(0), mDepth(0) {}

void AVLNode::attachLeft(AVLNode* node) {
	if (mLeft == node)
		return;
	if (mLeft)
		detachLeft();
	if (node == nullptr)
		return;

	mLeft = node;
	node->setParent(this);
	mHeight = std::max(mHeight, mLeft->getHeight() + 1);
	addEdgeOut(mLeft);
}

void AVLNode::attachRight(AVLNode* node) {
	if (mRight == node)
		return;
	if (mRight)
		detachRight();
	if (node == nullptr)
		return;

	mRight = node;
	node->setParent(this);
	updateHeight();
	addEdgeOut(mRight);
}

void AVLNode::detachLeft() {
	removeEdgeOut(mLeft);
	mLeft = nullptr;
	updateHeight();
}

void AVLNode::detachRight() {
	removeEdgeOut(mRight);
	mRight = nullptr;
	updateHeight();
}

void AVLNode::setDepth(int depth) {
	mDepth = depth;
}

void AVLNode::setParent(AVLNode* node) {
	mParent = node;
}

AVLNode* AVLNode::getParent() const {
	return mParent;
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

void AVLNode::updateHeight() {
	mHeight = 0;
	if (mLeft)
		mHeight = std::max(mHeight, mLeft->getHeight() + 1);
	if (mRight)
		mHeight = std::max(mHeight, mRight->getHeight() + 1);
}
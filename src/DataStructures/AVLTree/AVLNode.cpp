//
// Created by MINH NHUT on 8/15/2023.
//

#include "AVLNode.hpp"

#include <iostream>

AVLNode::AVLNode(const FontHolder& fonts, const ColorHolder& colors)
    : PolyNode(fonts, colors),
      mLeft(nullptr),
      mRight(nullptr),
      mParent(nullptr),
      mHeight(0),
      mDepth(0),
      visualBackupParent(nullptr),
      visualLeftChild(false) {}

void AVLNode::attachLeft(AVLNode* node) {
	if (mLeft == node)
		return;
	if (mLeft)
		detachLeft();
	if (node == nullptr)
		return;

	mLeft = node;

	if (AVLNode* parent = node->getParent()) {
		if (node == parent->getLeft())
			parent->detachLeft();
		else
			parent->detachRight();
	}
	node->setParent(this);

	updateHeight();
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

	if (AVLNode* parent = node->getParent()) {
		if (node == parent->getLeft())
			parent->detachLeft();
		else
			parent->detachRight();
	}
	node->setParent(this);

	updateHeight();
	addEdgeOut(mRight);
}

void AVLNode::detachLeft() {
	assert(mLeft != nullptr);
	removeEdgeOut(mLeft);
	mLeft->setParent(nullptr);
	mLeft = nullptr;
	updateHeight();
}

void AVLNode::detachRight() {
	assert(mRight != nullptr);
	removeEdgeOut(mRight);
	mRight->setParent(nullptr);
	mRight = nullptr;
	updateHeight();
}

void AVLNode::fakeDetach() {
	assert(isLeaf() && mParent != nullptr && visualBackupParent == nullptr);
	visualBackupParent = mParent;
	if (mParent->getLeft() == this) {
		visualLeftChild = true;
		mParent->detachLeft();
	} else {
		visualLeftChild = false;
		mParent->detachRight();
	}
	setTargetScale(0.f, 0.f, Smooth);
}

void AVLNode::revertFakeDetach() {
	assert(visualBackupParent != nullptr);
	setTargetScale(1.f, 1.f, Smooth);
	if (visualLeftChild)
		visualBackupParent->attachLeft(this);
	else
		visualBackupParent->attachRight(this);
	visualBackupParent = nullptr;
	visualLeftChild = false;
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

int AVLNode::getBalanceFactor() {
	updateHeight();
	return (mLeft ? mLeft->getHeight() : -1) - (mRight ? mRight->getHeight() : -1);
}

bool AVLNode::isLeaf() const {
	return mLeft == nullptr && mRight == nullptr;
}

void AVLNode::updateHeight() {
	mHeight = 0;
	if (mLeft) {
		mLeft->updateHeight();
		mHeight = std::max(mHeight, mLeft->getHeight() + 1);
	}
	if (mRight) {
		mRight->updateHeight();
		mHeight = std::max(mHeight, mRight->getHeight() + 1);
	}
}
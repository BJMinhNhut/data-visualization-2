//
// Created by MINH NHUT on 8/23/2023.
//

#include "Tree234.hpp"

Tree234::Tree234(const FontHolder& fonts, const ColorHolder& colors)
    : mFonts(fonts), mColors(colors), mRoot(nullptr) {}

void Tree234::insert(const int& value) {
	if (mRoot == nullptr) {
		mRoot = new Node234(mFonts, mColors);
		mRoot->insert(value);
		attachChild(Ptr(mRoot));
		return;
	}
	Node234* cur = mRoot;
	while (cur != nullptr) {
		if (cur->overflow())
			cur = split(cur);
		if (cur->isLeaf())
			break;
		else {
			cur = cur->findChild(value);
		}
	}
	assert(cur != nullptr);
	cur->insert(value);
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
	detachChild(*node);
	return root;
}
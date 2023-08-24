//
// Created by MINH NHUT on 8/23/2023.
//

#include "Tree234.hpp"

Tree234::Tree234(const FontHolder& fonts, const ColorHolder& colors)
    : mFonts(fonts), mColors(colors), mRoot(nullptr) {}

void Tree234::insert(const int& value) {
	Node234* insertedNode = insertBST(value);
}

Node234* Tree234::insertBST(const int& value) {
	if (mRoot == nullptr) {
		mRoot = new Node234(mFonts, mColors);
		mRoot->insert(value);
		attachChild(Ptr(mRoot));
		return mRoot;
	}
	Node234* cur = mRoot;
	while (cur != nullptr) {
		if (cur->isLeaf())
			break;
		else {
			cur = cur->findChild(value);
		}
	}
	cur->insert(value);
	return cur;
}

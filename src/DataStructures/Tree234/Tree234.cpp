//
// Created by MINH NHUT on 8/23/2023.
//

#include "Tree234.hpp"

#include <iostream>
#include <stack>

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
	align();
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

void Tree234::align() {
	if (mRoot == nullptr)
		return;
	std::vector<std::vector<Node234*>> layers;

	// DFS
	std::stack<Node234*> mStack;
	mStack.push(mRoot);
	mRoot->setDepth(0);
	while (!mStack.empty()) {
		Node234* cur = mStack.top();
		mStack.pop();
		if (layers.size() < cur->getDepth() + 1)
			layers.emplace_back();
		layers[cur->getDepth()].push_back(cur);
		for (auto& node : cur->getChildList()) {
			if (node == nullptr)
				break;
			mStack.push(node);
			node->setDepth(cur->getDepth() + 1);
		}
	}

	// left-aligned layout
	int leaf = (int)layers.size() - 1;
	for (int depth = leaf; depth >= 0; --depth) {
		float leftBound = 0.f;
		for (int i = 0; i < layers[depth].size(); ++i) {
			if (i > 0)
				leftBound += Node234::OFFSET.x;

			layers[depth][i]->calcWidth();
			layers[depth][i]->setTargetPosition(
			    sf::Vector2f(leftBound + layers[depth][i]->getWidth() / 2.f,
			                 Node234::OFFSET.y * (float)depth),
			    Smooth);
			leftBound += layers[depth][i]->getWidth();
		}
	}

	// centralize nodes
	sf::Vector2f delta(-mRoot->getWidth() / 2.f, 0.f);
	for (int depth = leaf; depth >= 0; --depth) {
		for (auto& node : layers[depth]) {
			node->setTargetPosition(node->getTargetPosition() + delta, Smooth);
		}
	}
}
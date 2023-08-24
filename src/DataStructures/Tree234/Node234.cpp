//
// Created by MINH NHUT on 8/23/2023.
//

#include "Node234.hpp"

#include <SFML/Graphics/RenderStates.hpp>
#include <SFML/Graphics/RenderTarget.hpp>

#include <iostream>

const int Node234::MAX_DATA = 3;
const int Node234::MAX_CHILD = 4;
const int Node234::MIN_VALUE = 0;
const int Node234::MAX_VALUE = 99;
const float Node234::NODE_RADIUS = 16.f;

Node234::Node234(const FontHolder& fonts, const ColorHolder& colors)
    : mChildren(MAX_CHILD, nullptr), mData(), mFonts(fonts), mColors(colors), mParent(nullptr) {}

void Node234::insert(int value) {
	int position = (int)mData.size();
	for (int i = 0; i < mData.size(); ++i) {
		if (mData[i]->getIntData() < value) {
			position = i + 1;
			break;
		}
	}
	insert(position, value);
}

void Node234::setChild(int id, Node234* child) {
	assert(mChildren[id] == nullptr);
	mChildren[id] = child;

	if (child == nullptr)
		return;
	child->setParent(this);
}

void Node234::setParent(Node234* parent) {
	mParent = parent;
}

void Node234::split(int& pivot, Node234*& left, Node234*& right) {
	assert(overflow());
	pivot = mData[1]->getIntData();

	left = new Node234(mFonts, mColors);
	left->insert(mData[0]->getIntData());
	left->setChild(0, mChildren[0]);
	left->setChild(1, mChildren[1]);

	right = new Node234(mFonts, mColors);
	right->insert(mData[2]->getIntData());
	right->setChild(0, mChildren[2]);
	right->setChild(1, mChildren[3]);
}

void Node234::insertSplit(int id, int pivot, Node234* left, Node234* right) {
	int low = id > 0 ? mData[id - 1]->getIntData() : -1;
	int high = id < mData.size() ? mData[id]->getIntData() : MAX_VALUE + 1;
	assert(low <= pivot && pivot <= high);
	mChildren[id] = nullptr;
	mChildren.insert(mChildren.begin() + id, nullptr);
	setChild(id, left);
	setChild(id + 1, right);
	insert(id, pivot);
}

Node234* Node234::getParent() const {
	return mParent;
}

bool Node234::isLeaf() const {
	return mChildren[0] == nullptr;
}

bool Node234::overflow() const {
	return mData.size() == MAX_DATA;
}

Node234* Node234::findChild(int value) const {
	for (int i = 0; i < mData.size(); ++i) {
		if (i + 1 == mData.size() || mData[i + 1]->getIntData() > value)
			return mChildren[i + 1];
	}
	assert(false);
	return nullptr;
}

int Node234::getChildID(Node234* node) const {
	for (int i = 0; i < mChildren.size(); ++i) {
		if (mChildren[i] == node)
			return i;
	}
	assert(false);
	return -1;
}

void Node234::insert(int id, int value) {
	auto* newNode = new PolyNode(mFonts, mColors);
	newNode->setData(value);
	newNode->setPoint(4);
	attachChild(Ptr(newNode));
	mData.insert(mData.begin() + id, newNode);
	align();
}

void Node234::align() {
	float delta = -((float)mData.size() - 1.f) * NODE_RADIUS;
	for (auto& node : mData) {
		node->setTargetPosition(delta, 0.f, None);
		delta += 2.f * NODE_RADIUS;
	}
}
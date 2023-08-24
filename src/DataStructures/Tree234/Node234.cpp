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
    : mChildren(MAX_CHILD, nullptr), mData(), mFonts(fonts), mColors(colors) {}

void Node234::insert(int value) {
	auto* newNode = new PolyNode(mFonts, mColors);
	newNode->setData(value);
	newNode->setPoint(4);
	attachChild(Ptr(newNode));
	int position = (int)mData.size();
	for (int i = 0; i < mData.size(); ++i) {
		if (mData[i]->getIntData() < value) {
			position = i + 1;
			break;
		}
	}
	mData.insert(mData.begin() + position, newNode);
	align();
}

void Node234::setChild(int id, Node234* child) {
	assert(mChildren[id] == nullptr);
	mChildren[id] = child;
}

bool Node234::isLeaf() const {
	return mChildren[0] == nullptr;
}

Node234* Node234::findChild(int value) const {
	for (int i = 0; i < mData.size(); ++i) {
		if (i + 1 == mData.size() || mData[i + 1]->getIntData() > value)
			return mChildren[i + 1];
	}
	assert(false);
	return nullptr;
}

void Node234::align() {
	float delta = -((float)mData.size() - 1.f) * NODE_RADIUS;
	for (auto& node : mData) {
		node->setTargetPosition(delta, 0.f, None);
		delta += 2.f * NODE_RADIUS;
	}
}
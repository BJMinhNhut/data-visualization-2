//
// Created by MINH NHUT on 8/23/2023.
//

#include "Node234.hpp"

#include <SFML/Graphics/RenderStates.hpp>
#include <SFML/Graphics/RenderTarget.hpp>

const int Node234::MAX_DATA = 3;
const int Node234::MAX_CHILD = 4;
const int Node234::MIN_VALUE = 0;
const int Node234::MAX_VALUE = 99;
const float Node234::NODE_RADIUS = 16.f;

Node234::Node234(const FontHolder& fonts, const ColorHolder& colors)
    : mChildren(), mData(), mFonts(fonts), mColors(colors) {}

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

void Node234::align() {
	float delta;
	switch (mData.size()) {
		case 1:
			delta = 0.f;
			break;
		case 2:
			delta = -2.f * NODE_RADIUS;
			break;
		case 3:
			delta = -3.f * NODE_RADIUS;
			break;
		default:
			assert(false);
	}
	for (auto& node : mData) {
		node->setTargetPosition(delta, 0.f, None);
		delta += 2.f * NODE_RADIUS;
	}
}
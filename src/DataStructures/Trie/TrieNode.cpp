//
// Created by MINH NHUT on 8/18/2023.
//

#include "TrieNode.hpp"

const sf::Vector2f TrieNode::TREE_OFF_SET(60.f, 90.f);

TrieNode::TrieNode(const FontHolder& fonts, const ColorHolder& colors, char character)
    : PolyNode(fonts, colors),
      mChar(character),
      mFrequency(0),
      mDepth(0),
      mChildren(100, nullptr),
      mFonts(fonts),
      mColors(colors) {
	assert(isupper(character) || isspace(character));
	setData(std::string(1, character));
}

TrieNode* TrieNode::addString(const std::string& str, int freq) {
	mFrequency += freq;
	if (str.empty()) {
		if (mFrequency != 0)
			highlight(Secondary);
		else
			highlight(PolyNode::None);
		return this;
	}
	char firstCH = str[0];
	if (!hasChild(firstCH))
		addChild(firstCH);
	return getChild(firstCH)->addString(str.substr(1, str.size() - 1), freq);
}

TrieNode* TrieNode::addChild(char character) {
	assert(!hasChild(character));
	const int id = getCharID(character);
	mChildren[id] = new TrieNode(mFonts, mColors, character);
	addEdgeOut(mChildren[id]);
	attachChild(TrieNode::Ptr(mChildren[id]));
	return mChildren[id];
}

sf::Vector2f TrieNode::align() {
	sf::Vector2f width(0.f, 0.f);
	std::vector<TrieNode*> availChild;
	std::vector<sf::Vector2f> childWidth;
	for (auto& node : mChildren)
		if (node != nullptr) {
			availChild.push_back(node);
			childWidth.push_back(node->align());
		}

	int mid1, mid2;
	if (availChild.empty())
		return width;
	else if (availChild.size() % 2 == 1) {
		mid1 = mid2 = (int)availChild.size() / 2;
		availChild[mid1]->setTargetPosition(0.f, TREE_OFF_SET.y, Smooth);
		width = childWidth[mid1];
	} else {
		mid1 = (int)availChild.size() / 2 - 1;
		mid2 = (int)availChild.size() / 2;
		availChild[mid1]->setTargetPosition(-(childWidth[mid1].y + TREE_OFF_SET.x / 2.f),
		                                    TREE_OFF_SET.y, Smooth);
		availChild[mid2]->setTargetPosition(childWidth[mid2].x + TREE_OFF_SET.x / 2.f,
		                                    TREE_OFF_SET.y, Smooth);
		width.x = childWidth[mid1].x + childWidth[mid1].y + TREE_OFF_SET.x / 2.f;
		width.y = childWidth[mid2].x + childWidth[mid2].y + TREE_OFF_SET.x / 2.f;
	}

	for (int i = mid2 + 1; i < (int)availChild.size(); ++i) {
		availChild[i]->setTargetPosition(width.y + TREE_OFF_SET.x + childWidth[i].x, TREE_OFF_SET.y,
		                                 Smooth);
		width.y += TREE_OFF_SET.x + childWidth[i].x + childWidth[i].y;
	}
	for (int i = mid1 - 1; i >= 0; --i) {
		availChild[i]->setTargetPosition(-width.x - TREE_OFF_SET.x - childWidth[i].y,
		                                 TREE_OFF_SET.y, Smooth);
		width.x += TREE_OFF_SET.x + childWidth[i].x + childWidth[i].y;
	}
	return width;
}

void TrieNode::clear() {
	for (auto& node : mChildren)
		if (node != nullptr) {
			node->clear();
			removeEdgeOut(node);
			detachChild(*node);
			node = nullptr;
		}
}

void TrieNode::clearHighlight() {
	highlight(PolyNode::None);
	for (auto& node : mChildren)
		if (node != nullptr)
			node->clearHighlight();
}

bool TrieNode::hasChild(char character) const {
	return mChildren[getCharID(character)] != nullptr;
}

TrieNode* TrieNode::getChild(char character) const {
	return mChildren[getCharID(character)];
}

char TrieNode::getChar() const {
	return mChar;
}

int TrieNode::depth() const {
	return mDepth;
}

int TrieNode::frequency() const {
	return mFrequency;
}

int TrieNode::count() const {
	int ans = mFrequency;
	for (auto& node : mChildren)
		if (node != nullptr)
			ans += node->count();
	return ans;
}

int TrieNode::getCharID(const char& ch) {
	assert(isupper(ch) || isspace(ch));
	return (int)ch - (int)'A';
}

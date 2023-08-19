//
// Created by MINH NHUT on 8/18/2023.
//

#include "TrieNode.hpp"

const sf::Vector2f TrieNode::TREE_OFF_SET(60.f, 90.f);

TrieNode::TrieNode(const FontHolder& fonts, const ColorHolder& colors, char character)
    : PolyNode(fonts, colors),
      mChar(character),
      mFrequency(0),
      mEndString(0),
      mChildren(100, nullptr),
      mFonts(fonts),
      mColors(colors),
      mParent(nullptr),
      mBin(nullptr) {
	assert(isupper(character) || isspace(character));
	setData(std::string(1, character));
}

TrieNode* TrieNode::addString(const std::string& str, int freq) {
	mFrequency += freq;
	if (str.empty()) {
		mEndString += freq;
		highlightOff();
		return this;
	}
	char firstCH = str[0];
	if (!hasChild(firstCH))
		addChild(firstCH);
	return getChild(firstCH)->addString(str.substr(1, str.size() - 1), freq);
}

void TrieNode::popNode(const std::string& str) {
	auto* cur = const_cast<TrieNode*>(this);
	for (char ch : str) {
		cur = cur->getChild(ch);
		assert(cur != nullptr);
	}
	assert(cur->getParent() != nullptr);
	cur->getParent()->removeLeaf(cur->getChar());
}

void TrieNode::removeLeaf(char character) {
	const int id = getCharID(character);
	assert(mChildren[id] != nullptr);
	assert(mChildren[id]->isLeaf());
	if (mBin != nullptr)
		detachChild(*mBin);

	mBin = mChildren[id];
	mBin->setTargetScale(0.f, 0.f, Smooth);
	removeEdgeOut(mBin);
	mChildren[id] = nullptr;
}

TrieNode* TrieNode::addChild(char character) {
	assert(!hasChild(character));
	const int id = getCharID(character);
	mChildren[id] = new TrieNode(mFonts, mColors, character);
	addEdgeOut(mChildren[id]);
	mChildren[id]->setParent(this);
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
	highlightOff();
	for (auto& node : mChildren)
		if (node != nullptr)
			node->highlightOff();
}

void TrieNode::highlightOn() {
	highlight(Primary);
}

void TrieNode::highlightOff() {
	if (mEndString > 0)
		highlight(PolyNode::Secondary);
	else
		highlight(PolyNode::None);
}

bool TrieNode::hasChild(char character) const {
	return mChildren[getCharID(character)] != nullptr;
}

TrieNode* TrieNode::getNode(const std::string& str) const {
	auto* cur = const_cast<TrieNode*>(this);
	for (char ch : str) {
		cur = cur->getChild(ch);
		if (cur == nullptr)
			break;
	}
	return cur;
}

bool TrieNode::hasString(const std::string& str) const {
	auto* cur = const_cast<TrieNode*>(this);
	for (char ch : str) {
		cur = cur->getChild(ch);
		if (cur == nullptr)
			return false;
	}
	return cur->isStringEnd();
}

bool TrieNode::isStringEnd() const {
	return mEndString;
}

TrieNode* TrieNode::getParent() const {
	return mParent;
}

TrieNode* TrieNode::getChild(char character) const {
	return mChildren[getCharID(character)];
}

char TrieNode::getChar() const {
	return mChar;
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

bool TrieNode::isLeaf() const {
	return std::all_of(mChildren.begin(), mChildren.end(),
	                   [](TrieNode* a) { return a == nullptr; });
}

std::vector<TrieNode*> TrieNode::getEndNodes() const {
	std::vector<TrieNode*> nodes;
	if (mEndString > 0)
		nodes.push_back(const_cast<TrieNode*>(this));
	for (auto& node : mChildren)
		if (node) {
			const auto& tempList = node->getEndNodes();
			nodes.insert(nodes.end(), tempList.begin(), tempList.end());
		}
	return nodes;
}

int TrieNode::getCharID(const char& ch) {
	assert(isupper(ch) || isspace(ch));
	return (int)ch - (int)'A';
}

void TrieNode::setParent(TrieNode* parent) {
	mParent = parent;
}

void TrieNode::updateCurrent(sf::Time dt) {
	PolyNode::updateCurrent(dt);
	if (mBin != nullptr && mBin->getScale().x < SceneNode::EPS) {
		detachChild(*mBin);
		mBin = nullptr;
	}
}

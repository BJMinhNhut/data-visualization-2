//
// Created by MINH NHUT on 8/18/2023.
//

#include "TrieNode.hpp"

TrieNode::TrieNode(const FontHolder& fonts, const ColorHolder& colors, char character)
    : PolyNode(fonts, colors), mChar(character), mFrequency(0), mDepth(0) {
	assert(isupper(character));
	setLabel(mFrequency);
	setData(std::string(1, character));
}

void TrieNode::operator++() {
	mFrequency++;
	setLabel(mFrequency);
}

void TrieNode::operator--() {
	mFrequency--;
	setLabel(mFrequency);
}

int TrieNode::depth() const {
	return mDepth;
}

int TrieNode::frequency() const {
	return mFrequency;
}

int TrieNode::getCharID(const char& ch) {
	return (int)ch - (int)'A';
}

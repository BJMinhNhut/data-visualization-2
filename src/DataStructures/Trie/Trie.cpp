//
// Created by MINH NHUT on 8/19/2023.
//

#include "Trie.hpp"

const int Trie::MAX_SIZE = 40;
const int Trie::MIN_LENGTH = 1;
const int Trie::MAX_LENGTH = 5;
const sf::Vector2f Trie::TREE_OFF_SET(27.f, 90.f);

Trie::Trie(const FontHolder& fonts, const ColorHolder& colors)
    : mSize(0), mNumString(0), mFonts(fonts), mColors(colors) {
	mRoot = new TrieNode(fonts, colors, 'A');
	attachChild(TrieNode::Ptr(mRoot));
}

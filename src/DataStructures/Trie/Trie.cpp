//
// Created by MINH NHUT on 8/19/2023.
//

#include "Trie.hpp"

const int Trie::MAX_SIZE = 40;
const int Trie::MIN_LENGTH = 1;
const int Trie::MAX_LENGTH = 5;

Trie::Trie(const FontHolder& fonts, const ColorHolder& colors) : mFonts(fonts), mColors(colors) {
	mRoot = new TrieNode(fonts, colors, ' ');
	attachChild(TrieNode::Ptr(mRoot));
	push("ABC");
	push("ADB");
	push("ADC");
	push("AXY");
	push("XYZ");
}

void Trie::push(const std::string& str) {
	mRoot->addString(str, 1);
	mRoot->align();
}

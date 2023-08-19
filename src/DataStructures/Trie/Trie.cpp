//
// Created by MINH NHUT on 8/19/2023.
//

#include "Trie.hpp"
#include "Template/Random.hpp"

#include <iostream>

const int Trie::MAX_SIZE = 40;
const int Trie::MIN_LENGTH = 1;
const int Trie::MAX_LENGTH = 5;

Trie::Trie(const FontHolder& fonts, const ColorHolder& colors) : mFonts(fonts), mColors(colors) {
	mRoot = new TrieNode(fonts, colors, ' ');
	attachChild(TrieNode::Ptr(mRoot));
	randomize();
	//	push("ABC");
	//	push("ADB");
	//	push("ADC");
	//	push("AXY");
	//	push("XYZ");
}

std::string Trie::getRandString(int minLen, int maxLen) {
	int len = Random::getInt(minLen, maxLen);
	std::string str;
	while (len--)
		str.push_back((char)Random::getInt('A', 'Z'));
	return str;
}

int Trie::count() const {
	return mRoot->count();
}

void Trie::push(const std::string& str) {
	mRoot->addString(str, 1);
	mRoot->align();
}

void Trie::clear() {
	mRoot->clear();
}

void Trie::randomize() {
	clear();
	std::string seed = getRandString(2, 2 * MAX_LENGTH);
	std::cout << "seed: " << seed << '\n';
	int num = Random::getInt(1, 10);
	while (num--) {
		std::string str;
		int len = Random::getInt(MIN_LENGTH, MAX_LENGTH);
		while (len--)
			str.push_back(seed[Random::getInt(0, (int)seed.size() - 1)]);
		push(str);
	}
}

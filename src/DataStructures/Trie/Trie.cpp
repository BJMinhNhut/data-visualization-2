//
// Created by MINH NHUT on 8/19/2023.
//

#include "Trie.hpp"
#include "Template/Random.hpp"

#include <fstream>
#include <iostream>

const int Trie::MAX_SIZE = 40;
const int Trie::MIN_LENGTH = 1;
const int Trie::MAX_LENGTH = 6;

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
	sf::Vector2f width = mRoot->align();
	float mid = (-width.x + width.y) / 2.f;
	mRoot->setTargetPosition(-mid, 0.f, Smooth);
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

void Trie::loadFromFile(const std::string& fileDir) {
	std::ifstream fileStream(fileDir);
	int numString = 0;
	std::string token;
	clear();
	while (fileStream >> token && numString < MAX_SIZE) {
		try {
			format(token);
			if (!valid(token))
				throw std::exception();
#ifdef SFML_DEBUG
			std::cout << "Token [" << token << "] read\n";
#endif
			push(token);
			numString++;
		} catch (std::exception& e) {
#ifdef SFML_DEBUG
			std::cerr << "Token [" << token << "] is not convertible\n";
#endif
		}
	}
	fileStream.close();
}

void Trie::format(std::string& str) {
	while (!str.empty() && str.back() == ',')
		str.pop_back();
}

bool Trie::valid(const std::string& str) {
	return !str.empty() && str.length() < MAX_LENGTH &&
	       std::all_of(str.begin(), str.end(), isupper);
}

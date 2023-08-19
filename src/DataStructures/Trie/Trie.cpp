//
// Created by MINH NHUT on 8/19/2023.
//

#include "Trie.hpp"
#include "Template/Random.hpp"
#include "TrieCode.hpp"

#include <fstream>
#include <iostream>

const int Trie::MAX_SIZE = 40;
const int Trie::MIN_LENGTH = 1;
const int Trie::MAX_LENGTH = 6;

Trie::Trie(const FontHolder& fonts, const ColorHolder& colors) : mFonts(fonts), mColors(colors) {
	mRoot = new TrieNode(fonts, colors, ' ');
	attachChild(TrieNode::Ptr(mRoot));
	randomize();
}

std::string Trie::getRandomElement() const {
	std::vector<TrieNode*> nodes = mRoot->getEndNodes();
	assert(!nodes.empty());
	TrieNode* chosen = nodes[Random::getInt(0, (int)nodes.size() - 1)];
	return getString(chosen);
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

std::pair<std::vector<Animation>, std::string> Trie::insertAnimation(const std::string& str) {
	const std::string code = TrieCode::Insert;
	std::vector<Animation> list;
	list.push_back(Animation({}, "Insert " + str + " to trie."));

	int lcp = getLCP(str);
	TrieNode* cur = mRoot;
	list.push_back(Animation(
	    {0}, "Assign cur = root", [&]() { mRoot->highlight(PolyNode::Primary); },
	    [&]() { mRoot->highlight(PolyNode::None); }));
	for (int i = 0; i < lcp; ++i) {
		cur = cur->getChild(str[i]);
		std::string ch(1, str[i]);
		list.push_back(Animation(
		    {1, 4, 5}, "The " + ch + " child exists, continue",
		    [&, cur]() {
			    cur->getParent()->highlightOff();
			    cur->highlightOn();
		    },
		    [&, cur]() {
			    cur->getParent()->highlightOn();
			    cur->highlightOff();
		    }));
	}

	for (int i = lcp; i < str.size(); ++i) {
		std::string ch(1, str[i]);
		list.push_back(Animation(
		    {1, 2, 3, 4, 5}, "The " + ch + " child doesn't exist, create it",
		    [&, str, i]() {
			    TrieNode* newNode = mRoot->addString(str.substr(0, i + 1), 0);
			    mRoot->align();
			    newNode->getParent()->highlightOff();
			    newNode->highlightOn();
		    },
		    [&, str, i]() {
			    mRoot->popNode(str.substr(0, i + 1));
			    mRoot->align();
		    }));
	}

	list.push_back(Animation(
	    {6}, "Finish insertion, mark the last node as string end. Complexity is O(|s|).",
	    [&, str]() {
		    TrieNode* last;
		    last = mRoot->addString(str, 1);
		    last->highlightOff();
	    },
	    [&, str]() {
		    TrieNode* last = mRoot->addString(str, -1);
		    last->highlightOn();
	    }));

	return std::make_pair(list, code);
}

std::pair<std::vector<Animation>, std::string> Trie::searchAnimation(const std::string& str) {
	const std::string code = TrieCode::Search;
	std::vector<Animation> list;
	list.push_back(Animation({}, "Search for " + str + " in trie."));

	int lcp = getLCP(str);
	TrieNode* cur = mRoot;
	list.push_back(Animation(
	    {0}, "Assign cur = root", [&]() { mRoot->highlight(PolyNode::Primary); },
	    [&]() { mRoot->highlight(PolyNode::None); }));
	for (int i = 0; i < lcp; ++i) {
		cur = cur->getChild(str[i]);
		std::string ch(1, str[i]);
		list.push_back(Animation(
		    {1, 4}, "The " + ch + " child exists, continue",
		    [&, cur]() {
			    cur->getParent()->highlightOff();
			    cur->highlightOn();
		    },
		    [&, cur]() {
			    cur->getParent()->highlightOn();
			    cur->highlightOff();
		    }));
	}

	if (lcp == str.size()) {
		if (mRoot->hasString(str))
			list.push_back(Animation({5}, "Node is marked string end, hence " + str + " is FOUND"));
		else
			list.push_back(Animation({6},
			                         "Node isn't marked string end, hence " + str + " is NOT_FOUND",
			                         [&]() { clearHighlight(); }));
	} else {
		list.push_back(Animation({1, 2, 3}, "Null node reached, hence " + str + " is NOT_FOUND",
		                         [&]() { clearHighlight(); }));
	}

	return std::make_pair(list, code);
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

void Trie::clearHighlight() {
	mRoot->clearHighlight();
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

int Trie::getLCP(const std::string& str) const {
	TrieNode* cur = mRoot;
	int ans = 0;
	for (char ch : str) {
		cur = cur->getChild(ch);
		if (cur == nullptr)
			return ans;
		++ans;
	}
	return ans;
}

std::string Trie::getString(TrieNode* node) const {
	std::string str;
	while (node != mRoot) {
		str.push_back(node->getChar());
		node = node->getParent();
	}
	std::reverse(str.begin(), str.end());
	return str;
}

void Trie::format(std::string& str) {
	while (!str.empty() && str.back() == ',')
		str.pop_back();
}

bool Trie::valid(const std::string& str) {
	return !str.empty() && str.length() < MAX_LENGTH &&
	       std::all_of(str.begin(), str.end(), isupper);
}

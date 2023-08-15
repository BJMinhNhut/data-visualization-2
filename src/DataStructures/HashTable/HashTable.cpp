//
// Created by MINH NHUT on 8/14/2023.
//

#include "HashTable.hpp"
#include "HashCode.hpp"
#include "Template/Random.hpp"

#include <fstream>
#include <iostream>

const unsigned int HashTable::MAX_SIZE = 60;
const int HashTable::PADDING = 100;
const int HashTable::MIN_VALUE = 0;
const int HashTable::MAX_VALUE = 199;
const int HashTable::WIDTH = 10;

HashTable::HashTable(const FontHolder& fonts, const ColorHolder& colors)
    : mFonts(fonts), mColors(colors), mNodes(), mUsed(0) {
	setSize(Random::getInt(20, MAX_SIZE));
	randomize();
}

void HashTable::setSize(const unsigned int& size) {
	while (mNodes.size() < size) {
		mNodes.push_back(new PolyNode(mFonts, mColors));
		mNodes.back()->setLabel((int)mNodes.size() - 1);
		attachChild(std::unique_ptr<PolyNode>(mNodes.back()));
	}
	while (mNodes.size() > size) {
		detachChild(*mNodes.back());
		mNodes.pop_back();
	}
	align();
}

void HashTable::randomize() {
	loadArray(Random::getArray(1, std::max(1, (int)getSize() / 3 * 2), MIN_VALUE, MAX_VALUE));
}

void HashTable::loadArray(const std::vector<int>& array) {
	clearData();
	for (auto& val : array)
		insert(val);
}

void HashTable::loadFromFile(const std::string& fileDir) {
	std::ifstream fileStream(fileDir);
	std::vector<int> elements;
	std::string token;
	int value;
	while (fileStream >> token && elements.size() + 1 < mNodes.size()) {
		try {
			value = std::stoi(token);
			if (value < MIN_VALUE || value > MAX_VALUE)
				throw std::exception();
			std::cout << "Token [" << token << "] read\n";
			elements.push_back(value);
		} catch (std::exception& e) {
			std::cerr << "Token [" << token << "] is not convertible\n";
		}
	}
	fileStream.close();
	loadArray(elements);
}

unsigned int HashTable::getSize() const {
	return mNodes.size();
}

int HashTable::getUsed() const {
	return mUsed;
}

int HashTable::getRandomElement() const {
	std::vector<int> values;
	for (auto& node : mNodes)
		if (!node->getData().empty())
			values.push_back(node->getIntData());
	assert(!values.empty());
	return values[Random::getInt(0, (int)values.size() - 1)];
}

std::pair<std::vector<Animation>, std::string> HashTable::insertAnimation(const int& value) {
	const std::string& code = HashCode::Insert;
	std::vector<Animation> list;
	if (mUsed + 1 == mNodes.size()) {
		list.push_back(Animation(
		    {0}, "Hash table is filled up, so stop inserting new values.",
		    [&]() {
			    for (auto& node : mNodes)
				    if (!node->getData().empty())
					    node->highlight(PolyNode::Primary);
		    },
		    [&]() {
			    for (auto& node : mNodes)
				    node->highlight(PolyNode::None);
		    }));
	} else {
		list.push_back(Animation({0}, "Hash table has not been filled up, proceed to insert " +
		                                  std::to_string(value) + " to hash table."));
		int id = value % (int)mNodes.size();
		list.push_back(Animation(
		    {1}, "id = value % size = " + std::to_string(id),
		    [&, id]() { mNodes[id]->highlight(PolyNode::Primary); },
		    [&, id]() { mNodes[id]->highlight(PolyNode::None); }));
		int last = -1;
		while (!mNodes[id]->getData().empty()) {
			list.push_back(Animation(
			    {2, 3},
			    "hash[" + std::to_string(id) +
			        "] already contained a value, so check the next index.\n",
			    [&, id, last]() {
				    mNodes[id]->highlight(PolyNode::Primary);
				    if (last != -1)
					    mNodes[last]->highlight(PolyNode::None);
			    },
			    [&, id, last]() {
				    mNodes[id]->highlight(PolyNode::None);
				    if (last != -1)
					    mNodes[last]->highlight(PolyNode::Primary);
			    }));
			last = id;
			id = (id + 1) % (int)mNodes.size();
		}
		list.push_back(Animation(
		    {2}, "hash[" + std::to_string(id) + "] is empty, hence insertion position found!",
		    [&, id, last]() {
			    mNodes[id]->highlight(PolyNode::Primary);
			    if (last != -1)
				    mNodes[last]->highlight(PolyNode::None);
		    },
		    [&, id, last]() {
			    mNodes[id]->highlight(PolyNode::None);
			    if (last != -1)
				    mNodes[last]->highlight(PolyNode::Primary);
		    }));

		list.push_back(Animation(
		    {4},
		    "Insert " + std::to_string(value) + " to that position. Worst case complexity is O(n).",
		    [&, id, value]() { mNodes[id]->setData(value); },
		    [&, id]() { mNodes[id]->setData(""); }));

		mUsed++;
	}

	return std::make_pair(list, code);
}

std::pair<std::vector<Animation>, std::string> HashTable::deleteAnimation(const int& value) {
	const std::string& code = HashCode::Delete;
	std::vector<Animation> list;
	list.push_back(Animation({}, "Search for " + std::to_string(value) + " in the hash table."));
	int id = value % (int)mNodes.size();
	list.push_back(Animation(
	    {0}, "id = value % size = " + std::to_string(id),
	    [&, id]() { mNodes[id]->highlight(PolyNode::Primary); },
	    [&, id]() { mNodes[id]->highlight(PolyNode::None); }));
	int last = -1;
	while (!mNodes[id]->getData().empty()) {
		if (mNodes[id]->getIntData() != value) {
			list.push_back(Animation(
			    {1, 5},
			    "hash[" + std::to_string(id) + "] != " + std::to_string(value) +
			        ", so check the next index.\n",
			    [&, id, last]() {
				    mNodes[id]->highlight(PolyNode::Primary);
				    if (last != -1)
					    mNodes[last]->highlight(PolyNode::None);
			    },
			    [&, id, last]() {
				    mNodes[id]->highlight(PolyNode::None);
				    if (last != -1)
					    mNodes[last]->highlight(PolyNode::Primary);
			    }));
			last = id;
			id = (id + 1) % (int)mNodes.size();
		} else {
			list.push_back(Animation(
			    {1, 2}, "Found " + std::to_string(value) + " at index " + std::to_string(id) + ".",
			    [&, id, last]() {
				    mNodes[id]->highlight(PolyNode::Primary);
				    if (last != -1)
					    mNodes[last]->highlight(PolyNode::None);
			    },
			    [&, id, last]() {
				    mNodes[id]->highlight(PolyNode::None);
				    if (last != -1)
					    mNodes[last]->highlight(PolyNode::Primary);
			    }));
			list.push_back(Animation(
			    {3, 4},
			    "Remove the value at " + std::to_string(id) + ". Worst case complexity is O(n).",
			    [&, id]() { mNodes[id]->setData(""); },
			    [&, id, value]() { mNodes[id]->setData(value); }));
			mUsed--;
			return std::make_pair(list, code);
		}
	}
	list.push_back(Animation(
	    {},
	    "hash[" + std::to_string(id) + "] is empty, hence " + std::to_string(id) +
	        " is not found! Worst case complexity is O(n).",
	    [&, id, last]() {
		    mNodes[id]->highlight(PolyNode::Primary);
		    if (last != -1)
			    mNodes[last]->highlight(PolyNode::None);
	    },
	    [&, id, last]() {
		    mNodes[id]->highlight(PolyNode::None);
		    if (last != -1)
			    mNodes[last]->highlight(PolyNode::Primary);
	    }));

	return std::make_pair(list, code);
}

std::pair<std::vector<Animation>, std::string> HashTable::searchAnimation(const int& value) {
	const std::string& code = HashCode::Search;
	std::vector<Animation> list;
	list.push_back(Animation({}, "Search for " + std::to_string(value) + " in the hash table."));
	int id = value % (int)mNodes.size();
	list.push_back(Animation(
	    {0}, "id = value % size = " + std::to_string(id),
	    [&, id]() { mNodes[id]->highlight(PolyNode::Primary); },
	    [&, id]() { mNodes[id]->highlight(PolyNode::None); }));
	int last = -1;
	while (!mNodes[id]->getData().empty()) {
		if (mNodes[id]->getIntData() != value) {
			list.push_back(Animation(
			    {1, 4},
			    "hash[" + std::to_string(id) + "] != " + std::to_string(value) +
			        ", so check the next index.\n",
			    [&, id, last]() {
				    mNodes[id]->highlight(PolyNode::Primary);
				    if (last != -1)
					    mNodes[last]->highlight(PolyNode::None);
			    },
			    [&, id, last]() {
				    mNodes[id]->highlight(PolyNode::None);
				    if (last != -1)
					    mNodes[last]->highlight(PolyNode::Primary);
			    }));
			last = id;
			id = (id + 1) % (int)mNodes.size();
		} else {
			list.push_back(Animation(
			    {1, 3},
			    "Found " + std::to_string(value) + " at index " + std::to_string(id) +
			        ". Worst case complexity is O(n).",
			    [&, id, last]() {
				    mNodes[id]->highlight(PolyNode::Primary);
				    if (last != -1)
					    mNodes[last]->highlight(PolyNode::None);
			    },
			    [&, id, last]() {
				    mNodes[id]->highlight(PolyNode::None);
				    if (last != -1)
					    mNodes[last]->highlight(PolyNode::Primary);
			    }));
			return std::make_pair(list, code);
		}
	}
	list.push_back(Animation(
	    {5},
	    "hash[" + std::to_string(id) + "] is empty, hence " + std::to_string(id) +
	        " is not found! Worst case complexity is O(n).",
	    [&, id, last]() {
		    mNodes[id]->highlight(PolyNode::Primary);
		    if (last != -1)
			    mNodes[last]->highlight(PolyNode::None);
	    },
	    [&, id, last]() {
		    mNodes[id]->highlight(PolyNode::None);
		    if (last != -1)
			    mNodes[last]->highlight(PolyNode::Primary);
	    }));

	return std::make_pair(list, code);
}

void HashTable::align() {
	for (int i = 0; i < mNodes.size(); ++i) {
		int col = i % WIDTH;
		int row = i / WIDTH;
		mNodes[i]->setTargetPosition(float(col * PADDING), float(row * PADDING), PolyNode::Smooth);
	}
}

void HashTable::insert(const int& value) {
	unsigned int id = getID(value);
	unsigned int insertPos = id;
	while (!mNodes[insertPos]->getData().empty()) {
		insertPos = (insertPos + 1) % mNodes.size();
		assert(insertPos != id);
	}
	mNodes[insertPos]->setData(value);
	mUsed++;
}

void HashTable::clearData() {
	for (auto& node : mNodes) {
		node->setData("");
		node->highlight(PolyNode::None);
	}
	mUsed = 0;
}

unsigned int HashTable::getID(const int& value) const {
	assert(!mNodes.empty());
	return value % mNodes.size();
}

void HashTable::clearHighlight() {
	for (auto& node : mNodes) {
		node->highlight(PolyNode::None);
	}
}

//
// Created by MINH NHUT on 8/14/2023.
//

#include "HashTable.hpp"
#include "Template/Random.hpp"

#include <fstream>
#include <iostream>

const unsigned int HashTable::MAX_SIZE = 60;
const int HashTable::PADDING = 100;
const int HashTable::MIN_VALUE = 0;
const int HashTable::MAX_VALUE = 199;
const int HashTable::WIDTH = 10;

HashTable::HashTable(const FontHolder& fonts, const ColorHolder& colors)
    : mFonts(fonts), mColors(colors), mNodes() {
	setSize(Random::getInt(MAX_SIZE - 20, MAX_SIZE));
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
	loadArray(Random::getArray(1, getSize() / 2, MIN_VALUE, MAX_VALUE));
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
	while (fileStream >> token && elements.size() < mNodes.size()) {
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
}

void HashTable::clearData() {
	for (auto& node : mNodes) {
		node->setData("");
	}
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

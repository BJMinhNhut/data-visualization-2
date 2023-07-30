//
// Created by MINH NHUT on 7/28/2023.
//

#include "Heap.hpp"
#include "Template/Random.hpp"

#include <SFML/Graphics/RenderTarget.hpp>
#include <SFML/Graphics/RenderStates.hpp>

#include <queue>
#include <fstream>
#include <iostream>

const sf::Vector2f Heap::TREE_OFF_SET(60.f, 90.f);
const unsigned int Heap::MAX_SIZE(15);

Heap::Heap(const FontHolder &fonts, const ColorHolder &colors) :
        mNodes(), mFonts(fonts), mColors(colors), height() {
    randomize();
}

void Heap::randomize() {
    std::vector<int> elements(Random::getArray(1, 15, 0, 99));
    loadArray(elements);
}

void Heap::loadFromFile(const std::string &fileDir) {
    std::ifstream fileStream(fileDir);
    std::vector<int> elements;
    while (!fileStream.eof()) {
        int value;
        fileStream >> value;
        elements.push_back(value);
    }
    loadArray(elements);
}

void Heap::loadArray(const std::vector<int> &array) {
    clear();
    for (int v: array) push(v);
}

void Heap::clear(const int &root) {
    if (mNodes.empty()) return;
    int leftNode = root * 2 + 1, rightNode = root * 2 + 2;
    if (leftNode < mNodes.size()) {
        clear(leftNode);
        mNodes[root]->detachChild(*mNodes[leftNode]);
    }
    if (rightNode < mNodes.size()) {
        clear(rightNode);
        mNodes[root]->detachChild(*mNodes[rightNode]);
    }
    if (root == 0) {
        detachChild(*mNodes[0]);
        std::vector<PolyNode *>().swap(mNodes);
        std::vector<unsigned int>().swap(height);
    }
}

void Heap::alignBinaryTree() {
    fill(height.begin(), height.end(), 0);
    for (int id = (int) mNodes.size() - 1; id > 0; --id) {
        height[parent(id)] = height[id] + 1;
        float xOffset;
        if (id % 2 == 0)
            xOffset = float(1 << height[id]) * TREE_OFF_SET.x;
        else
            xOffset = -float(1 << height[id]) * TREE_OFF_SET.x;
        mNodes[id]->setPosition(xOffset, TREE_OFF_SET.y);
    }
}

void Heap::push(const int &value) {
    if (mNodes.size() == MAX_SIZE) {
        std::cerr << "Heap maximum size reached!\n";
        return;
    }

    auto *newNode = new PolyNode(mFonts, mColors);
    newNode->setData(value);

    if (mNodes.empty())
        attachChild(PolyNode::Ptr(newNode));
    else mNodes[parent(mNodes.size())]->attachChild(PolyNode::Ptr(newNode));

    mNodes.push_back(newNode);
    height.push_back(0);
    heapifyUp((int) mNodes.size() - 1);

    alignBinaryTree();
}

int Heap::top() const {
    if (mNodes.empty()) {
        std::cerr << "Heap is empty!\n";
        return -1;
    }

    return mNodes[0]->getIntData();
}

void Heap::pop() {
    if (mNodes.empty()) {
        std::cerr << "Heap is empty!\n";
        return;
    }
    mNodes[0]->setData(mNodes.back()->getData());

    if (mNodes.size() > 1)
        mNodes[parent(mNodes.size() - 1)]->detachChild(*mNodes[mNodes.size() - 1]);
    else detachChild(*mNodes[mNodes.size() - 1]);

    mNodes.pop_back();
    height.pop_back();
    heapifyDown();

    alignBinaryTree();
}

void Heap::heapifyUp(int index) {
    assert(index < mNodes.size());
    while (index > 0) {
        int curValue = mNodes[index]->getIntData();
        int parValue = mNodes[parent(index)]->getIntData();
        if (curValue > parValue) {
            int temp = curValue;
            mNodes[index]->setData(parValue);
            mNodes[parent(index)]->setData(temp);
            index = parent(index);
        } else
            break;
    }
}

void Heap::heapifyDown() {
    int index = 0;
    while (index < mNodes.size()) {
        int leftChild = index * 2 + 1;
        int rightChild = index * 2 + 2;
        int largest = index;

        if (leftChild < mNodes.size() && mNodes[largest]->getIntData() < mNodes[leftChild]->getIntData())
            largest = leftChild;
        if (rightChild < mNodes.size() && mNodes[largest]->getIntData() < mNodes[rightChild]->getIntData())
            largest = rightChild;
        if (largest != index) {
            std::string temp = mNodes[index]->getData();
            mNodes[index]->setData(mNodes[largest]->getData());
            mNodes[largest]->setData(temp);
            index = largest;
        } else
            break;
    }
}

int Heap::parent(const int &index) {
    return (index - 1) / 2;
}
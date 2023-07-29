//
// Created by MINH NHUT on 7/28/2023.
//

#include "Heap.hpp"
#include "Template/Random.hpp"

#include <SFML/Graphics/RenderTarget.hpp>
#include <SFML/Graphics/RenderStates.hpp>

#include <queue>

const sf::Vector2f Heap::treeOffSet(60.f, 90.f);

Heap::Heap(const FontHolder &fonts, const ColorHolder &colors) :
        mNodes(), mFonts(fonts), mColors(colors), height() {
    randomize();
}

void Heap::randomize() {
    std::vector<int> elements(Random::getArray(1, 15, 0, 99));
    for (int &v: elements) insert(v);
}

void Heap::alignBinaryTree() {
    for (int id = (int) mNodes.size() - 1; id > 0; --id) {
        height[(id - 1) / 2] = height[id] + 1;
        float xOffset;
        if (id % 2 == 0)
            xOffset = float(1 << height[id]) * treeOffSet.x;
        else
            xOffset = -float(1 << height[id]) * treeOffSet.x;
        mNodes[id]->setPosition(xOffset, treeOffSet.y);
    }
}

void Heap::insert(const int &value) {
    auto *newNode = new PolyNode(mFonts, mColors);
    newNode->setData(value);

    if (mNodes.empty())
        attachChild(PolyNode::Ptr(newNode));
    else mNodes[(mNodes.size() - 1) / 2]->attachChild(PolyNode::Ptr(newNode));

    mNodes.push_back(newNode);
    height.push_back(0);
    alignBinaryTree();

    heapifyUp((int) mNodes.size() - 1);
}

void Heap::heapifyUp(int index) {
    assert(index < mNodes.size());
    while (index > 0) {
        int parent = index / 2;
        int curValue = mNodes[index]->getIntData();
        int parValue = mNodes[parent]->getIntData();
        if (curValue > parValue) {
            int temp = curValue;
            mNodes[index]->setData(parValue);
            mNodes[parent]->setData(temp);
            index = parent;
        } else
            break;
    }
}
//
// Created by MINH NHUT on 7/28/2023.
//

#include "Heap.hpp"

#include <SFML/Graphics/RenderTarget.hpp>
#include <SFML/Graphics/RenderStates.hpp>

#include <queue>

const sf::Vector2f Heap::treeOffSet(50.f, 70.f);

Heap::Heap(const FontHolder &fonts, const ColorHolder &colors) :
        mNodes(), mFonts(fonts), mColors(colors) {
}

void Heap::alignBinaryTree() {
    for (int id = (int) mNodes.size() - 1; id > 0; --id) {
        height[id / 2] = height[id] + 1;
        float xOffset = (id % 2 == 1 ? -treeOffSet.x : treeOffSet.x) * float(height[id] + 1);
        mNodes[id]->setPosition(xOffset, treeOffSet.y);
    }
}

void Heap::insert(const int &value) {
    auto *newNode = new PolyNode(mFonts, mColors);
    if (mNodes.empty())
        attachChild(PolyNode::Ptr(newNode));
    else mNodes[mNodes.size() / 2]->attachChild(PolyNode::Ptr(newNode));

    mNodes.push_back(newNode);
    height.push_back(0);
    newNode->setData(value);
    alignBinaryTree();
}
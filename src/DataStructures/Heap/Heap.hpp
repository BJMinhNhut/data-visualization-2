//
// Created by MINH NHUT on 7/28/2023.
//

#ifndef DATAVISUALIZATION2_HEAP_HPP
#define DATAVISUALIZATION2_HEAP_HPP

#include "Template/SceneNode.hpp"
#include "../PolyNode.hpp"

#include <vector>

/*
 * TODO: Heap features
 *  - [] Binary Tree style nodes alignment
 *  - [] Comparison definition
 */

class Heap : public SceneNode {
public:
    Heap(const FontHolder &, const ColorHolder &);

private:
    void insert(const int &value);

    void alignBinaryTree();

    void heapifyUp(int index);

    void heapifyDown();

private:
    static const sf::Vector2f treeOffSet;
    const ColorHolder &mColors;
    const FontHolder &mFonts;
    std::vector<PolyNode *> mNodes;
    std::vector<unsigned int> height;
};


#endif //DATAVISUALIZATION2_HEAP_HPP

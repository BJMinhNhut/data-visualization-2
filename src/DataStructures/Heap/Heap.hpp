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
 *  - [x] Binary Tree style nodes alignment
 *  - [] Comparison definition
 *  - [x] Randomize data
 *  - [] AnimationList generation
 */

class Heap : public SceneNode {
public:
    Heap(const FontHolder &, const ColorHolder &);

    void randomize();

    void loadFromFile(const std::string &fileDir);

    void push(const int &value);

private:
    void loadArray(const std::vector<int> &array);

    void clear(const int &root = 0);

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

//
// Created by MINH NHUT on 7/28/2023.
//

#ifndef DATAVISUALIZATION2_HEAP_HPP
#define DATAVISUALIZATION2_HEAP_HPP

#include "Template/SceneNode.hpp"
#include "../PolyNode.hpp"

class Heap : public SceneNode {
public:
    Heap(const FontHolder &, const ColorHolder &);

private:
    PolyNode *mNode;
};


#endif //DATAVISUALIZATION2_HEAP_HPP

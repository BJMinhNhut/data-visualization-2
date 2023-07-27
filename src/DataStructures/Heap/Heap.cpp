//
// Created by MINH NHUT on 7/28/2023.
//

#include "Heap.hpp"

#include <SFML/Graphics/RenderTarget.hpp>
#include <SFML/Graphics/RenderStates.hpp>

Heap::Heap(const FontHolder &fonts, const ColorHolder &colors) :
        mNode(new PolyNode(fonts, colors)) {
    attachChild(PolyNode::Ptr(mNode));
    mNode->setData("69");
}

//
// Created by MINH NHUT on 8/14/2023.
//

#ifndef DATAVISUALIZATION2_HASHCODE_HPP
#define DATAVISUALIZATION2_HASHCODE_HPP

#include <string>

namespace HashCode {
const std::string Insert(
    "if full, return\n"
    "id = value % size\n"
    "while (hash[id] != EMPTY)\n"
    "	id = (id+1) % size\n"
    "hash[id] = value");
}

#endif  //DATAVISUALIZATION2_HASHCODE_HPP

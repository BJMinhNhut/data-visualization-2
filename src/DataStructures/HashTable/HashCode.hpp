//
// Created by MINH NHUT on 8/14/2023.
//

#ifndef DATAVISUALIZATION2_HASHCODE_HPP
#define DATAVISUALIZATION2_HASHCODE_HPP

#include <string>

namespace HashCode {

const std::string Insert(
    "if used+1 == size, return\n"
    "id = value % size\n"
    "while (hash[id] != EMPTY)\n"
    "	id = (id+1) % size\n"
    "hash[id] = value, used++");

const std::string Search(
    "id = value % size\n"
    "while (hash[id] != EMPTY)\n"
    "	if (hash[id] == value)\n"
    "		return id\n"
    "	else id = (id+1) % size\n"
    "return NOT_FOUND");
}

#endif  //DATAVISUALIZATION2_HASHCODE_HPP

//
// Created by MINH NHUT on 8/25/2023.
//

#ifndef DATAVISUALIZATION2_CODE234_HPP
#define DATAVISUALIZATION2_CODE234_HPP

#include <string>

namespace Code234 {
const std::string Insert(
    "if this.numData == 3, split\n"
    "if isLeaf(this), this.insert(v)\n"
    "i = this.upper_bound(value)-1\n"
    "Go to this.child[i+1]");
const std::string Delete(" ");
const std::string Search(
    "if this == null, return NOT_FOUND\n"
    "i = this.upper_bound(value)-1\n"
    "if i >= 0 && value == this.data[i]\n"
    "   return FOUND\n"
    "else search(this.child[i+1])\n");
}  // namespace Code234

#endif  //DATAVISUALIZATION2_CODE234_HPP

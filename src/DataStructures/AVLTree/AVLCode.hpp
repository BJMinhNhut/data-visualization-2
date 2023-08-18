//
// Created by MINH NHUT on 8/16/2023.
//

#ifndef DATAVISUALIZATION2_AVLCODE_HPP
#define DATAVISUALIZATION2_AVLCODE_HPP

#include <string>

namespace AVLCode {
const std::string Insert(
    "Insert v\n"
    "Check balance factor (bf):\n"
    "  LL: rt_Right\n"
    "  LR: left.rt_Left, rt_Right\n"
    "  RR: rt_Left\n"
    "  RL: right.rt_Right, rt_Left");

const std::string Delete(
    "Delete v\n"
    "Check balance factor (bf):\n"
    "  LL: rt_Right\n"
    "  LR: left.rt_Left, rt_Right\n"
    "  RR: rt_Left\n"
    "  RL: right.rt_Right, rt_Left");

const std::string Search(
    "if this == null\n"
    "	return NOT_FOUND\n"
    "if this.data == value\n"
    "	return FOUND\n"
    "if value < this.data\n"
    "	searchLeft\n"
    "if value > this.data\n"
    "	searchRight");
}  // namespace AVLCode

#endif  //DATAVISUALIZATION2_AVLCODE_HPP
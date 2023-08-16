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
    "	LL case: rotateRight"
    "	LR case: rotateLeft, rotateRight\n"
    "	RR case: rotateLeft\n"
    "	RL case: rotateRight, rotateLeft");

const std::string Delete(
    "Delete v\n"
    "Check balance factor (bf):\n"
    "	LL case: rotateRight"
    "	LR case: rotateLeft, rotateRight\n"
    "	RR case: rotateLeft\n"
    "	RL case: rotateRight, rotateLeft");

const std::string Search(
    "cur = root\n"
    "while (cur != null)\n"
    "	if (cur.data == value) return FOUND\n"
    "	if (value < cur.data) cur = cur.left\n"
    "	if (value > cur.data) cur = cur.right\n"
    "return NOT_FOUND");
}  // namespace AVLCode

#endif  //DATAVISUALIZATION2_AVLCODE_HPP
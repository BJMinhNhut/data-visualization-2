//
// Created by MINH NHUT on 8/19/2023.
//

#ifndef DATAVISUALIZATION2_TRIECODE_HPP
#define DATAVISUALIZATION2_TRIECODE_HPP

#include <string>

namespace TrieCode {
const std::string Insert(
    "cur = root\n"
    "for(char c : str)\n"
    "  if cur.child[c] == null\n"
    "    cur.child[c] = new Node(c)\n"
    "  cur = cur.child[c]\n"
    "  cur.freq++\n"
    "cur.endStr = true");

const std::string Delete(
    "cur = search(str)\n"
    "cur.endStr = false\n"
    "for(char ch : rev(str))\n"
    "  cur.freq--\n"
    "  cur = cur.parent\n"
    "  if cur.child[ch].freq == 0\n"
    "    delete cur.child[ch]");

const std::string Search(
    "cur = root\n"
    "for(char c : str)\n"
    "  if cur.child[c] == null\n"
    "    return NOT_FOUND\n"
    "  cur = cur.child[c]\n"
    "if cur.endStr return FOUND\n"
    "else return NOT_FOUND");
}  // namespace TrieCode

#endif  //DATAVISUALIZATION2_TRIECODE_HPP

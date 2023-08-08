//
// Created by MINH NHUT on 8/6/2023.
//

#ifndef DATAVISUALIZATION2_HEAPCODE_HPP
#define DATAVISUALIZATION2_HEAPCODE_HPP

#include <string>

namespace HeapCode {

namespace Max {
const std::string Push(
    "i = size, size++\n"
    "A[i] = value\n"
    "while (i > 0 && A[i/2] < A[i])\n"
    "	swap(A[i/2], A[i])\n"
    "	i /= 2");
}

namespace Min {
const std::string Push(
    "i = size, size++\n"
    "A[i] = value\n"
    "while (i > 0 && A[i/2] > A[i])\n"
    "	swap(A[i/2], A[i])\n"
    "	i /= 2");
}  // namespace Min

const std::string Top("return A[0]");

const std::string Size("return size");

}  // namespace Heap

#endif  //DATAVISUALIZATION2_HEAPCODE_HPP

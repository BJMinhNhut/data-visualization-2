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
    "	swap(A[i/2], A[i]), i /= 2\n");

const std::string Delete(
    "A[i] = A[0]+1\n"
    "while (i > 0 && A[i/2] > A[i])\n"
    "	swap(A[i/2], A[i]), i /= 2\n"
    "A[0] = A[size-1]\n"
    "size--\n"
    "while (A[i] < A[Largest])\n"
    "	swap(A[i], A[Largest])\n"
    "	i = Largest");
}

namespace Min {
const std::string Push(
    "i = size, size++\n"
    "A[i] = value\n"
    "while (i > 0 && A[i/2] > A[i])\n"
    "	swap(A[i/2], A[i]), i /= 2\n");
}  // namespace Min

const std::string Top("return A[0]");

const std::string Size("return size");

}  // namespace HeapCode

#endif  //DATAVISUALIZATION2_HEAPCODE_HPP

//
// Created by MINH NHUT on 7/30/2023.
//

#ifndef DATAVISUALIZATION2_RANDOM_HPP
#define DATAVISUALIZATION2_RANDOM_HPP

#include <random>
#include <vector>

namespace Random {

    int getInt(int Min, int Max);

    std::vector<int> getArray(int minLength, int maxLength, int minVal, int maxVal);

};  // namespace Random

#endif //DATAVISUALIZATION2_RANDOM_HPP

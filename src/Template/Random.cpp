//
// Created by MINH NHUT on 7/30/2023.
//

#include "Random.hpp"

#include <algorithm>
#include <cassert>
#include <chrono>

std::mt19937 rng(std::chrono::steady_clock::now().time_since_epoch().count());

int Random::getInt(int Min, int Max) {
	assert(Min <= Max);
	return std::uniform_int_distribution<int>(Min, Max)(rng);
}

std::vector<int> Random::getArray(int minLength, int maxLength, int minVal, int maxVal) {
    std::vector<int> result(getInt(minLength, maxLength));
    for (int &v: result) v = getInt(minVal, maxVal);
    return result;
}

void Random::shuffle(std::vector<std::pair<int, int>>& list) {
	for (int i = 0; i < list.size(); ++i) {
		int x = getInt(0, (int)list.size() - 1);
		int y = getInt(0, (int)list.size() - 1);
		std::reverse(list.begin() + x, list.begin() + y);
	}
}
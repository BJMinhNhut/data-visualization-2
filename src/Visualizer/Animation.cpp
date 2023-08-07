//
// Created by MINH NHUT on 7/26/2023.
//

#include "Animation.hpp"

Animation::Animation(const std::function<void()>& forward, const std::function<void()>& backward)
    : mBackward(backward), mForward(forward) {}

void Animation::play() {
	mForward();
}

void Animation::revert() {
	mBackward();
}
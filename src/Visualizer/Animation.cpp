//
// Created by MINH NHUT on 7/26/2023.
//

#include "Animation.hpp"

Animation::Animation(const std::vector<int>& lineIDs, const std::string& description,
                     const callback& forward, const callback& backward)
    : mBackward(backward), mForward(forward), mLineIDs(lineIDs), mDescription(description) {}

void Animation::play() {
	mForward();
}

void Animation::revert() {
	mBackward();
}
const std::string& Animation::getDescription() const {
	return mDescription;
}
const std::vector<int>& Animation::getLineIDs() const {
	return mLineIDs;
}

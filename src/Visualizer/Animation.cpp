//
// Created by MINH NHUT on 7/26/2023.
//

#include "Animation.hpp"

#include <utility>

Animation::Animation(std::vector<int> lineIDs, std::string description, callback forward,
                     callback backward)
    : mBackward(std::move(backward)),
      mForward(std::move(forward)),
      mLineIDs(std::move(lineIDs)),
      mDescription(std::move(description)) {}

void Animation::play() {
	if (mForward)
		mForward();
}

void Animation::revert() {
	if (mBackward)
		mBackward();
}
const std::string& Animation::getDescription() const {
	return mDescription;
}
const std::vector<int>& Animation::getLineIDs() const {
	return mLineIDs;
}

//
// Created by MINH NHUT on 7/26/2023.
//

#include "AnimationList.hpp"

#include <iostream>

AnimationList::AnimationList(const GUI::CodeBlock::Ptr& codeblock, const GUI::Console::Ptr& console)
    : currentAnimation(0),
      mIsPlaying(false),
      mCoolDown(sf::seconds(0.f)),
      mSpeed(1.f),
      mCodeBlock(codeblock),
      mConsole(console),
      mList() {}

bool AnimationList::isFinished() const {
	return !mList.empty() && currentAnimation == mList.size();
}

unsigned int AnimationList::getProgress() const {
	return currentAnimation;
}

unsigned int AnimationList::getSize() const {
	return mList.size();
}

float AnimationList::getSpeed() const {
	return mSpeed;
}

bool AnimationList::isEmpty() const {
	return mList.empty();
}

bool AnimationList::isPlaying() const {
	return mIsPlaying;
}

void AnimationList::push(const Animation& animation) {
	mList.push_back(animation);
}

void AnimationList::play() {
	//#ifdef SFML_DEBUG
	//	std::cerr << "playing animation\n";
	//#endif
	mIsPlaying = true;
}

void AnimationList::pause() {
	mIsPlaying = false;
}

void AnimationList::clear() {
	//#ifdef SFML_DEBUG
	//	std::cerr << "clear call\n";
	//#endif
	std::vector<Animation>().swap(mList);
	currentAnimation = 0;
	mIsPlaying = false;
	mCoolDown = sf::seconds(0.f);
}

void AnimationList::play(const unsigned int& id) {
	mList[id].play();
	mCodeBlock->setHighlight(mList[id].getLineIDs());
	mConsole->log(GUI::Console::Info, mList[id].getDescription());
}

void AnimationList::playNext() {
	if (currentAnimation == mList.size())
		return;
	play(currentAnimation);
	currentAnimation++;
	resetCoolDown();
}

void AnimationList::playPrevious() {
	if (currentAnimation == 0)
		return;
	currentAnimation--;
	mList[currentAnimation].revert();

	if (currentAnimation >= 1) {
		mList[currentAnimation - 1].revert();
		play(currentAnimation - 1);
	}
	resetCoolDown();
}

void AnimationList::goToFront() {
	while (currentAnimation > 0)
		playPrevious();
	resetCoolDown();
}

void AnimationList::goToBack() {
	while (currentAnimation < mList.size())
		playNext();
	resetCoolDown();
}

void AnimationList::resetCoolDown() {
	mCoolDown = sf::seconds(0.f);
}

void AnimationList::setSpeed(const float& speed) {
	mSpeed = speed;
}

void AnimationList::update(sf::Time dt) {
	if (isPlaying()) {
		if (currentAnimation == mList.size())
			pause();
		else {
			mCoolDown += dt;
			if (mCoolDown > sf::seconds(1.f / mSpeed))
				playNext();
		}
	}
}
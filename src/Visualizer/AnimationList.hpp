//
// Created by MINH NHUT on 7/26/2023.
//

#ifndef DATAVISUALIZATION2_ANIMATIONLIST_HPP
#define DATAVISUALIZATION2_ANIMATIONLIST_HPP

#include "Animation.hpp"
#include "GUI/CodeBlock.hpp"
#include "GUI/Console.hpp"

#include <vector>

class AnimationList {
   public:
	AnimationList(const GUI::CodeBlock::Ptr& codeblock, const GUI::Console::Ptr& console);

	[[nodiscard]] bool isFinished() const;
	[[nodiscard]] unsigned int getProgress() const;
	[[nodiscard]] unsigned int getSize() const;
	[[nodiscard]] float getSpeed() const;

	[[nodiscard]] bool isEmpty() const;
	[[nodiscard]] bool isPlaying() const;

	void push(const Animation& animation);
	void clear();

	void play();
	void pause();
	void playNext();
	void playPrevious();
	void goToFront();
	void goToBack();

	void resetCoolDown();
	void setSpeed(const float& speed);

	void update(sf::Time dt);

   private:
	void play(const unsigned int& id);

   private:
	const GUI::CodeBlock::Ptr& mCodeBlock;
	const GUI::Console::Ptr& mConsole;

	sf::Time mCoolDown;
	float mSpeed;

	unsigned int currentAnimation;
	bool mIsPlaying;

	std::vector<Animation> mList;
};

#endif  //DATAVISUALIZATION2_ANIMATIONLIST_HPP

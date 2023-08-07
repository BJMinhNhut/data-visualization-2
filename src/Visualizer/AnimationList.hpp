//
// Created by MINH NHUT on 7/26/2023.
//

#ifndef DATAVISUALIZATION2_ANIMATIONLIST_HPP
#define DATAVISUALIZATION2_ANIMATIONLIST_HPP

#include "Animation.hpp"
#include "Player.hpp"

#include "SFML/System/NonCopyable.hpp"

#include <vector>

class AnimationList : public sf::NonCopyable {
   public:
	typedef std::function<void()> callback;

   public:
	AnimationList(const Player::Ptr& player);

	[[nodiscard]] bool isFinished() const;
	[[nodiscard]] unsigned int getProgress() const;
	[[nodiscard]] unsigned int getSize() const;
	[[nodiscard]] float getSpeed() const;

	[[nodiscard]] bool isEmpty() const;
	[[nodiscard]] bool isPlaying() const;

	void push(const callback& forward, const callback& backward, const std::vector<int>& highlights,
	          const std::string& description);
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
	const Player::Ptr& mPlayer;

	sf::Time mCoolDown;
	float mSpeed;

	unsigned int currentAnimation;
	bool mIsPlaying;

	std::vector<Animation> mList;
};

#endif  //DATAVISUALIZATION2_ANIMATIONLIST_HPP

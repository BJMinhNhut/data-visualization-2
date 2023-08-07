//
// Created by MINH NHUT on 7/26/2023.
//

#ifndef DATAVISUALIZATION2_ANIMATION_HPP
#define DATAVISUALIZATION2_ANIMATION_HPP

#include "SFML/Graphics.hpp"
#include "SFML/System/Time.hpp"

#include <functional>

class Animation {
   public:
	explicit Animation(const std::function<void()>& forward,
	                   const std::function<void()>& backward = nullptr);

	void play();
	void revert();

   private:
	const std::function<void()>& mForward;
	const std::function<void()>& mBackward;
};

#endif  //DATAVISUALIZATION2_ANIMATION_HPP

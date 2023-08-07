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
	typedef std::function<void()> callback;

   public:
	explicit Animation(const std::vector<int>& lineIDs, const std::string& description,
	                   const callback& forward, const callback& backward = nullptr);

	[[nodiscard]] const std::string& getDescription() const;
	[[nodiscard]] const std::vector<int>& getLineIDs() const;

	void play();
	void revert();

   private:
	const std::vector<int>& mLineIDs;
	const std::string& mDescription;
	const std::function<void()>& mForward;
	const std::function<void()>& mBackward;
};

#endif  //DATAVISUALIZATION2_ANIMATION_HPP

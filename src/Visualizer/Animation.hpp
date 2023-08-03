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
    explicit Animation(const std::function<void()> &forward);

    Animation(const std::function<void()> &forward,
              const std::function<void()> &backward);

    void play();

    void reverse();

private:
    std::function<void()> mForward;
    std::function<void()> mBackward;
};


#endif //DATAVISUALIZATION2_ANIMATION_HPP

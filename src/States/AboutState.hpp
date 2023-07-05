//
// Created by MINH NHUT on 7/4/2023.
//

#ifndef DATAVISUALIZATION2_ABOUTSTATE_HPP
#define DATAVISUALIZATION2_ABOUTSTATE_HPP

#include "GUI/Container.hpp"
#include "Template/State.hpp"

#include <SFML/Graphics/Sprite.hpp>

namespace About {
    static const std::string content = {
            "Author: Nhut Dang - HCMUS - 22APCS1 - 2212571.\n"
            "\n"
            "This is a CS163 Solo Lab Project using C++. The application\n"
            "provides an intuitive and user-friendly interface for the display\n"
            "and understanding advanced data structures such as trees and\n"
            "graphs.\n"
            "\n"
            "The app uses SFML library for graphic display and portable-file-\n"
            "dialogs library for file dialog calling.\n"
            "\n"
            "The development for this app is from Jun 24, 2023."};
}
class AboutState : public State {
public:
public:
    explicit AboutState(StateStack &stack, Context context);

    virtual void draw();

    virtual bool update(sf::Time dt);

    virtual bool handleEvent(const sf::Event &event);

private:
    GUI::Container mGUIContainer;
    sf::Sprite mBackgroundSprite;
};

#endif //DATAVISUALIZATION2_ABOUTSTATE_HPP

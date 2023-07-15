//
// Created by MINH NHUT on 7/15/2023.
//

#ifndef DATAVISUALIZATION2_DATASTATE_HPP
#define DATAVISUALIZATION2_DATASTATE_HPP

#include "GUI/Container.hpp"
#include "Template/State.hpp"

#include <SFML/Graphics/Sprite.hpp>

class DataState : public State {
public:
    DataState(StateStack &stack, Context context);

    virtual void draw();

    virtual bool update(sf::Time dt);

    virtual bool handleEvent(const sf::Event &event);

private:
    GUI::Container mGUIContainer;
    sf::Sprite mBackgroundSprite;
};


#endif //DATAVISUALIZATION2_DATASTATE_HPP

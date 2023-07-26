//
// Created by MINH NHUT on 7/4/2023.
//

#ifndef DATAVISUALIZATION2_SETTINGSSTATE_HPP
#define DATAVISUALIZATION2_SETTINGSSTATE_HPP

#include "GUI/Container.hpp"
#include "Template/Settings.hpp"
#include "Template/State.hpp"

#include <SFML/Graphics/Sprite.hpp>

class SettingsState : public State {
public:
    SettingsState(StateStack &stack, Context context);

    virtual void draw();

    virtual bool update(sf::Time dt);

    virtual bool handleEvent(const sf::Event &event);

private:
    GUI::Container themeContainer;
    GUI::Container mGUIContainer;
    sf::Sprite mBackgroundSprite;
    Settings mSettings;
};


#endif //DATAVISUALIZATION2_SETTINGSSTATE_HPP

//
// Created by MINH NHUT on 6/27/2023.
//

#ifndef DATAVISUALIZATION2_CONSTANTS_HPP
#define DATAVISUALIZATION2_CONSTANTS_HPP

#include <SFML/Graphics/Color.hpp>
#include <SFML/System/Time.hpp>

#include <string>
#include <vector>

namespace Constants {
// Math
float const PI = 3.14159265;

// Color
sf::Color const mBlack(66, 66, 66);
sf::Color const BlueDark(13, 71, 161);
sf::Color const WhiteDisplay(255, 255, 255);
sf::Color const WhiteUI(245, 245, 245);
sf::Color const GrayBorder(189, 189, 189);
sf::Color const YellowLight(255, 245, 157);
sf::Color const OrangeLight(239, 108, 0);
sf::Color const RedDark(183, 28, 28);

sf::Color const BlackUI(69, 90, 100);
sf::Color const BlackDisplay(55, 71, 79);
sf::Color const RedLight(229, 115, 115);
sf::Color const BlueLight(100, 181, 246);
sf::Color const TealDark(0, 96, 100);
sf::Color const TealLight(0, 137, 123);
sf::Color const BlueGrayBorder(81, 105, 117);

// Resource links
std::vector<std::string> const imageNames = {
    "background.png",
    "title.png",
    "checkbox-normal.png",
    "checkbox-selected.png",
    "checkbox-activated.png",
    "home-normal.png",
    "home-selected.png",
    "back-normal.png",
    "back-selected.png",
    "title-bar.png",
    "command-normal.png",
    "command-selected.png",
    "command-activated.png",
    "play-normal.png",
    "play-selected.png",
    "pause-normal.png",
    "pause-selected.png",
    "replay-normal.png",
    "replay-selected.png",
    "small-arrow-normal.png",
    "small-arrow-selected.png",
    "arrow-normal.png",
    "arrow-selected.png",
    "double-arrow-normal.png",
    "double-arrow-selected.png",
    "input-normal.png",
    "input-selected.png",
    "input-activated.png",
    "button-small-normal.png",
    "button-small-selected.png",
    "button-big-normal.png",
    "button-big-selected.png",
    "menu-hash-normal.png",
    "menu-hash-selected.png",
    "menu-avl-normal.png",
    "menu-avl-selected.png",
    "menu-234-normal.png",
    "menu-234-selected.png",
    "menu-minheap-normal.png",
    "menu-minheap-selected.png",
    "menu-maxheap-normal.png",
    "menu-maxheap-selected.png",
    "menu-trie-normal.png",
    "menu-trie-selected.png",
    "menu-graph-normal.png",
    "menu-graph-selected.png",
};

#ifdef SFML_DEBUG
const std::string dataPrefix = "../";
#else
const std::string dataPrefix = "";
#endif
}  // namespace Constants

#endif  //DATAVISUALIZATION2_CONSTANTS_HPP

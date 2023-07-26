//
// Created by MINH NHUT on 6/27/2023.
//

#ifndef DATAVISUALIZATION2_UTILITY_HPP
#define DATAVISUALIZATION2_UTILITY_HPP

#include "ResourceIdentifiers.hpp"
#include "ColorHolder.hpp"

#include <SFML/Graphics/ConvexShape.hpp>
#include <SFML/Graphics/RectangleShape.hpp>
#include <SFML/Graphics/Sprite.hpp>
#include <SFML/Graphics/Text.hpp>

namespace sf {
    class Sprite;

    class Text;
}  // namespace sf

namespace Utility {
    void centerOrigin(sf::Sprite &sprite);

    void centerOrigin(sf::Text &text);

    void centerOrigin(sf::Shape &rect);

    sf::RectangleShape getLineShape(sf::Vector2f line,
                                    float thickness = 1.f);

    std::vector<int> loadArrayFromString(std::string text);

    std::vector<int> loadArrayFromFile(const std::string &filename);

    void loadImages(TextureHolder &textures, const std::string &prefix);

    void loadLightTheme(TextureHolder &textures, ColorHolder &colors);

    void loadDarkTheme(TextureHolder &textures, ColorHolder &colors);
}

#endif //DATAVISUALIZATION2_UTILITY_HPP

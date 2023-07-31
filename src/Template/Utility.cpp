//
// Created by MINH NHUT on 6/27/2023.
//

#include "Utility.hpp"
#include "Constants.hpp"
#include "ResourceHolder.hpp"

#include <cmath>
#include <iostream>

namespace Utility {
    void centerOrigin(sf::Sprite &sprite) {
        sf::FloatRect bounds = sprite.getLocalBounds();
        sprite.setOrigin(std::floor(bounds.left + bounds.width / 2.f),
                         std::floor(bounds.top + bounds.height / 2.f));
    }

    void centerOrigin(sf::Text &text) {
        sf::FloatRect bounds = text.getLocalBounds();
        text.setOrigin(std::floor(bounds.left + bounds.width / 2.f),
                       std::floor(bounds.top + bounds.height / 2.f));
    }

    void centerOrigin(sf::Shape &shape) {
        sf::FloatRect bounds = shape.getLocalBounds();
        shape.setOrigin(std::floor(bounds.left + bounds.width / 2.f),
                        std::floor(bounds.top + bounds.height / 2.f));
    }

    void loadImages(TextureHolder &textures, const std::string &prefix) {
        for (int id = 0; id < Textures::NumTextures; ++id) {
            std::string imagePaths = Constants::dataPrefix + "resources/images/" + (prefix + Constants::imageNames[id]);
            std::cerr << "Loading: " << imagePaths << '\n';
            textures.load(static_cast<Textures::ID>(id), imagePaths);
            std::cerr << "OK\n";
        }
    }

    void loadLightTheme(TextureHolder &textures, ColorHolder &colors) {
        loadImages(textures, "");

        colors.load(Colors::Text, Constants::mBlack);
        colors.load(Colors::UIPrimary, Constants::WhiteUI);
        colors.load(Colors::UISecondary, Constants::WhiteDisplay);
        colors.load(Colors::UIBorder, Constants::GrayBorder);
        colors.load(Colors::Highlight, Constants::YellowLight);
        colors.load(Colors::Red, Constants::RedDark);
        colors.load(Colors::Blue, Constants::BlueDark);
    }

    void loadDarkTheme(TextureHolder &textures, ColorHolder &colors) {
        loadImages(textures, "dark/");

        colors.load(Colors::Text, sf::Color::White);
        colors.load(Colors::UIPrimary, Constants::BlackUI);
        colors.load(Colors::UISecondary, Constants::BlackDisplay);
        colors.load(Colors::UIBorder, Constants::BlueGrayBorder);
        colors.load(Colors::Highlight, Constants::TealDark);
        colors.load(Colors::Red, Constants::RedLight);
        colors.load(Colors::Blue, Constants::BlueLight);
    }

    bool isInt(const std::string &data) {
        if (data.empty()) return false;
        for (int i = 0; i < data.length(); ++i) {
            if (!std::isdigit(data[i])) return i > 9;
        }
        return true;
    }
}



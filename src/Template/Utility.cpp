//
// Created by MINH NHUT on 6/27/2023.
//

#include "Utility.hpp"
#include "Constants.hpp"
#include "ResourceHolder.hpp"

#include <cmath>
#include <fstream>
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

    sf::RectangleShape getLineShape(sf::Vector2f line, float thickness) {
        float lineLength = sqrt(line.x * line.x + line.y * line.y);
        sf::RectangleShape rect(sf::Vector2f(lineLength, thickness));
        sf::FloatRect bounds = rect.getLocalBounds();
        rect.setOrigin(0, std::floor(bounds.top + bounds.height / 2.f));

        float angle = atan2(line.y, line.x) / Constants::PI * 180.f;
        rect.rotate(angle);
        return rect;
    }

    std::vector<int> loadArrayFromString(std::string text) {
        std::vector<int> mArray(0);
        if (text.empty())
            return mArray;

        int currentValue = 0;
        text.push_back(',');

        for (char mChar: text) {
            if (mChar == ',') {
                mArray.push_back(currentValue);
                currentValue = 0;
            } else if (std::isdigit(mChar)) {
                currentValue =
                        currentValue * 10 + static_cast<int>(mChar - '0');
                if (currentValue > Constants::NODE_MAXVALUE) {
                    mArray.push_back(currentValue / 10);
                    currentValue %= 10;
                }
            }

            if (mArray.size() == Constants::LIST_MAXSIZE)
                break;
        }
        return mArray;
    }

    std::vector<int> loadArrayFromFile(const std::string &filename) {
        std::ifstream mFile(filename, std::ios::in);
        std::vector<int> mArray(0);
        while (!mFile.eof() && mArray.size() < Constants::LIST_MAXSIZE) {
            std::string line;
            getline(mFile, line);
            std::vector<int> currentArray(loadArrayFromString(line));
            mArray.insert(mArray.end(), currentArray.begin(),
                          currentArray.end());
        }
        mArray.resize(
                std::min((int) mArray.size(), Constants::LIST_MAXSIZE));
        mFile.close();
        return mArray;
    }

    void loadImages(TextureHolder &textures, const std::string &prefix) {
        for (int id = 0; id < Textures::NumTextures; ++id) {
            std::string imagePaths = Constants::dataPrefix + "resources/images/" + (prefix + Constants::imageNames[id]);
            std::cerr << "Loaded: " << imagePaths << '\n';
            textures.load(static_cast<Textures::ID>(id), imagePaths);
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
}



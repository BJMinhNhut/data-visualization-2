//
// Created by MINH NHUT on 8/1/2023.
//

#include "CodeBlock.hpp"

#include <SFML/Graphics/RenderStates.hpp>
#include <SFML/Graphics/RenderTarget.hpp>

#include <iostream>

namespace GUI {
    CodeBlock::CodeBlock(const FontHolder &fonts,
                         const ColorHolder &colors)
    : mText("", fonts.get(Fonts::Mono), 16u),
      mHighlight(),
              mLinePositions(),
              highlightList(),
              highlightColor(colors.get(Colors::Highlight)) {
        mText.setFillColor(colors.get(Colors::Text));
        mText.setPosition(15.f, 10.f);
        mText.setLineSpacing(1.5f);
    }

    void CodeBlock::loadCode(const std::string &code) {
        if (code == mText.getString())
            return;
        mText.setString(code);
        getLinePosition();
        getHighLightRectangle();
    }

    void CodeBlock::setHighlight(const std::vector<int> &lineID) {
        std::vector<int>().swap(highlightList);
        for (int id: lineID) {
            if (id < 0 || id >= mLinePositions.size())
                continue;
            highlightList.emplace_back(id);
        }
    }

    bool CodeBlock::isSelectable() const {
        return false;
    }

    void CodeBlock::handleEvent(const sf::Event &event) {}

    void CodeBlock::draw(sf::RenderTarget &target,
                         sf::RenderStates states) const {
        states.transform *= getTransform();
        for (auto &id: highlightList)
            target.draw(mHighlight[id], states);
        target.draw(mText, states);
    }

    void CodeBlock::getLinePosition() {
        std::vector<sf::Vector2f>().swap(mLinePositions);
        std::string text = mText.getString();
        for (int i = 0; i < text.size(); ++i)
            if (i == 0 || text[i - 1] == '\n') {
                mLinePositions.emplace_back(0.f, mText.findCharacterPos(i).y);
            }
    }

    void CodeBlock::getHighLightRectangle() {
	    mHighlight.resize(mLinePositions.size());
	    for (int id = 0; id < mLinePositions.size(); ++id) {
            mHighlight[id] = sf::RectangleShape(sf::Vector2f(350.f, 20.f));
		    mHighlight[id].setPosition(mLinePositions[id]);
            mHighlight[id].setFillColor(highlightColor);
        }
    }

}  // namespace GUI
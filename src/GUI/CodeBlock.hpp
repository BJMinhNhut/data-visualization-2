//
// Created by MINH NHUT on 8/1/2023.
//

#ifndef DATAVISUALIZATION2_CODEBLOCK_HPP
#define DATAVISUALIZATION2_CODEBLOCK_HPP


#include "Component.hpp"
#include "Template/ColorHolder.hpp"
#include "Template/ResourceHolder.hpp"
#include "Template/ResourceIdentifiers.hpp"

#include <SFML/Graphics/RectangleShape.hpp>
#include <SFML/Graphics/Text.hpp>

#include <string>
#include <vector>

namespace GUI {
    class CodeBlock : public Component {
    public:
        typedef std::shared_ptr<CodeBlock> Ptr;

    public:
        CodeBlock(const FontHolder &fonts, const ColorHolder &colors);

        void loadCode(const std::string &code);

        void setHighlight(const std::vector<int> &lineID);

        bool isSelectable() const override;

        void handleEvent(const sf::Event &event) override;

    private:
        void draw(sf::RenderTarget &target,
                  sf::RenderStates states) const override;

        void getLinePosition();

        void getHighLightRectangle();

    private:
        std::vector<sf::Vector2f> mLinePositions;
        std::vector<sf::RectangleShape> mHighlight;
        std::vector<int> highlightList;
        sf::Text mText;
        const sf::Color highlightColor;
    };
}  // namespace GUI


#endif //DATAVISUALIZATION2_CODEBLOCK_HPP

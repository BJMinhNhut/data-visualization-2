//
// Created by MINH NHUT on 7/4/2023.
//

#ifndef DATAVISUALIZATION2_LABEL_HPP
#define DATAVISUALIZATION2_LABEL_HPP

#include "GUI/Component.hpp"
#include "Template/ColorHolder.hpp"
#include "Template/ResourceHolder.hpp"
#include "Template/ResourceIdentifiers.hpp"

#include <SFML/Graphics/Color.hpp>
#include <SFML/Graphics/Text.hpp>

namespace GUI {

    class Label : public Component {
    public:
        enum Type {
            Main,
            Bold,
            Mono,
        };

    public:
        typedef std::shared_ptr<Label> Ptr;

    public:
        Label(Type type, const std::string &text, const FontHolder &fonts,
              const ColorHolder &colors);

        virtual bool isSelectable() const;

        void setText(const std::string &text);

        void setColor(const sf::Color &color);

        void alignCenter();

        virtual void handleEvent(const sf::Event &event);

    private:
        static Fonts::ID getFontID(Type type);

        void draw(sf::RenderTarget &target,
                  sf::RenderStates states) const;

    private:
        sf::Text mText;
    };

}  // namespace GUI

#endif //DATAVISUALIZATION2_LABEL_HPP

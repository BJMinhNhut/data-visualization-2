//
// Created by MINH NHUT on 7/27/2023.
//

#ifndef DATAVISUALIZATION2_CIRCLENODE_HPP
#define DATAVISUALIZATION2_CIRCLENODE_HPP

#include "Template/SceneNode.hpp"
#include "Template/ColorHolder.hpp"
#include "Template/ResourceIdentifiers.hpp"

#include <SFML/Graphics/CircleShape.hpp>
#include <SFML/Graphics/Text.hpp>

/*
 * TODO: Circle Node implementation
 *  - [x] Value display, with circle
 *  - [] Adjacent list, pointer to edges
 *  - [] When object moves, update the corresponding edge
 */

class CircleNode : public SceneNode {
public:
    explicit CircleNode(const FontHolder &fonts,
                        const ColorHolder &colors);

    [[nodiscard]] int getValue() const;

    void setValue(const int &value);

    void setCircle(const sf::CircleShape &circle);

private:
    virtual void updateCurrent(sf::Time dt);

    virtual void drawCurrent(sf::RenderTarget &target,
                             sf::RenderStates states) const;

private:
    int mValue;
    sf::Text mText;
    sf::CircleShape mCircle;
};


#endif //DATAVISUALIZATION2_CIRCLENODE_HPP

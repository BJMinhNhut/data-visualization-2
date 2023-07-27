//
// Created by MINH NHUT on 7/27/2023.
//

#ifndef DATAVISUALIZATION2_POLYNODE_HPP
#define DATAVISUALIZATION2_POLYNODE_HPP

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

class PolyNode : public SceneNode {
public:
    explicit PolyNode(const FontHolder &fonts,
                      const ColorHolder &colors);

    [[nodiscard]] std::string getData() const;

    [[nodiscard]] int getIntData() const;

    void setData(const std::string &);

    void setPoint(const int &);

private:
    void updateCurrent(sf::Time dt) override;

    void drawCurrent(sf::RenderTarget &target,
                     sf::RenderStates states) const override;

private:
    sf::Text mText;
    sf::CircleShape mPolygon;
};


#endif //DATAVISUALIZATION2_POLYNODE_HPP
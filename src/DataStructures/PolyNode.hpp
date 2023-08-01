//
// Created by MINH NHUT on 7/27/2023.
//

#ifndef DATAVISUALIZATION2_POLYNODE_HPP
#define DATAVISUALIZATION2_POLYNODE_HPP

#include "Template/SceneNode.hpp"
#include "Template/ColorHolder.hpp"
#include "Template/ResourceIdentifiers.hpp"
#include "Edge.hpp"

#include <SFML/Graphics/CircleShape.hpp>
#include <SFML/Graphics/RectangleShape.hpp>
#include <SFML/Graphics/Text.hpp>

class PolyNode : public SceneNode {
public:
    explicit PolyNode(const FontHolder &fonts,
                      const ColorHolder &colors);

    [[nodiscard]] std::string getData() const;

    [[nodiscard]] int getIntData() const;

    void setData(const std::string &data);

    void setData(const int &data);

    void setPoint(const int &points);

    void addEdgeOut(PolyNode *to);

    void addEdgeIn(Edge *edge);

    void removeEdgeOut(PolyNode *to);

    void removeEdgeIn(Edge *edge);

    void setPosition(float x, float y);

private:
    void updateCurrent(sf::Time dt) override;

    void drawCurrent(sf::RenderTarget &target,
                     sf::RenderStates states) const override;

private:
    sf::Text mText;
    sf::CircleShape mPolygon;
    std::vector<Edge *> inEdges;
    std::vector<std::unique_ptr<Edge>> outEdges;
    const ColorHolder &mColors;
};


#endif //DATAVISUALIZATION2_POLYNODE_HPP

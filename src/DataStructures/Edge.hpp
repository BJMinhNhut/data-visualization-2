//
// Created by MINH NHUT on 7/31/2023.
//

#ifndef DATAVISUALIZATION2_EDGE_HPP
#define DATAVISUALIZATION2_EDGE_HPP

#include "Template/SceneNode.hpp"

#include <SFML/Graphics/RectangleShape.hpp>

class PolyNode;

class Edge : public SceneNode {
public:
    enum EdgeType {
        Hidden,
        Directed,
        Undirected,
    };

public:
    Edge(PolyNode *from, PolyNode *to, EdgeType type, const sf::Color &color);

    void callUpdate();

    [[nodiscard]] PolyNode *getTo() const;

    [[nodiscard]] PolyNode *getFrom() const;

private:
    void updateCurrent(sf::Time dt) override;

    void drawCurrent(sf::RenderTarget &target,
                     sf::RenderStates states) const override;

    static sf::RectangleShape getLineShape(sf::Vector2f line);

private:
    static const float THICKNESS;
    PolyNode *mFrom, *mTo;
    sf::RectangleShape mLine;
    EdgeType mType;
    bool mUpdate;
};

#endif //DATAVISUALIZATION2_EDGE_HPP

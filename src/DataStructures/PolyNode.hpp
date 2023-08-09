//
// Created by MINH NHUT on 7/27/2023.
//

#ifndef DATAVISUALIZATION2_POLYNODE_HPP
#define DATAVISUALIZATION2_POLYNODE_HPP

#include "Edge.hpp"
#include "Template/ColorHolder.hpp"
#include "Template/ResourceIdentifiers.hpp"
#include "Template/SceneNode.hpp"

#include <SFML/Graphics/CircleShape.hpp>
#include <SFML/Graphics/RectangleShape.hpp>
#include <SFML/Graphics/Text.hpp>

class PolyNode : public SceneNode {
   public:
	enum Highlight {
		None,
		Primary,
		Secondary,
	};

   public:
	explicit PolyNode(const FontHolder& fonts, const ColorHolder& colors);

	[[nodiscard]] std::string getData() const;
	[[nodiscard]] int getIntData() const;

	void setData(const std::string& data);
	void setData(const int& data);
	void swapData(PolyNode* node);
	void setPoint(const int& points);
	void highlight(Highlight type);

	void addEdgeOut(PolyNode* to);
	void addEdgeIn(const Edge::Ptr& edge);
	void removeEdgeOut(PolyNode* to);
	void removeEdgeIn(const Edge::Ptr& edge);
	void removeAllEdges();

	void setPosition(float pX, float pY) override;
	void setPosition(sf::Vector2f position) override;

   private:
	void updateCurrent(sf::Time dt) override;

	void drawCurrent(sf::RenderTarget& target, sf::RenderStates states) const override;

   private:
	sf::Text mText;
	sf::CircleShape mPolygon;
	std::vector<Edge::Ptr> inEdges, outEdges;
	const ColorHolder& mColors;
};

#endif  //DATAVISUALIZATION2_POLYNODE_HPP

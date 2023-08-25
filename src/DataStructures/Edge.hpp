//
// Created by MINH NHUT on 7/31/2023.
//

#ifndef DATAVISUALIZATION2_EDGE_HPP
#define DATAVISUALIZATION2_EDGE_HPP

#include "Template/ColorHolder.hpp"
#include "Template/ResourceIdentifiers.hpp"
#include "Template/SceneNode.hpp"

#include <SFML/Graphics/ConvexShape.hpp>
#include <SFML/Graphics/Drawable.hpp>
#include <SFML/Graphics/RectangleShape.hpp>
#include <SFML/Graphics/Text.hpp>
#include <SFML/Graphics/Transformable.hpp>
#include <SFML/System/NonCopyable.hpp>

class PolyNode;

class Edge : public sf::Transformable, public sf::Drawable, private sf::NonCopyable {
   public:
	typedef std::shared_ptr<Edge> Ptr;
	enum EdgeType {
		Hidden = 1 << 0,
		Directed = 1 << 1,
		Weighted = 1 << 2,
	};

   public:
	Edge(PolyNode* from, PolyNode* to, int type, const FontHolder& fonts,
	     const ColorHolder& colors);

	void callUpdate();

	void setColor(Colors::ID color);
	void setType(int type);
	void setWeight(int weight);

	[[nodiscard]] PolyNode* getTo() const;
	[[nodiscard]] PolyNode* getFrom() const;

	void update(sf::Time dt);

   private:
	void draw(sf::RenderTarget& target, sf::RenderStates states) const override;

	sf::RectangleShape getLineShape(sf::Vector2f line);
	sf::ConvexShape getArrowShape(sf::Vector2f line);
	sf::Vector2f getWeightPosition();

   private:
	static const float THICKNESS;
	const ColorHolder& mColors;
	const FontHolder& mFonts;
	PolyNode *mFrom, *mTo;
	sf::Text mText;

	sf::RectangleShape mLine;
	sf::ConvexShape mArrow;
	int mType;
	bool mUpdate;
};

#endif  //DATAVISUALIZATION2_EDGE_HPP

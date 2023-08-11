//
// Created by MINH NHUT on 7/31/2023.
//

#ifndef DATAVISUALIZATION2_EDGE_HPP
#define DATAVISUALIZATION2_EDGE_HPP

#include "Template/ColorHolder.hpp"
#include "Template/SceneNode.hpp"

#include <SFML/Graphics/Drawable.hpp>
#include <SFML/Graphics/RectangleShape.hpp>
#include <SFML/Graphics/Transformable.hpp>
#include "SFML/System/NonCopyable.hpp"

class PolyNode;

class Edge : public sf::Transformable, public sf::Drawable, private sf::NonCopyable {
   public:
	typedef std::shared_ptr<Edge> Ptr;
	enum EdgeType {
		Hidden,
		Directed,
		Undirected,
	};

   public:
	Edge(PolyNode* from, PolyNode* to, EdgeType type, const ColorHolder& colors);

	void callUpdate();

	[[nodiscard]] PolyNode* getTo() const;

	[[nodiscard]] PolyNode* getFrom() const;

	void update(sf::Time dt);

   private:
	void draw(sf::RenderTarget& target, sf::RenderStates states) const override;

	static sf::RectangleShape getLineShape(sf::Vector2f line);

   private:
	static const float THICKNESS;
	const ColorHolder& mColors;
	PolyNode *mFrom, *mTo;
	sf::RectangleShape mLine;
	EdgeType mType;
	bool mUpdate;
};

#endif  //DATAVISUALIZATION2_EDGE_HPP

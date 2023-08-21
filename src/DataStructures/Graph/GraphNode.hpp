//
// Created by MINH NHUT on 8/20/2023.
//

#ifndef DATAVISUALIZATION2_GRAPHNODE_HPP
#define DATAVISUALIZATION2_GRAPHNODE_HPP

#include "../PolyNode.hpp"

class GraphNode : public PolyNode {
   public:
	typedef std::unique_ptr<GraphNode> Ptr;
	static const float REPULSE;
	static const float ATTRACT;
	static const float LENGTH_LIMIT;

   public:
	GraphNode(const FontHolder& fonts, const ColorHolder& colors);
	void setVelocity(sf::Vector2f velocity);

	void makeAdjacent(GraphNode* node);

	sf::Vector2f getRepulsion(const GraphNode& node) const;
	bool isAdjacent(const GraphNode& node) const;
	sf::Vector2f getTotalAttraction() const;
	sf::Vector2f getAttraction(const GraphNode& node) const;

   private:
	void updateCurrent(sf::Time dt) override;

   private:
	std::vector<GraphNode*> mAdj;
	sf::Vector2f mVelocity;
};

#endif  //DATAVISUALIZATION2_GRAPHNODE_HPP

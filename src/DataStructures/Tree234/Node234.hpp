//
// Created by MINH NHUT on 8/23/2023.
//

#ifndef DATAVISUALIZATION2_NODE234_HPP
#define DATAVISUALIZATION2_NODE234_HPP

#include "../PolyNode.hpp"
#include "Template/SceneNode.hpp"

class Node234 : public SceneNode {
   public:
	static const int MAX_DATA;
	static const int MAX_CHILD;
	static const int MIN_VALUE;
	static const int MAX_VALUE;
	static const float NODE_RADIUS;

   public:
	Node234(const FontHolder& fonts, const ColorHolder& colors);

	void insert(int value);

   private:
	void align();

	//	void drawCurrent(sf::RenderTarget& target, sf::RenderStates states) const override;

   private:
	const FontHolder& mFonts;
	const ColorHolder& mColors;

	std::vector<Node234> mChildren;
	std::vector<PolyNode*> mData;
};

#endif  //DATAVISUALIZATION2_NODE234_HPP

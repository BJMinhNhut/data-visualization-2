//
// Created by MINH NHUT on 8/23/2023.
//

#ifndef DATAVISUALIZATION2_TREE234_HPP
#define DATAVISUALIZATION2_TREE234_HPP

#include "Node234.hpp"
#include "Template/SceneNode.hpp"

class Tree234 : public SceneNode {
   public:
	static const int MAX_SIZE;

   public:
	Tree234(const FontHolder& fonts, const ColorHolder& colors);
	void insert(const int& value);

   private:
	Node234* insertBST(const int& value);

   private:
	const ColorHolder& mColors;
	const FontHolder& mFonts;

	Node234* mRoot;
};

#endif  //DATAVISUALIZATION2_TREE234_HPP

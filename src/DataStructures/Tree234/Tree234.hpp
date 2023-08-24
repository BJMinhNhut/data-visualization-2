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
	void clear();
	void loadFromFile(const std::string& fileDir);
	void randomize();

	int getSize() const;

   private:
	Node234* split(Node234* node);  // split the node, return the root of the split node
	void align();
	void clear(Node234* node);
	//	void clearHighlight(AVLNode* root);
	void loadArray(const std::vector<int>& array);

   private:
	const ColorHolder& mColors;
	const FontHolder& mFonts;

	Node234* mRoot;
};

#endif  //DATAVISUALIZATION2_TREE234_HPP

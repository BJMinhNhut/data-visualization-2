//
// Created by MINH NHUT on 8/15/2023.
//

#ifndef DATAVISUALIZATION2_AVLTREE_HPP
#define DATAVISUALIZATION2_AVLTREE_HPP

#include "AVLNode.hpp"

class AVLTree : public SceneNode {
   public:
	static const int MAX_SIZE;
	static const int MIN_VALUE;
	static const int MAX_VALUE;
	static const sf::Vector2f TREE_OFF_SET;

   public:
	AVLTree(const FontHolder& fonts, const ColorHolder& colors);

	void insert(const int& value);

   private:
	void loadArray(const std::vector<int>& array);

	AVLNode* pureInsert(AVLNode* root, const int& value);
	void alignAsTree();
	std::vector<AVLNode*> getInOrder(AVLNode* root);

   private:
	const ColorHolder& mColors;
	const FontHolder& mFonts;

	AVLNode* mRoot;
};

#endif  //DATAVISUALIZATION2_AVLTREE_HPP

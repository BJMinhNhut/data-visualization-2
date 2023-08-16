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

	void randomize();
	void loadFromFile(const std::string& fileDir);
	void insert(const int& value);
	void rotateLeft();
	void rotateRight();

   private:
	void clear(AVLNode* root);
	void loadArray(std::vector<int> array);

	AVLNode* create(const std::vector<int>& array, int left, int right);
	AVLNode* rotateLeft(AVLNode* root);
	AVLNode* rotateRight(AVLNode* root);
	AVLNode* pureInsert(AVLNode* root, const int& value);

	void alignAsTree();
	std::vector<AVLNode*> getInOrder(AVLNode* root);
	void calculateDepth();
	void calculateDepth(AVLNode* root);

   private:
	const ColorHolder& mColors;
	const FontHolder& mFonts;

	AVLNode* mRoot;
};

#endif  //DATAVISUALIZATION2_AVLTREE_HPP

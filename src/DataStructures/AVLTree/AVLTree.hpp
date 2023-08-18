//
// Created by MINH NHUT on 8/15/2023.
//

#ifndef DATAVISUALIZATION2_AVLTREE_HPP
#define DATAVISUALIZATION2_AVLTREE_HPP

#include "AVLNode.hpp"
#include "Visualizer/Animation.hpp"

class AVLTree : public SceneNode {
   public:
	static const int MAX_SIZE;
	static const int MIN_VALUE;
	static const int MAX_VALUE;
	static const sf::Vector2f TREE_OFF_SET;

   public:
	AVLTree(const FontHolder& fonts, const ColorHolder& colors);

	unsigned int getSize() const;
	int getRandomElement() const;

	std::pair<std::vector<Animation>, std::string> searchAnimation(const int& value);
	std::pair<std::vector<Animation>, std::string> insertAnimation(const int& value);
	std::pair<std::vector<Animation>, std::string> deleteAnimation(const int& value);
	AVLNode* rotateRightAnimation(AVLNode* node, std::vector<Animation>& list);
	AVLNode* rotateLeftAnimation(AVLNode* node, std::vector<Animation>& list);
	AVLNode* rotateLRAnimation(AVLNode* node, std::vector<Animation>& list);
	AVLNode* rotateRLAnimation(AVLNode* node, std::vector<Animation>& list);

	void clear();
	void randomize();
	void loadFromFile(const std::string& fileDir);
	void clearHighlight();
	void insert(const int& value);

#ifdef SFML_DEBUG
	void rotateLeft();
	void rotateRight();
#endif

   private:
	AVLNode* traverseToLeafAnimation(const int& value, std::vector<Animation>& list);
	AVLNode* traverseSearchingAnimation(const int& value, std::vector<Animation>& list);
	AVLNode* deleteNodeAnimation(AVLNode* node, std::vector<Animation>& list);
	void balanceAnimation(AVLNode* node, std::vector<Animation>& list);

	void dump(AVLNode* node, Transition type = Smooth);
	void clear(AVLNode* root);
	void clearHighlight(AVLNode* root);
	void loadArray(std::vector<int> array);

	AVLNode* create(const std::vector<int>& array, int left, int right);
	void rotateLeft(AVLNode* root);
	void rotateRight(AVLNode* root);
	AVLNode* pureInsert(AVLNode* root, const int& value);

	void alignAsTree();
	std::vector<AVLNode*> getInOrder(AVLNode* root) const;
	void calculateDepth();
	void calculateDepth(AVLNode* root);

	void updateCurrent(sf::Time dt) override;

   private:
	const ColorHolder& mColors;
	const FontHolder& mFonts;

	AVLNode *mRoot, *mBin;
	std::vector<AVLNode*> mInOrder;
};

#endif  //DATAVISUALIZATION2_AVLTREE_HPP

//
// Created by MINH NHUT on 8/15/2023.
//

#ifndef DATAVISUALIZATION2_AVLNODE_HPP
#define DATAVISUALIZATION2_AVLNODE_HPP

#include "../PolyNode.hpp"

class AVLNode : public PolyNode {
   public:
	typedef std::unique_ptr<AVLNode> Ptr;
	enum BalanceStatus {
		Balanced,
		LeftLeft,
		LeftRight,
		RightRight,
		RightLeft,
	};

   public:
	AVLNode(const FontHolder& fonts, const ColorHolder& colors);

	void attachLeft(AVLNode* node);
	void attachRight(AVLNode* node);
	void detachLeft();
	void detachRight();
	void setDepth(int depth);
	void setParent(AVLNode* node);
	void fakeDetach();
	void revertFakeDetach();

	AVLNode* getParent() const;
	AVLNode* getLeft() const;
	AVLNode* getRight() const;
	int getHeight() const;
	int getDepth() const;
	bool isLeaf() const;

	int getBalanceFactor();
	BalanceStatus getBalanceStatus();

   private:
	void updateHeight();

   private:
	AVLNode *mLeft, *mRight;
	AVLNode* mParent;
	int mHeight, mDepth;

	AVLNode* visualBackupParent;
	bool visualLeftChild;
};

#endif  //DATAVISUALIZATION2_AVLNODE_HPP

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
	void setChild(int id, Node234* child);
	void setParent(Node234* parent);
	void split(int& pivot, Node234*& left, Node234*& right);
	void insertSplit(int id, int pivot, Node234* left, Node234* right);

	bool isLeaf() const;
	bool overflow() const;
	Node234* getParent() const;
	Node234* findChild(int value) const;  // Return the child whose range contains "value"
	int getChildID(Node234* node) const;

   private:
	void insert(int id, int value);
	void align();
	void alignNode();
	void alignChildren();

	//	void drawCurrent(sf::RenderTarget& target, sf::RenderStates states) const override;

   private:
	const FontHolder& mFonts;
	const ColorHolder& mColors;

	Node234* mParent;
	std::vector<Node234*> mChildren;
	std::vector<PolyNode*> mData;
};

#endif  //DATAVISUALIZATION2_NODE234_HPP

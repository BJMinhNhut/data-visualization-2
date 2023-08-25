//
// Created by MINH NHUT on 8/23/2023.
//

#ifndef DATAVISUALIZATION2_TREE234_HPP
#define DATAVISUALIZATION2_TREE234_HPP

#include "Node234.hpp"
#include "Template/SceneNode.hpp"
#include "Visualizer/Animation.hpp"

class Tree234 : public SceneNode {
   public:
	static const int MAX_SIZE;

   public:
	Tree234(const FontHolder& fonts, const ColorHolder& colors);
	void insert(const int& value);
	void clear();
	void clearHighlight();
	void loadFromFile(const std::string& fileDir);
	void randomize();

	int getSize() const;
	int getRandomElement() const;

	std::pair<std::vector<Animation>, std::string> searchAnimation(const int& value);
	std::pair<std::vector<Animation>, std::string> insertAnimation(const int& value);

   private:
	Node234* split(Node234* node);  // split the node, return the root of the split node
	void align();
	void clear(Node234* node);
	void clearHighlight(Node234* node);
	void loadArray(const std::vector<int>& array);

	Node234* searchNode(int value, int depth);

   private:
	const ColorHolder& mColors;
	const FontHolder& mFonts;

	Node234* mRoot;
};

#endif  //DATAVISUALIZATION2_TREE234_HPP

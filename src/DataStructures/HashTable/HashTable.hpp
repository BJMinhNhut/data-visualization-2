//
// Created by MINH NHUT on 8/14/2023.
//

#ifndef DATAVISUALIZATION2_HASHTABLE_HPP
#define DATAVISUALIZATION2_HASHTABLE_HPP

#include "../PolyNode.hpp"
#include "Template/SceneNode.hpp"
#include "Visualizer/Animation.hpp"

#include <vector>

class HashTable : public SceneNode {
   public:
	static const unsigned int MAX_SIZE;
	static const int PADDING;
	static const int MIN_VALUE;
	static const int MAX_VALUE;
	static const int WIDTH;

   public:
	HashTable(const FontHolder& fonts, const ColorHolder& colors);

	void setSize(const unsigned int& size);
	void randomize();
	void loadFromFile(const std::string& fileDir);
	void clearHighlight();

	unsigned int getSize() const;

   private:
	void loadArray(const std::vector<int>& array);
	void align();
	void insert(const int& value);
	void clearData();

	unsigned int getID(const int& value) const;

   private:
	const ColorHolder& mColors;
	const FontHolder& mFonts;
	std::vector<PolyNode*> mNodes;
};

#endif  //DATAVISUALIZATION2_HASHTABLE_HPP

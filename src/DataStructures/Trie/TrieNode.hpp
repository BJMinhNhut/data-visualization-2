//
// Created by MINH NHUT on 8/18/2023.
//

#ifndef DATAVISUALIZATION2_TRIENODE_HPP
#define DATAVISUALIZATION2_TRIENODE_HPP

#include "../PolyNode.hpp"

class TrieNode : public PolyNode {
   public:
	typedef std::unique_ptr<TrieNode> Ptr;

   public:
	TrieNode(const FontHolder& fonts, const ColorHolder& colors, char character);

	void operator--();
	void operator++();

	int depth() const;
	int frequency() const;

   private:
	static int getCharID(const char& ch);

   private:
	std::vector<TrieNode*> mChildren;
	int mFrequency, mDepth;
	const char mChar;
};

#endif  //DATAVISUALIZATION2_TRIENODE_HPP

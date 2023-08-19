//
// Created by MINH NHUT on 8/18/2023.
//

#ifndef DATAVISUALIZATION2_TRIENODE_HPP
#define DATAVISUALIZATION2_TRIENODE_HPP

#include "../PolyNode.hpp"

class TrieNode : public PolyNode {
   public:
	typedef std::unique_ptr<TrieNode> Ptr;
	static const sf::Vector2f TREE_OFF_SET;

   public:
	TrieNode(const FontHolder& fonts, const ColorHolder& colors, char character);

	TrieNode* addString(const std::string& str, int freq);
	sf::Vector2f align();
	void clear();

	bool hasChild(char character) const;
	TrieNode* getChild(char character) const;
	char getChar() const;
	int depth() const;
	int frequency() const;
	int count() const;

   private:
	TrieNode* addChild(char character);
	static int getCharID(const char& ch);

   private:
	const FontHolder& mFonts;
	const ColorHolder& mColors;

	std::vector<TrieNode*> mChildren;
	int mFrequency, mDepth;
	const char mChar;
};

#endif  //DATAVISUALIZATION2_TRIENODE_HPP

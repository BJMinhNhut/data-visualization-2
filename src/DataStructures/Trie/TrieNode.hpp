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
	void popNode(const std::string& str);
	void removeLeaf(char character);
	sf::Vector2f align();
	void clear();
	void clearHighlight();
	void highlightOn();
	void highlightOff();

	bool hasChild(char character) const;
	bool hasString(const std::string& str) const;
	bool isStringEnd() const;
	TrieNode* getChild(char character) const;
	TrieNode* getParent() const;
	TrieNode* getNode(const std::string& str) const;
	char getChar() const;
	int frequency() const;
	int count() const;
	bool isLeaf() const;
	std::vector<TrieNode*> getEndNodes() const;

   private:
	void updateCurrent(sf::Time dt) override;

	void setParent(TrieNode* parent);
	TrieNode* addChild(char character);
	static int getCharID(const char& ch);

   private:
	const FontHolder& mFonts;
	const ColorHolder& mColors;

	std::vector<TrieNode*> mChildren;
	TrieNode *mParent, *mBin;
	int mFrequency;
	int mEndString;
	const char mChar;
};

#endif  //DATAVISUALIZATION2_TRIENODE_HPP

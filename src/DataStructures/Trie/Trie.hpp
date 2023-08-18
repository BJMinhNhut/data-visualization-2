//
// Created by MINH NHUT on 8/19/2023.
//

#ifndef DATAVISUALIZATION2_TRIE_HPP
#define DATAVISUALIZATION2_TRIE_HPP

#include "Template/ColorHolder.hpp"
#include "Template/ResourceIdentifiers.hpp"
#include "Template/SceneNode.hpp"
#include "TrieNode.hpp"

class Trie : public SceneNode {
   public:
	static const int MAX_SIZE;
	static const int MIN_LENGTH;
	static const int MAX_LENGTH;
	static const sf::Vector2f TREE_OFF_SET;

   public:
	Trie(const FontHolder& fonts, const ColorHolder& colors);

	std::string getRandomString() const;

	void clear();
	void randomize();
	void loadFromFile(const std::string& fileDir);
	void flush();

   private:
	const ColorHolder& mColors;
	const FontHolder& mFonts;

	int mSize, mNumString;
	TrieNode* mRoot;
};

#endif  //DATAVISUALIZATION2_TRIE_HPP

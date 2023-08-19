//
// Created by MINH NHUT on 8/19/2023.
//

#ifndef DATAVISUALIZATION2_TRIE_HPP
#define DATAVISUALIZATION2_TRIE_HPP

#include "Template/ColorHolder.hpp"
#include "Template/ResourceIdentifiers.hpp"
#include "Template/SceneNode.hpp"
#include "TrieNode.hpp"
#include "Visualizer/Animation.hpp"

class Trie : public SceneNode {
   public:
	static const int MAX_SIZE;
	static const int MIN_LENGTH;
	static const int MAX_LENGTH;

   public:
	Trie(const FontHolder& fonts, const ColorHolder& colors);

	std::string getRandomElement() const;
	static std::string getRandString(int minLen, int maxLen);
	int count() const;

	std::pair<std::vector<Animation>, std::string> insertAnimation(const std::string& str);
	std::pair<std::vector<Animation>, std::string> searchAnimation(const std::string& str);

	void clear();
	void clearHighlight();
	void randomize();
	void loadFromFile(const std::string& fileDir);

	void push(const std::string& str);

   private:
	int getLCP(const std::string& str) const;
	std::string getString(TrieNode* node) const;

	void format(std::string& str);
	static bool valid(const std::string& str);

   private:
	const ColorHolder& mColors;
	const FontHolder& mFonts;

	TrieNode* mRoot;
};

#endif  //DATAVISUALIZATION2_TRIE_HPP

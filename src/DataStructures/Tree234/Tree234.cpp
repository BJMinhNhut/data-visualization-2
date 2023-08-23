//
// Created by MINH NHUT on 8/23/2023.
//

#include "Tree234.hpp"

Tree234::Tree234(const FontHolder& fonts, const ColorHolder& colors)
    : mFonts(fonts), mColors(colors) {
	mRoot = new Node234(fonts, colors);
	attachChild(Node234::Ptr(mRoot));
}

void Tree234::insert(const int& value) {
	mRoot->insert(value);
}

//
// Created by MINH NHUT on 8/15/2023.
//

#include "AVLTree.hpp"
#include "AVLCode.hpp"
#include "Template/Random.hpp"

#include <algorithm>
#include <fstream>
#include <iostream>

const int AVLTree::MAX_SIZE = 42;
const int AVLTree::MIN_VALUE = 0;
const int AVLTree::MAX_VALUE = 999;
const sf::Vector2f AVLTree::TREE_OFF_SET(27.f, 90.f);

AVLTree::AVLTree(const FontHolder& fonts, const ColorHolder& colors)
    : mFonts(fonts), mColors(colors), mRoot(nullptr), mInOrder(), mBin() {
	randomize();
}

unsigned int AVLTree::getSize() const {
	return mInOrder.size();
}

int AVLTree::getRandomElement() const {
	auto elements = getInOrder(mRoot);
	return elements[Random::getInt(0, (int)elements.size() - 1)]->getIntData();
}

#ifdef SFML_DEBUG
void AVLTree::rotateLeft() {
	rotateLeft(mRoot->getLeft());
}

void AVLTree::rotateRight() {
	rotateRight(mRoot->getLeft());
}

#endif

std::pair<std::vector<Animation>, std::string> AVLTree::insertAnimation(const int& value) {
	if (getSize() == MAX_SIZE)
		throw std::out_of_range("Maximum size reached, you are not allowed to insert more values.");

	const std::string& code = AVLCode::Insert;
	std::vector<Animation> list;
	list.push_back(Animation({}, "Insert " + std::to_string(value) + " to AVL tree.",
	                         [&]() { clearHighlight(mRoot); }));

	auto* newNode = new AVLNode(mFonts, mColors);
	newNode->setData(value);
	newNode->setTargetScale(0.f, 0.f, None);
	attachChild(AVLNode::Ptr(newNode));

	if (mRoot == nullptr) {
		mRoot = newNode;
		list.push_back(Animation(
		    {0},
		    "Tree is empty, insert " + std::to_string(value) +
		        ". Tree is balanced, complexity is O(1).",
		    [&, newNode]() {
			    newNode->setTargetScale(1.f, 1.f, Smooth);
			    newNode->highlight(PolyNode::Primary);
			    alignAsTree();
		    },
		    [&, newNode]() {
			    newNode->setTargetScale(0.f, 0.f, Smooth);
			    alignAsTree();
		    }));
		return std::make_pair(list, code);
	}

	/* insert phase */
	AVLNode* last = traverseToLeafAnimation(value, list);
	bool goLeft = value < last->getIntData();

	list.push_back(Animation(
	    {0}, "Null node reached, insert " + std::to_string(value),
	    [&, newNode, last, goLeft]() {
		    newNode->highlight(PolyNode::Primary);

		    if (goLeft)
			    last->attachLeft(newNode);
		    else
			    last->attachRight(newNode);
		    last->highlight(PolyNode::None);

		    alignAsTree();
		    newNode->setPosition(last->getPosition());
		    newNode->setTargetScale(1.f, 1.f, None);
	    },
	    [&, newNode, last, goLeft]() {
		    newNode->setTargetScale(0.f, 0.f, None);
		    if (goLeft) {
			    last->detachLeft();
		    } else {
			    last->detachRight();
		    }
		    last->highlight(PolyNode::Primary);
		    alignAsTree();
	    }));
	list.back().play();

	balanceAnimation(newNode, nullptr, list);

	for (auto itr = list.rbegin(); itr != list.rend(); itr++)
		itr->revert();
	return std::make_pair(list, code);
}

std::pair<std::vector<Animation>, std::string> AVLTree::deleteAnimation(const int& value) {
	const std::string& code = AVLCode::Delete;
	std::vector<Animation> list;
	list.push_back(Animation({}, "Delete " + std::to_string(value) + " from AVL tree.",
	                         [&]() { clearHighlight(mRoot); }));

	AVLNode* deleteNode = traverseSearchingAnimation(value, list);

	if (deleteNode == nullptr) {
		for (auto itr = list.rbegin(); itr != list.rend(); itr++)
			itr->revert();
		return std::make_pair(list, code);
	}

	AVLNode* balanceStart = deleteNodeAnimation(deleteNode, list);

	balanceAnimation(balanceStart, deleteNode, list);

	for (auto itr = list.rbegin(); itr != list.rend(); itr++)
		itr->revert();
	return std::make_pair(list, code);
}

AVLNode* AVLTree::traverseSearchingAnimation(const int& value, std::vector<Animation>& list) {
	AVLNode* cur = mRoot;
	AVLNode* last = nullptr;
	while (cur != nullptr) {
		std::string log = std::to_string(value);

		if (value == cur->getIntData())
			log += " found";
		else if (value < cur->getIntData())
			log += " < current node data, go to left child";
		else
			log += " >= current node data, go to right child";

		list.push_back(Animation(
		    {0}, log,
		    [&, cur, last]() {
			    if (last)
				    last->highlight(PolyNode::None);
			    cur->highlight(PolyNode::Primary);
		    },
		    [&, cur, last]() {
			    if (last)
				    last->highlight(PolyNode::Primary);
			    cur->highlight(PolyNode::None);
		    }));
		list.back().play();

		last = cur;
		if (value == cur->getIntData())
			return cur;
		else if (value < cur->getIntData()) {
			cur = cur->getLeft();
		} else {
			cur = cur->getRight();
		}
	}
	list.push_back(Animation(
	    {}, "Null node reached. Cancel deletion, worst-case complexity O(logn).",
	    [&]() { clearHighlight(); },
	    [&, last]() {
		    if (last)
			    last->highlight(PolyNode::Primary);
	    }));
	return nullptr;
}

AVLNode* AVLTree::deleteNodeAnimation(AVLNode* node, std::vector<Animation>& list) {
	int numChild = (node->getLeft() ? 1 : 0) + (node->getRight() ? 1 : 0);
	if (numChild == 0) {  // node is Leaf
		dump(node);
		bool isRoot = node == mRoot;
		AVLNode* mParent = node->getParent();
		list.push_back(Animation(
		    {0}, "Node is leaf, just delete it from tree",
		    [&, node, isRoot]() {
			    if (isRoot) {
				    node->setTargetScale(0.f, 0.f, Smooth);
				    mRoot = nullptr;
			    } else
				    node->fakeDetach();
			    alignAsTree();
		    },
		    [&, node, isRoot]() {
			    if (isRoot) {
				    node->setTargetScale(1.f, 1.f, Smooth);
				    mRoot = node;
			    } else
				    node->revertFakeDetach();
			    alignAsTree();
		    }));
		list.back().play();
		return mParent;
	} else if (numChild == 1) {  // node has one child
		return deleteOneChildNodeAnimation(node, list);
	} else {  // node has two child
		return deleteTwoChildNodeAnimation(node, list);
	}
}

AVLNode* AVLTree::deleteOneChildNodeAnimation(AVLNode* node, std::vector<Animation>& list) {
	AVLNode* mParent = node->getParent();
	bool goLeft = mParent && mParent->getLeft() == node;
	bool childIsLeft;
	AVLNode* mChild;

	if (node->getLeft()) {
		mChild = node->getLeft();
		childIsLeft = true;
	} else {
		mChild = node->getRight();
		childIsLeft = false;
	}
	dump(node);
	assert(mChild != nullptr);
	list.push_back(Animation(
	    {0}, "Node has one child, so delete it and assign the child to the parent node.",
	    [&, node, mChild, mParent, goLeft, childIsLeft]() {
		    if (childIsLeft)
			    node->detachLeft();
		    else
			    node->detachRight();

		    assert(node->isLeaf());
		    if (mParent) {
			    node->fakeDetach();
			    if (goLeft)
				    mParent->attachLeft(mChild);
			    else
				    mParent->attachRight(mChild);
		    } else {
			    mRoot = mChild;
			    node->setTargetScale(0.f, 0.f, Smooth);
		    }
		    alignAsTree();
	    },
	    [&, node, mChild, mParent, childIsLeft]() {
		    if (childIsLeft)
			    node->attachLeft(mChild);
		    else
			    node->attachRight(mChild);

		    if (mParent)
			    node->revertFakeDetach();
		    else {
			    mRoot = node;
			    node->setTargetScale(1.f, 1.f, Smooth);
		    }
		    alignAsTree();
	    }));
	list.back().play();
	return mParent;
}

AVLNode* AVLTree::deleteTwoChildNodeAnimation(AVLNode* node, std::vector<Animation>& list) {
	AVLNode* successor = findSuccessorAnimation(node, list);
	assert(successor != nullptr);
	assert(successor->getLeft() == nullptr);
	AVLNode* mParent = successor->getParent();
	bool isSuccessorLeft = mParent->getLeft() == successor;
	AVLNode* successorRight = successor->getRight();
	dump(successor);
	list.push_back(Animation(
	    {0}, "Swap data of " + node->getData() + " with its successor. Delete the successor.",
	    [&, node, successor, isSuccessorLeft, successorRight, mParent]() {
		    node->swapData(successor);
		    node->highlight(PolyNode::Primary);

		    if (isSuccessorLeft) {
			    mParent->detachLeft();
			    if (successorRight)
				    mParent->attachLeft(successorRight);
		    } else {
			    mParent->detachRight();
			    if (successorRight)
				    mParent->attachRight(successorRight);
		    }

		    successor->setTargetScale(0.f, 0.f, Smooth);
		    alignAsTree();
	    },
	    [&, node, successor, isSuccessorLeft, mParent, successorRight]() {
		    node->swapData(successor);
		    node->highlight(PolyNode::None);
		    successor->setTargetScale(1.f, 1.f, Smooth);
		    if (isSuccessorLeft) {
			    mParent->attachLeft(successor);
		    } else {
			    mParent->attachRight(successor);
		    }
		    if (successorRight)
			    successor->attachRight(successorRight);
		    alignAsTree();
	    }));
	list.back().play();
	return mParent;
}

AVLNode* AVLTree::findSuccessorAnimation(AVLNode* node, std::vector<Animation>& list) {
	if (node->getRight() == nullptr) {
		return nullptr;
	}
	AVLNode* cur = node->getRight();
	AVLNode* last = nullptr;
	while (true) {
		std::string description = cur->getLeft()
		                              ? "Find successor: Node has a left child, go to left."
		                              : "Node doesn't have a left child, so " + cur->getData() +
		                                    " is the inorder successor.";

		list.push_back(Animation(
		    {0}, description,
		    [&, cur, last]() {
			    if (last)
				    last->highlight(PolyNode::None);
			    cur->highlight(PolyNode::Secondary);
		    },
		    [&, cur, last]() {
			    if (last)
				    last->highlight(PolyNode::Secondary);
			    cur->highlight(PolyNode::None);
		    }));
		list.back().play();

		if (cur->getLeft() == nullptr)
			break;
		last = cur;
		cur = cur->getLeft();
	}

	return cur;
}

AVLNode* AVLTree::traverseToLeafAnimation(const int& value, std::vector<Animation>& list) {
	AVLNode* cur = mRoot;
	AVLNode* last = nullptr;
	while (cur != nullptr) {
		std::string log =
		    std::to_string(value) + ((value < cur->getIntData())
		                                 ? " < current node data, go to left child"
		                                 : " >= current node data, go to right child");
		list.push_back(Animation(
		    {0}, log,
		    [&, cur, last]() {
			    if (last)
				    last->highlight(PolyNode::None);
			    cur->highlight(PolyNode::Primary);
		    },
		    [&, cur, last]() {
			    if (last)
				    last->highlight(PolyNode::Primary);
			    cur->highlight(PolyNode::None);
		    }));
		list.back().play();

		last = cur;
		if (value < cur->getIntData()) {
			cur = cur->getLeft();
		} else {
			cur = cur->getRight();
		}
	}
	return last;
}

void AVLTree::balanceAnimation(AVLNode* node, AVLNode* last, std::vector<Animation>& list) {

	while (node != nullptr) {
		AVLNode* parent = node->getParent();

		const int bf = node->getBalanceFactor();
		//		std::cout << "Node: " << ' ' << node->getData() << ' ' << bf << '\n';
		if (abs(bf) > 1) {
			list.push_back(Animation(
			    {1}, "Subtree is unbalanced, start rotating...",
			    [&, last, node, bf]() {
				    if (last) {
					    last->highlight(PolyNode::None);
					    last->setLabel("");
				    }
				    node->highlight(PolyNode::Primary);
				    node->setLabel("bf = " + std::to_string(bf));
			    },
			    [&, last, node]() {
				    if (last)
					    last->highlight(PolyNode::Primary);
				    node->highlight(PolyNode::None);
				    node->setLabel("");
			    }));

			AVLNode::BalanceStatus status = node->getBalanceStatus();
			switch (status) {
				case AVLNode::Balanced:
					assert(false);
					break;
				case AVLNode::LeftLeft:
					node = rotateRightAnimation(node, list);
					break;
				case AVLNode::LeftRight:
					node = rotateLRAnimation(node, list);
					break;
				case AVLNode::RightRight:
					node = rotateLeftAnimation(node, list);
					break;
				case AVLNode::RightLeft:
					node = rotateRLAnimation(node, list);
					break;
			}
		} else {
			list.push_back(Animation(
			    {1}, "Subtree is balanced, go to parent.",
			    [&, last, node, bf]() {
				    if (last) {
					    last->highlight(PolyNode::None);
					    last->setLabel("");
				    }
				    node->highlight(PolyNode::Primary);
				    node->setLabel("bf = " + std::to_string(bf));
			    },
			    [&, last, node]() {
				    if (last)
					    last->highlight(PolyNode::Primary);
				    node->highlight(PolyNode::None);
				    node->setLabel("");
			    }));
			list.back().play();
		}

		last = node;
		node = parent;
	}

	list.push_back(Animation({}, "Tree is balanced. Time complexity is O(logn).",
	                         [&]() { clearHighlight(mRoot); }));
}

AVLNode* AVLTree::rotateRightAnimation(AVLNode* node, std::vector<Animation>& list) {
	AVLNode* mLeft = node->getLeft();
	list.push_back(Animation(
	    {1, 2}, "Left-left case: rotate right.",
	    [&, node, mLeft]() {
		    rotateRight(node);
		    node->highlight(PolyNode::None);
		    node->setLabel("");
		    mLeft->highlight(PolyNode::Primary);
		    mLeft->setLabel("bf = " + std::to_string(mLeft->getBalanceFactor()));
	    },
	    [&, node, mLeft]() {
		    rotateLeft(mLeft);
		    node->highlight(PolyNode::Primary);
		    node->setLabel("bf = " + std::to_string(node->getBalanceFactor()));
		    mLeft->highlight(PolyNode::None);
		    mLeft->setLabel("");
	    }));
	list.back().play();

	return mLeft;
}

AVLNode* AVLTree::rotateRLAnimation(AVLNode* node, std::vector<Animation>& list) {
	AVLNode* mRight = node->getRight();
	assert(mRight != nullptr);
	AVLNode* RLNode = mRight->getLeft();
	assert(RLNode != nullptr);

	list.push_back(Animation(
	    {1, 5}, "Right-Left case: rotate right the right child, then rotate left.",
	    [&, node, mRight]() {
		    node->highlight(PolyNode::Primary);
		    node->setLabel("bf = " + std::to_string(node->getBalanceFactor()));
		    rotateRight(mRight);
	    },
	    [&, node, RLNode]() {
		    node->highlight(PolyNode::None);
		    node->setLabel("");
		    rotateLeft(RLNode);
	    }));
	list.back().play();

	list.push_back(Animation(
	    {1, 5}, "Right-Left case: Rotate right the right child, then rotate left.",
	    [&, node, RLNode]() {
		    rotateLeft(node);
		    node->highlight(PolyNode::None);
		    node->setLabel("");
		    RLNode->highlight(PolyNode::Primary);
		    RLNode->setLabel("bf = " + std::to_string(RLNode->getBalanceFactor()));
	    },
	    [&, node, RLNode]() {
		    rotateRight(RLNode);
		    node->highlight(PolyNode::Primary);
		    node->setLabel("bf = " + std::to_string(node->getBalanceFactor()));
		    RLNode->setLabel("");
		    RLNode->highlight(PolyNode::None);
	    }));
	list.back().play();

	return RLNode;
}

AVLNode* AVLTree::rotateLeftAnimation(AVLNode* node, std::vector<Animation>& list) {
	AVLNode* mRight = node->getRight();
	list.push_back(Animation(
	    {1, 4}, "Right-Right case: rotate left.",
	    [&, node, mRight]() {
		    rotateLeft(node);
		    node->highlight(PolyNode::None);
		    node->setLabel("");
		    mRight->highlight(PolyNode::Primary);
		    mRight->setLabel("bf = " + std::to_string(mRight->getBalanceFactor()));
	    },
	    [&, node, mRight]() {
		    rotateRight(mRight);
		    node->highlight(PolyNode::Primary);
		    node->setLabel("bf = " + std::to_string(node->getBalanceFactor()));
		    mRight->highlight(PolyNode::None);
		    mRight->setLabel("");
	    }));
	list.back().play();

	return mRight;
}

AVLNode* AVLTree::rotateLRAnimation(AVLNode* node, std::vector<Animation>& list) {
	AVLNode* mLeft = node->getLeft();
	assert(mLeft != nullptr);
	AVLNode* LRNode = mLeft->getRight();
	assert(LRNode != nullptr);

	list.push_back(Animation(
	    {1, 3}, "Right-Left case: rotate left the left child, then rotate right.",
	    [&, node, mLeft]() {
		    rotateLeft(mLeft);
		    node->highlight(PolyNode::Primary);
		    node->setLabel("bf = " + std::to_string(node->getBalanceFactor()));
	    },
	    [&, node, LRNode]() {
		    node->highlight(PolyNode::None);
		    node->setLabel("");
		    rotateRight(LRNode);
	    }));
	list.back().play();

	list.push_back(Animation(
	    {1, 3}, "Right-Left case: rotate left the left child, then rotate right",
	    [&, node, LRNode]() {
		    rotateRight(node);
		    node->highlight(PolyNode::None);
		    node->setLabel("");
		    LRNode->highlight(PolyNode::Primary);
		    LRNode->setLabel("bf = " + std::to_string(LRNode->getBalanceFactor()));
	    },
	    [&, node, LRNode]() {
		    rotateLeft(LRNode);
		    node->highlight(PolyNode::Primary);
		    node->setLabel("bf = " + std::to_string(node->getBalanceFactor()));
		    LRNode->setLabel("");
		    LRNode->highlight(PolyNode::None);
	    }));
	list.back().play();

	return LRNode;
}

std::pair<std::vector<Animation>, std::string> AVLTree::searchAnimation(const int& value) {
	const std::string& code = AVLCode::Search;
	std::vector<Animation> list;
	list.push_back(Animation({}, "Search for " + std::to_string(value) + " in AVL tree."));
	AVLNode* cur = mRoot;
	AVLNode* last = nullptr;
	while (true) {
		if (cur == nullptr) {
			list.push_back(Animation(
			    {0, 1}, "Current node is null, hence " + std::to_string(value) + " is NOT FOUND!",
			    [&, last]() {
				    if (last)
					    last->highlight(PolyNode::None);
			    },
			    [&, last]() {
				    if (last)
					    last->highlight(PolyNode::Primary);
			    }));
			break;
		} else {
			list.push_back(Animation(
			    {0}, "Current node is not null, continue searching",
			    [&, cur, last]() {
				    cur->highlight(PolyNode::Primary);
				    if (last)
					    last->highlight(PolyNode::None);
			    },
			    [&, cur, last]() {
				    cur->highlight(PolyNode::None);
				    if (last)
					    last->highlight(PolyNode::Primary);
			    }));
		}
		if (cur->getIntData() == value) {
			list.push_back(
			    Animation({2, 3}, std::to_string(value) + " is FOUND. Complexity is O(logn)."));
			break;
		} else if (value < cur->getIntData()) {
			list.push_back(Animation({4, 5}, std::to_string(value) +
			                                     " < current node data. Proceed "
			                                     "to search on the left child."));
			last = cur;
			cur = cur->getLeft();
		} else {
			list.push_back(Animation({6, 7}, std::to_string(value) +
			                                     " > current node data. Proceed to search "
			                                     "on the right child."));
			last = cur;
			cur = cur->getRight();
		}
	}
	return std::make_pair(list, code);
}

void AVLTree::clear() {
	clear(mRoot);
}

void AVLTree::randomize() {
	loadArray(Random::getArray(1, MAX_SIZE, MIN_VALUE, MAX_VALUE));
}

void AVLTree::loadFromFile(const std::string& fileDir) {
	std::ifstream fileStream(fileDir);
	std::vector<int> elements;
	std::string token;
	int value;
	while (fileStream >> token && elements.size() < MAX_SIZE) {
		try {
			value = std::stoi(token);
			if (value < MIN_VALUE || value > MAX_VALUE)
				throw std::exception();
			std::cout << "Token [" << token << "] read\n";
			elements.push_back(value);
		} catch (std::exception& e) {
			std::cerr << "Token [" << token << "] is not convertible\n";
		}
	}
	fileStream.close();
	loadArray(elements);
}

void AVLTree::clearHighlight() {
	clearHighlight(mRoot);
}

void AVLTree::insert(const int& value) {
	mRoot = pureInsert(mRoot, value);
	alignAsTree();
}

void AVLTree::dump(AVLNode* node) {
	assert(node != nullptr);
	mBin.push_back(node);
}

void AVLTree::flush() {
	for (auto& node : mBin) {
		assert(node->getLeft() == nullptr);
		assert(node->getRight() == nullptr);
		assert(node->getParent() == nullptr);
		std::cout << "flushing: " << node->getData() << '\n';
		detachChild(*node);
	}
	std::vector<AVLNode*>().swap(mBin);
}

void AVLTree::clear(AVLNode* root) {
	if (root == nullptr)
		return;
	clear(root->getLeft());
	clear(root->getRight());
	if (root == mRoot) {
		mRoot = nullptr;
		std::vector<AVLNode*>().swap(mInOrder);
	}
	detachChild(*root);
}

void AVLTree::loadArray(std::vector<int> array) {
	clear();
	std::sort(array.begin(), array.end());
	mRoot = create(array, 0, (int)array.size() - 1);
	alignAsTree();
}

AVLNode* AVLTree::create(const std::vector<int>& array, int left, int right) {
	if (left > right)
		return nullptr;
	auto* root = new AVLNode(mFonts, mColors);
	attachChild(AVLNode::Ptr(root));
	int mid = (left + right) >> 1;
	root->setData(array[mid]);
	root->attachLeft(create(array, left, mid - 1));
	root->attachRight(create(array, mid + 1, right));
	return root;
}

void AVLTree::rotateLeft(AVLNode* root) {
	AVLNode* parent = root->getParent();
	AVLNode* newRoot = root->getRight();
	assert(newRoot != nullptr);

	if (parent) {
		if (root == parent->getLeft())
			parent->attachLeft(newRoot);
		else
			parent->attachRight(newRoot);
	} else
		mRoot = newRoot;

	root->attachRight(newRoot->getLeft());
	newRoot->attachLeft(root);
	alignAsTree();

	assert(newRoot->getParent() == parent);
	assert(root->getParent() == newRoot);
}

void AVLTree::rotateRight(AVLNode* root) {
	AVLNode* parent = root->getParent();
	AVLNode* newRoot = root->getLeft();
	assert(newRoot != nullptr);

	if (parent) {
		if (root == parent->getLeft())
			parent->attachLeft(newRoot);
		else
			parent->attachRight(newRoot);
	} else
		mRoot = newRoot;

	root->attachLeft(newRoot->getRight());
	newRoot->attachRight(root);
	alignAsTree();

	assert(newRoot->getParent() == parent);
	assert(root->getParent() == newRoot);
}

void AVLTree::clearHighlight(AVLNode* root) {
	if (root == nullptr)
		return;
	root->highlight(PolyNode::None);
	root->setLabel("");
	root->resetDataScale();
	clearHighlight(root->getLeft());
	clearHighlight(root->getRight());
}

AVLNode* AVLTree::pureInsert(AVLNode* root, const int& value) {
	if (root == nullptr) {
		auto* newNode = new AVLNode(mFonts, mColors);
		newNode->setData(value);
		attachChild(std::unique_ptr<AVLNode>(newNode));
		return newNode;
	} else if (value < root->getIntData()) {
		root->attachLeft(pureInsert(root->getLeft(), value));
	} else {
		root->attachRight(pureInsert(root->getRight(), value));
	}
	return root;
}

void AVLTree::calculateDepth() {
	mRoot->setDepth(0);
	calculateDepth(mRoot);
}

void AVLTree::alignAsTree() {
	mInOrder = getInOrder(mRoot);
	if (mRoot == nullptr)
		return;

	calculateDepth();
	int mid = (int)mInOrder.size() / 2;
	for (int i = 0; i < mInOrder.size(); ++i) {
		float x = float(i - mid) * TREE_OFF_SET.x;
		float y = (float)mInOrder[i]->getDepth() * TREE_OFF_SET.y;
		mInOrder[i]->setTargetPosition(x, y, Smooth);
	}
}

std::vector<AVLNode*> AVLTree::getInOrder(AVLNode* root) const {
	std::vector<AVLNode*> inOrder;
	if (root) {
		if (root->getLeft()) {
			std::vector<AVLNode*> mLeft = getInOrder(root->getLeft());
			inOrder.insert(inOrder.end(), mLeft.begin(), mLeft.end());
		}

		inOrder.push_back(root);

		if (root->getRight()) {
			std::vector<AVLNode*> mRight = getInOrder(root->getRight());
			inOrder.insert(inOrder.end(), mRight.begin(), mRight.end());
		}
	}
	return inOrder;
}

void AVLTree::calculateDepth(AVLNode* root) {
	if (root == nullptr)
		return;

	if (AVLNode* mLeft = root->getLeft()) {
		mLeft->setDepth(root->getDepth() + 1);
		calculateDepth(mLeft);
	}

	if (AVLNode* mRight = root->getRight()) {
		mRight->setDepth(root->getDepth() + 1);
		calculateDepth(mRight);
	}
}

void AVLTree::updateCurrent(sf::Time dt) {
}

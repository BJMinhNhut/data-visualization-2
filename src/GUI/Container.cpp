//
// Created by MINH NHUT on 7/2/2023.
//

#include "Container.hpp"

#include <SFML/Graphics/RenderStates.hpp>
#include <SFML/Graphics/RenderTarget.hpp>
#include <SFML/Window/Event.hpp>

#include <iostream>

namespace GUI {

Container::Container() : mChildren(), mSelectedChild(-1), mActivatedChild(-1) {}

void Container::pack(const Component::Ptr& component) {
	mChildren.push_back(component);
}

void Container::activateChild(const Component::Ptr& component) {
	for (int index = 0; index < mChildren.size(); ++index)
		if (mChildren[index] == component)
			activate(index);
}

void Container::reset() {
	if (hasActivation()) {
		mChildren[mActivatedChild]->deactivate();
	}

	if (hasSelection())
		mChildren[mSelectedChild]->deselect();
	mSelectedChild = mActivatedChild = -1;
}

bool Container::isSelectable() const {
	return false;
}

void Container::deselect() {
	for (auto& child : mChildren)
		if (child->isSelected() && !child->isActive())
			child->deselect();
}

bool Container::update(sf::Time dt) {
	for (auto& index : mChildren) {
		index->update(dt);
	}
	return true;
}

bool Container::handleEvent(const sf::Event& event) {
	// If we have selected a child then give it events
	if (event.type == sf::Event::MouseMoved) {
		updateSelect(sf::Vector2i(event.mouseMove.x, event.mouseMove.y));
	}

	if (hasSelection()) {
		if (mChildren[mSelectedChild]->handleEvent(event)) {
			if (hasActivation() && mActivatedChild != mSelectedChild) {
				mChildren[mActivatedChild]->deactivate();
				mChildren[mActivatedChild]->deselect();
			}
#ifdef SFML_DEBUG
			std::cout << "activated: " << mSelectedChild << '\n';
#endif
			if (mChildren[mSelectedChild]->isActive()) {
				mActivatedChild = mSelectedChild;
				mSelectedChild = -1;
			}
			updateSelect(sf::Vector2i(event.mouseButton.x, event.mouseButton.y));
		}
	}
	return true;
}

void Container::draw(sf::RenderTarget& target, sf::RenderStates states) const {
	states.transform *= getTransform();

	for (const Component::Ptr& child : mChildren)
		target.draw(*child, states);
}

bool Container::hasSelection() const {
	return mSelectedChild >= 0;
}

bool Container::hasActivation() const {
	return mActivatedChild >= 0;
}

void Container::select(std::size_t index) {
	if (mChildren[index]->isSelectable() && !mChildren[index]->isActive()) {
		if (hasSelection() && !mChildren[mSelectedChild]->isActive())
			mChildren[mSelectedChild]->deselect();

		mChildren[index]->select();
		mSelectedChild = index;
	}
}

void Container::activate(std::size_t index) {
	if (mChildren[index]->isSelectable() && !mChildren[index]->isActive()) {
		if (hasActivation()) {
			mChildren[mActivatedChild]->deactivate();
			mChildren[mActivatedChild]->deselect();
		}
		mChildren[index]->activate();
		mActivatedChild = index;
	}
}

void Container::updateSelect(sf::Vector2i point) {
	for (int index = 0; index < mChildren.size(); ++index) {
		if (mChildren[index]->isSelectable() && !mChildren[index]->isActive() &&
		    mChildren[index]->contains(point)) {
			select(index);
#ifdef SFML_DEBUG
			std::cout << "selecting: " << index << '\n';
#endif
			return;
		}
	}
	// no component is selected
	if (hasSelection() && !mChildren[mSelectedChild]->isActive()) {
		mChildren[mSelectedChild]->deselect();
		mSelectedChild = -1;
	}
}

bool Container::contains(sf::Vector2i point) const {
	return std::any_of(
	    mChildren.begin(), mChildren.end(),
	    [&point](const GUI::Component::Ptr& child) { return child->contains(point); });
}

}  // namespace GUI
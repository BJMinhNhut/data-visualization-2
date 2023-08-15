//
// Created by MINH NHUT on 7/15/2023.
//

#include "DataState.hpp"
#include "GUI/Button.hpp"
#include "GUI/Label.hpp"
#include "GUI/Sprite.hpp"
#include "Template/Utility.hpp"

#include <SFML/Graphics/RenderWindow.hpp>

#include <memory>

DataState::DataState(StateStack& stack, Context context)
    : State(stack, context),
      mGUIContainer(),
      mBackgroundSprite(context.textures->get(Textures::Background)),
      mTitle(context.textures->get(Textures::Title)) {

	Utility::centerOrigin(mTitle);
	mTitle.setPosition(context.window->getSize().x / 2.f, context.window->getSize().y / 4.f);

	auto backButton = std::make_shared<GUI::Button>(GUI::Button::Back, *getContext().fonts,
	                                                *getContext().textures, *getContext().colors);
	backButton->setPosition(610u, 30u);
	backButton->setCallback([this]() {
		requestStackPop();
		requestStackPush(States::Menu);
	});
	mGUIContainer.pack(backButton);

	auto titleBar = std::make_shared<GUI::Sprite>(context.textures->get(Textures::TitleBar));
	titleBar->setPosition(800.f, 30.f);
	mGUIContainer.pack(titleBar);

	auto titleLabel = std::make_shared<GUI::Label>(GUI::Label::Bold, "Data Structure Menu",
	                                               *context.fonts, *getContext().colors);
	titleLabel->setPosition(titleBar->getPosition());
	titleLabel->alignCenter();
	mGUIContainer.pack(titleLabel);

	auto HashButton = std::make_shared<GUI::Button>(GUI::Button::MenuHash, *context.fonts,
	                                                *context.textures, *context.colors);
	HashButton->setPosition(context.window->getSize().x / 2.f - 275.f, 460.f);
	HashButton->setCallback([this]() {
		requestStackPop();
		requestStackPush(States::VisualHash);
	});
	mGUIContainer.pack(HashButton);

	auto AVLButton = std::make_shared<GUI::Button>(GUI::Button::MenuAVL, *context.fonts,
	                                               *context.textures, *context.colors);
	AVLButton->setPosition(context.window->getSize().x / 2.f, 460.f);
	AVLButton->setCallback([this]() {
		requestStackPop();
		requestStackPush(States::VisualAVL);
	});
	mGUIContainer.pack(AVLButton);
	//
	auto Tree234Button = std::make_shared<GUI::Button>(GUI::Button::Menu234, *context.fonts,
	                                                   *context.textures, *context.colors);
	Tree234Button->setPosition(context.window->getSize().x / 2.f + 275.f, 460.f);
	Tree234Button->setCallback([this]() {
		requestStackPop();
		requestStackPush(States::VisualTemplate);
	});
	mGUIContainer.pack(Tree234Button);

	auto MinHeapButton = std::make_shared<GUI::Button>(GUI::Button::MenuMinHeap, *context.fonts,
	                                                   *context.textures, *context.colors);
	MinHeapButton->setPosition(context.window->getSize().x / 2.f - 413, 640.f);
	MinHeapButton->setCallback([this]() {
		requestStackPop();
		requestStackPush(States::VisualMinHeap);
	});
	mGUIContainer.pack(MinHeapButton);

	auto MaxHeapButton = std::make_shared<GUI::Button>(GUI::Button::MenuMaxHeap, *context.fonts,
	                                                   *context.textures, *context.colors);
	MaxHeapButton->setPosition(context.window->getSize().x / 2.f - 138.f, 640.f);
	MaxHeapButton->setCallback([this]() {
		requestStackPop();
		requestStackPush(States::VisualMaxHeap);
	});
	mGUIContainer.pack(MaxHeapButton);

	auto TrieButton = std::make_shared<GUI::Button>(GUI::Button::MenuTrie, *context.fonts,
	                                                *context.textures, *context.colors);
	TrieButton->setPosition(context.window->getSize().x / 2.f + 138.f, 640.f);
	TrieButton->setCallback([this]() {
		requestStackPop();
		requestStackPush(States::VisualTemplate);
	});
	mGUIContainer.pack(TrieButton);
	//
	auto GraphButton = std::make_shared<GUI::Button>(GUI::Button::MenuGraph, *context.fonts,
	                                                 *context.textures, *context.colors);
	GraphButton->setPosition(context.window->getSize().x / 2.f + 413.f, 640.f);
	GraphButton->setCallback([this]() {
		requestStackPop();
		requestStackPush(States::VisualTemplate);
	});
	mGUIContainer.pack(GraphButton);
}

void DataState::draw() {
	sf::RenderWindow& window = *getContext().window;
	window.setView(window.getDefaultView());

	window.draw(mBackgroundSprite);
	window.draw(mTitle);
	window.draw(mGUIContainer);
}

bool DataState::update(sf::Time dt) {
	return true;
}

bool DataState::handleEvent(const sf::Event& event) {
	mGUIContainer.handleEvent(event);
	return false;
}
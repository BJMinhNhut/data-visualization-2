//
// Created by MINH NHUT on 8/2/2023.
//

#ifndef DATAVISUALIZATION2_ACTIONSHUB_HPP
#define DATAVISUALIZATION2_ACTIONSHUB_HPP

#include "GUI/Button.hpp"
#include "GUI/Container.hpp"
#include "Template/ColorHolder.hpp"
#include "Template/ResourceIdentifiers.hpp"

#include <SFML/Graphics/Drawable.hpp>
#include <SFML/Graphics/Transformable.hpp>
#include <SFML/System/NonCopyable.hpp>

#include <vector>

class ActionsHub : public sf::Drawable, public sf::Transformable, public sf::NonCopyable {
   public:
	static const int MAX_ACTIONS;

   public:
	ActionsHub(const TextureHolder& textures, const FontHolder& fonts, const ColorHolder& colors);

	void draw(sf::RenderTarget& target, sf::RenderStates states) const override;
	bool update(sf::Time dt);
	bool handleEvent(const sf::Event& event);

	unsigned int getCurrentOption() const;
	void addOption(int option, const std::string& title, bool toggle,
	               const GUI::Button::Callback& callback);
	void packOptionGUI(int option, GUI::Component::Ptr component);
	void setCurrentOption(int option);
	void setOptionAction(int option, const std::function<void()>& action);

   private:
	const TextureHolder& mTextures;
	const FontHolder& mFonts;
	const ColorHolder& mColors;
	unsigned int mCurrentOption;
	GUI::Container mGUIContainer;
	std::vector<GUI::Container> mGUICommands;
	std::vector<std::function<void()>> mActions;
};

#endif  //DATAVISUALIZATION2_ACTIONSHUB_HPP

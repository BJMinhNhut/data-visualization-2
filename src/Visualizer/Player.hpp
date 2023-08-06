//
// Created by MINH NHUT on 8/6/2023.
//

#ifndef DATAVISUALIZATION2_PLAYER_HPP
#define DATAVISUALIZATION2_PLAYER_HPP

#include "GUI/Button.hpp"
#include "GUI/Container.hpp"
#include "Template/ColorHolder.hpp"
#include "Template/ResourceIdentifiers.hpp"

#include <SFML/Graphics/Drawable.hpp>
#include <SFML/Graphics/Transformable.hpp>
#include <SFML/System/NonCopyable.hpp>

#include <vector>

class Player : public sf::Drawable, public sf::Transformable, public sf::NonCopyable {
   public:
	Player(const TextureHolder& textures, const FontHolder& fonts, const ColorHolder& colors);

	void draw(sf::RenderTarget& target, sf::RenderStates states) const override;
	void update(sf::Time dt);
	void handleEvent(const sf::Event& event);

   private:
	const TextureHolder& mTextures;
	const FontHolder& mFonts;
	const ColorHolder& mColors;
	GUI::Container mGUIContainer;

	// Speed
	static const std::vector<std::pair<std::string, float>> mSpeedMap;
	int mSpeedID;
};

#endif  //DATAVISUALIZATION2_PLAYER_HPP

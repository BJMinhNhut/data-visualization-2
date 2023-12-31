//
// Created by MINH NHUT on 8/6/2023.
//

#ifndef DATAVISUALIZATION2_PLAYER_HPP
#define DATAVISUALIZATION2_PLAYER_HPP

#include "AnimationList.hpp"
#include "GUI/Button.hpp"
#include "GUI/CodeBlock.hpp"
#include "GUI/Console.hpp"
#include "GUI/Container.hpp"
#include "Template/ColorHolder.hpp"
#include "Template/ResourceIdentifiers.hpp"

#include <SFML/Graphics/Drawable.hpp>
#include <SFML/Graphics/Transformable.hpp>
#include <SFML/System/NonCopyable.hpp>

#include <vector>

class Player : public sf::Drawable, public sf::Transformable, public sf::NonCopyable {
   public:
	typedef std::shared_ptr<Player> Ptr;

   public:
	enum State { Play, Pause, Replay, numStates };

   public:
	Player(const TextureHolder& textures, const FontHolder& fonts, const ColorHolder& colors,
	       const std::function<void()>& playCallback);

	void draw(sf::RenderTarget& target, sf::RenderStates states) const override;
	void update(sf::Time dt);
	void handleEvent(const sf::Event& event);

	void reset();

	// Console functions
	void callError(const std::string& text);
	void callInfo(const std::string& text);
	void cleanLog();

	// Controller
	State getCurrentState() const;
	void loadAnimation(const std::vector<Animation>& list, const std::string& code);
	void play();
	void increaseSpeed();
	void decreaseSpeed();
	void hideAdjustButtons();

	bool hasAnimation() const;
	bool isPlaying() const;

   private:
	// GUI
	GUI::Container mGUIContainer, mAdjust;
	GUI::Console::Ptr mConsole;
	GUI::CodeBlock::Ptr mCodeBlock;
	GUI::Label::Ptr mSpeed;
	std::vector<GUI::Container> ControllerGUI;
	std::vector<GUI::Button::Ptr> playButtons;
	bool drawAdjust;

	// Animation
	AnimationList mAnimationList;
	static const std::vector<std::pair<std::string, float>> mSpeedMap;
	int mSpeedID;
};

#endif  //DATAVISUALIZATION2_PLAYER_HPP

//
// Created by MINH NHUT on 8/12/2023.
//

#ifndef DATAVISUALIZATION2_PROGRESSBAR_HPP
#define DATAVISUALIZATION2_PROGRESSBAR_HPP

#include "GUI/Component.hpp"
#include "Template/ColorHolder.hpp"
#include "Template/ResourceIdentifiers.hpp"

#include <SFML/Graphics/RectangleShape.hpp>

namespace GUI {
class ProgressBar : public Component {
   public:
	typedef std::shared_ptr<ProgressBar> Ptr;

   public:
	ProgressBar(const ColorHolder& colors, const sf::Vector2f& size);

	bool isSelectable() const override;

	void setLength(const int& length);
	void setProgress(const int& progress);

	void handleEvent(const sf::Event& event) override;

   private:
	void draw(sf::RenderTarget& target, sf::RenderStates states) const override;
	void updateBar();

   private:
	const sf::Vector2f mSize;
	int mLength;
	int mProgress;

	sf::RectangleShape mBar;
};
}  // namespace GUI

#endif  //DATAVISUALIZATION2_PROGRESSBAR_HPP

//
// Created by MINH NHUT on 8/4/2023.
//

#ifndef DATAVISUALIZATION2_CONSOLE_HPP
#define DATAVISUALIZATION2_CONSOLE_HPP

#include "GUI/Label.hpp"
#include "Template/ColorHolder.hpp"
#include "Template/ResourceIdentifiers.hpp"

namespace GUI {

class Console : public Label {
   public:
	enum LogType {
		Info,
		Error,
	};

	typedef std::shared_ptr<Console> Ptr;

   public:
	Console(const FontHolder& fonts, const ColorHolder& colors);
	void log(LogType type, const std::string& text);
	void clean();

	LogType getLogType() const;

   private:
	sf::Color getColorFromType(LogType type) const;

   private:
	LogType currentType;
	const sf::Color InfoColor;
	const sf::Color ErrorColor;
};

}  // namespace GUI

#endif  //DATAVISUALIZATION2_CONSOLE_HPP

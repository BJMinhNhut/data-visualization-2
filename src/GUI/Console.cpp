//
// Created by MINH NHUT on 8/4/2023.
//

#include "Console.hpp"
#include "Template/Constants.hpp"

#include <sstream>

namespace GUI {
Console::Console(const FontHolder& fonts, const ColorHolder& colors, const int& width)
    : Label(Mono, "", fonts, colors),
      currentType(Info),
      InfoColor(colors.get(Colors::Blue)),
      ErrorColor(colors.get(Colors::Red)),
      mWidth(width) {}

void Console::log(LogType type, std::string text) {

	if (type == Console::Info)
		text = "[INFO] " + text;
	else if (type == Console::Error)
		text = "[ERROR] " + text;
	setText(wrapText(text));

	currentType = type;
	setColor(getColorFromType(type));
}

void Console::clean() {
	setText("");
}

Console::LogType Console::getLogType() const {
	return currentType;
}

sf::Color Console::getColorFromType(LogType type) const {
	switch (type) {
		case Info:
			return InfoColor;
		case Error:
			return ErrorColor;
		default:
			return InfoColor;
	}
}

std::string Console::wrapText(const std::string& text) const {
	std::stringstream mStream(text);
	std::string word;
	std::string ans;
	unsigned int lineLength = 0;
	while (mStream >> word) {
		if (ans.length() > 0)
			word.insert(word.begin(), ' ');
		if (lineLength + word.length() <= mWidth) {
			lineLength += word.length();
			ans += word;
		} else {
			if (word[0] == ' ')
				word.erase(word.begin());
			ans += '\n' + word;
			lineLength = word.length();
		}
	}
	return ans;
}

}  // namespace GUI
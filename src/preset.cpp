#include "preset.h"

#include <vector>
#include <sstream>
#include <algorithm>

Preset::Preset()
	: mode_(Mode::Normal)
{
	regionsMap_.insert(std::pair<Region, std::pair<Color, Level>>(Region::Left, std::pair<Color, Level>(Color::White, Level::High)));
	regionsMap_.insert(std::pair<Region, std::pair<Color, Level>>(Region::Middle, std::pair<Color, Level>(Color::White, Level::High)));
	regionsMap_.insert(std::pair<Region, std::pair<Color, Level>>(Region::Right, std::pair<Color, Level>(Color::White, Level::High)));
}

Preset::Preset(const std::string& region)
	: mode_(Mode::Normal)
{
	regionsMap_.insert(std::pair<Region, std::pair<Color, Level>>(Region::Left, std::pair<Color, Level>(Color::White, Level::High)));
	regionsMap_.insert(std::pair<Region, std::pair<Color, Level>>(Region::Middle, std::pair<Color, Level>(Color::White, Level::High)));
	regionsMap_.insert(std::pair<Region, std::pair<Color, Level>>(Region::Right, std::pair<Color, Level>(Color::White, Level::High)));

	std::string copyRegion = region;
	std::transform(copyRegion.begin(), copyRegion.end(), copyRegion.begin(), ::tolower);

	std::vector<std::string> strings;
	std::istringstream f(copyRegion);
	std::string s;

	while (std::getline(f, s, ' '))
	{
		strings.push_back(s);

		if (strings.size() == 3)
		{
			Region region = regionFromString(strings.at(0));
			Color color = colorFromString(strings.at(1));
			Level level = levelFromString(strings.at(2));

			if (region != Region::Incorrect)
				regionsMap_[region] = std::pair<Color, Level>(color, level);

			strings.clear();
		}
	}
}

Preset::Region Preset::regionFromString(std::string region)
{
	if (region == std::string("left"))
		return Region::Left;
	else if (region == std::string("middle"))
		return Region::Middle;
	else if (region == std::string("right"))
		return Region::Right;

	return Region::Incorrect;
}

Preset::Color Preset::colorFromString(std::string color)
{
	if (color == std::string("off"))
		return Color::Off;
	else if (color == std::string("red"))
		return Color::Red;
	else if (color == std::string("orange"))
		return Color::Orange;
	else if (color == std::string("yellow"))
		return Color::Yellow;
	else if (color == std::string("green"))
		return Color::Green;
	else if (color == std::string("sky"))
		return Color::Sky;
	else if (color == std::string("blue"))
		return Color::Blue;
	else if (color == std::string("purple"))
		return Color::Purple;
	else if (color == std::string("white"))
		return Color::White;

	return Color::White;
}

Preset::Level Preset::levelFromString(std::string level)
{
	if (level == std::string("light"))
		return Level::Light;
	else if (level == std::string("low"))
		return Level::Low;
	else if (level == std::string("medium"))
		return Level::Medium;
	else if (level == std::string("high"))
		return Level::High;

	return Level::High;
}

Preset::Color Preset::color(Preset::Region region) const
{
	auto it = regionsMap_.find(region);

	if (it != regionsMap_.end())
		return it->second.first;
	else
		return Color::White;
}

void Preset::setColor(Preset::Region region, Preset::Color color)
{
	regionsMap_[region].first = color;
}

Preset::Level Preset::level(Preset::Region region) const
{
	auto it = regionsMap_.find(region);

	if (it != regionsMap_.end())
		return it->second.second;
	else
		return Level::High;
}

void Preset::setLevel(Preset::Region region, Preset::Level level)
{
	regionsMap_[region].second = level;
}

Preset::Mode Preset::mode() const
{
	return mode_;
}

void Preset::setMode(Preset::Mode mode)
{
	mode_ = mode;
}

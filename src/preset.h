#ifndef PRESET_H
#define PRESET_H

#include <map>
#include <string>
#include <iostream>

class Preset
{
public:
	enum class Region
	{
		Incorrect = 0,
		Left = 1,
		Middle = 2,
		Right = 3
	};

	enum class Mode
	{
		Incorrect = 0,
		Normal = 1,
		Gaming = 2,
		Breathe = 3,
		Demo = 4,
		Wave = 5
	};

	enum class Color
	{
		Off = 0,
		Red = 1,
		Orange = 2,
		Yellow = 3,
		Green = 4,
		Sky = 5,
		Blue = 6,
		Purple = 7,
		White = 8
	};

	// levels of illumination
	enum class Level
	{
		Light = 3,
		Low = 2,
		Medium = 1,
		High = 0
	};

	Preset();
	Preset(const std::string& region);

	Region regionFromString(std::string region);
	Color colorFromString(std::string color);
	Level levelFromString(std::string level);

	Color color(Region region) const;
	void setColor(Region region, Color color);

	Level level(Region region) const;
	void setLevel(Region region, Level level);

	Mode mode() const;
	void setMode(Mode mode);

	friend std::ostream& operator<<(std::ostream& os, const Preset& obj)
	{
		os << static_cast<int>(Region::Left) << " " << static_cast<int>(obj.color(Region::Left)) << " " << static_cast<int>(obj.level(Region::Left)) << " ";
		os << static_cast<int>(Region::Middle) << " " << static_cast<int>(obj.color(Region::Middle)) << " " << static_cast<int>(obj.level(Region::Middle)) << " ";
		os << static_cast<int>(Region::Right) << " " << static_cast<int>(obj.color(Region::Right)) << " " << static_cast<int>(obj.level(Region::Right)) << " ";
		os << static_cast<int>(obj.mode());
		return os;
	}
	friend std::istream& operator>>(std::istream& is, Preset& obj)
	{

		int region;
		int color;
		int level;

		for (int i = 0; i < 3; i++)
		{
			is >> region;
			is >> color;
			is >> level;


			obj.setColor(static_cast<Region>(region), static_cast<Color>(color));
			obj.setLevel(static_cast<Region>(region), static_cast<Level>(level));
		}

		int mode;

		is >> mode;

		obj.setMode(static_cast<Mode>(mode));

		return is;
	}

private:
	std::map<Region, std::pair<Color, Level>> regionsMap_;
	Mode mode_;
};

#endif // PRESET_H

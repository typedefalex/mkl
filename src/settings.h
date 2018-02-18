#ifndef SETTINGS_H
#define SETTINGS_H

#include <iostream>

#include "preset.h"

class Settings
{
public:
	Settings(std::string directory, std::string fileName);

	Preset loadPreset() const;
	void savePreset(const Preset& preset);

private:
	std::string settingsPath_;
};

#endif // SETTINGS_H

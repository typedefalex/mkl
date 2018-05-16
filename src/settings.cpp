#include "settings.h"

#include <fstream>

Settings::Settings(std::string directory, std::string fileName)
{
	settingsPath_ = directory + std::string("/") + fileName;

	std::string command = std::string("mkdir -p ") + directory;
	const int returnCode = system(command.c_str());

	if (returnCode != 0)
		std::cout << "Can't create directory. Use default preset." << std::endl;
	else
	{
        std::ifstream presetFile(settingsPath_, std::ifstream::out);

		presetFile.close();
	}
}

void Settings::savePreset(const Preset& preset)
{
    std::cout << "Unable to open filedf" <<settingsPath_ << std::endl;

	std::ofstream myfile (settingsPath_, std::ios_base::trunc);

	if (myfile.is_open())
	{
		myfile << preset << std::endl;
		myfile.close();
	}
	else
		std::cout << "Unable to open file" << std::endl;
}

Preset Settings::loadPreset() const
{
	std::ifstream presetFile(settingsPath_, std::ifstream::in);
	Preset preset;

	if (presetFile.is_open())
	{
		if (!(presetFile >> preset))
			preset = Preset();
	}
	else
        std::cout << "Can't open file. Load default preset." << std::endl;

	presetFile.close();

	return preset;
}

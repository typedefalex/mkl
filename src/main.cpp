#include <cstdlib>
#include <fstream>
#include <iostream>

#include "preset.h"
#include "settings.h"
#include "hidmanager.h"

int main(int argc, char* argv[])
{
	std::string settingsDir("/etc/mkl");
	std::string settingsFile("preset.conf");

	Settings settings(settingsDir, settingsFile);
	Preset settingPreset = settings.loadPreset();

	HidManager hidManager;

	if (argc == 1)
	{
		hidManager.setPreset(settingPreset);
		exit(0);
	}

	std::string str;

	for (int i = 1; i < argc; i++)
	{
		str += argv[i];
		str += " ";
	}

	Preset nowPreset = Preset(std::string(str));
	HidManager().setPreset(nowPreset);

	settings.savePreset(nowPreset);

	return 0;
}

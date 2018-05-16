#include <pwd.h>
#include <unistd.h>
#include <sys/types.h>

#include <sstream>

#include "preset.h"
#include "settings.h"
#include "hidmanager.h"

int main(int argc, char* argv[])
{
    const struct passwd* passwd = getpwuid(getuid());

    std::ostringstream stringStream;
    stringStream << "/home/" << passwd->pw_name << "/.config";

    std::string settingsDir = stringStream.str();
    std::string settingsFile("mkl.conf");

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

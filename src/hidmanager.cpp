#include "hidmanager.h"

#include <iostream>

HidManager::HidManager()
{

}

void HidManager::setPreset(const Preset& preset)
{
	if (hid_init())
	{
        std::cout << "Failed to initialize HIDAPI." << std::endl;
        return;
	}

    hid_device* msiKeyboard = hid_open(0x1770, 0xff00, 0);

    if (!msiKeyboard)
	{
        std::cout << "Error opening the device." << std::endl;
		hid_exit();
		return;
	}

    sendColor(msiKeyboard, preset, Preset::Region::Left);
    sendColor(msiKeyboard, preset, Preset::Region::Middle);
    sendColor(msiKeyboard, preset, Preset::Region::Right);

    sendMode(msiKeyboard, Preset::Mode::Normal);

    hid_close(msiKeyboard);
	hid_exit();
}

void HidManager::sendColor(hid_device* msiKeyboard, const Preset& preset, Preset::Region region)
{
	unsigned char activate[8];

	activate[0] = 1;
	activate[1] = 2;
	activate[2] = 66; // set
	activate[3] = (unsigned char) region;
	activate[4] = (unsigned char) preset.color(region);
	activate[5] = (unsigned char) preset.level(region);
	activate[6] = 0;
	activate[7] = 236; // EOR (end of request)

    hid_send_feature_report(msiKeyboard, activate, 8);
}

void HidManager::sendMode(hid_device *msiKeyboard, Preset::Mode mode)
{
	unsigned char commit[8];

	commit[0] = 1;
	commit[1] = 2;
	commit[2] = 65; // commit
	commit[3] = (unsigned char) mode; // set hardware mode
	commit[4] = 0;
	commit[5] = 0;
	commit[6] = 0;
	commit[7] = 236; // EOR

    hid_send_feature_report(msiKeyboard, commit, 8);
}

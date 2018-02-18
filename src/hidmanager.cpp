#include "hidmanager.h"

#include <iostream>

HidManager::HidManager()
{

}

void HidManager::setPreset(const Preset& preset)
{
	if (hid_init())
	{
		//qDebug() << QString("Failed to initialize HIDAPI.");
		exit(0);
	}

	msiKeyboard_ = hid_open(0x1770, 0xff00, 0);

	if (!msiKeyboard_)
	{
		hid_exit();
		std::cout << "Hesdfsdfld!" << std::endl;
		//qDebug() << QString("Error opening the device!\n");
		return;
	}

	sendColor(preset, Preset::Region::Left);
	sendColor(preset, Preset::Region::Middle);
	sendColor(preset, Preset::Region::Right);

	sendMode(Preset::Mode::Normal);

	hid_close(msiKeyboard_);
	hid_exit();
}

void HidManager::sendColor(const Preset& preset, Preset::Region region)
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

	hid_send_feature_report(msiKeyboard_, activate, 8);
}

void HidManager::sendMode(Preset::Mode mode)
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

	hid_send_feature_report(msiKeyboard_, commit, 8);
}

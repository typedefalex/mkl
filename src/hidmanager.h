#ifndef HIDMANAGER_H
#define HIDMANAGER_H

#include "preset.h"
#include <hidapi/hidapi.h>

class HidManager
{
public:
	HidManager();

	void setPreset(const Preset& preset);

private:
	hid_device * msiKeyboard_;

	void sendColor(const Preset& preset, Preset::Region region);
	void sendMode(Preset::Mode mode);
};

#endif // HIDMANAGER_H

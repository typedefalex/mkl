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
    void sendColor(hid_device *msiKeyboard, const Preset& preset, Preset::Region region);
    void sendMode(hid_device* msiKeyboard, Preset::Mode mode);
};

#endif // HIDMANAGER_H

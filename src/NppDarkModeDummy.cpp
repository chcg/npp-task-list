#include "NppDarkMode.h"
#include "PluginInterface.h"

extern NppData nppData;

namespace NppDarkMode
{
	bool isEnabled()
	{
		return ::SendMessage(nppData._nppHandle, NPPM_ISDARKMODEENABLED, 0, 0);
	}

	HBRUSH getDarkerBackgroundBrush()
	{
		return ::CreateSolidBrush(HEXRGB(0x202020));
	}

	COLORREF getDarkerTextColor()
	{
		return HEXRGB(0xC0C0C0);
	}

	COLORREF getLinkTextColor()
	{
		return HEXRGB(0xFFFF00);
	}

	void setDarkTitleBar(HWND /*hwnd*/)
	{
	}
}

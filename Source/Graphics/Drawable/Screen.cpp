#include <DxLib.h>
#include "Screen.h"

class BackScreen :
	public Screen
{
public:
	BackScreen() :
		Screen(DX_SCREEN_BACK)
	{
	}

	~BackScreen() override
	{
		handle_ = -1;
	}
};

Screen::Screen(int x, int y, bool transFlg) :
	Screen(MakeScreen(x, y, transFlg))
{
}

Screen& Screen::GetBackScreen(void)
{
	static BackScreen backScreen;
	return backScreen;
}

void Screen::Flip(void)
{
	ScreenFlip();
}

void Screen::Setup(void) const
{
	SetDrawScreen(handle_);
}

void Screen::Clear(void)
{
	if (handle_ != GetDrawScreen())
	{
		Setup();
	}
	ClsDrawScreen();
}

Screen::Screen(int handle) :
	Image(handle)
{
}

#include <DxLib.h>
#include "Screen.h"

class BackScreen final:
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
	Image(MakeScreen(x, y, transFlg))
{
}

const Screen& Screen::GetBackScreen(void)
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

void Screen::Clear(void) const
{
	if (handle_ != GetDrawScreen())
	{
		Setup();
	}
	ClsDrawScreen();
}

Screen::Screen(Screen&& screen) noexcept:
	Image(screen.handle_)
{
	screen.handle_ = -1;
}

Screen& Screen::operator=(Screen&& screen) noexcept
{
	handle_ = screen.handle_;
	screen.handle_ = -1;
	return *this;
}

Screen::Screen(int handle) :
	Image(handle)
{
}

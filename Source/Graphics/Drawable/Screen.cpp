#include <array>
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

ScreenPtr Screen::Create(void)
{
	int x = 0;
	int y = 0;
	GetBackScreen().GetScreenSize(x, y);
	return Create(x, y, true);
}

ScreenPtr Screen::Create(int x, int y, bool transFlg)
{
	return ScreenPtr(new Screen(x, y, transFlg));
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

void Screen::GetScreenSize(int& x, int& y) const
{
	GetGraphSize(handle_, &x, &y);
}

void Screen::GetScreenSize(float& x, float& y) const
{
	GetGraphSizeF(handle_, &x, &y);
}

void Screen::Setup(void) const
{
	SetDrawScreen(handle_);
}

void Screen::Setup(int index) const
{
	SetRenderTargetToShader(index, handle_);
}

void Screen::Clear(void) const
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

Screen::Screen(int x, int y, bool transFlg) :
	Image(MakeScreen(x, y, transFlg))
{
}

#pragma once
#include "Image.h"

class Screen :
	public Image
{
public:
	Screen(int x, int y, bool transFlg);
	~Screen() override = default;

	static const Screen& GetBackScreen(void);
	static void Flip(void);

	void Setup(void) const;

	void Clear(void) const;

	Screen(const Screen&) = delete;
	Screen& operator=(const Screen&) = delete;

	Screen(Screen&& screen) noexcept;
	Screen& operator=(Screen&& screen) noexcept;

protected:
	Screen(int handle);

};

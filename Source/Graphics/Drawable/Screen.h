#pragma once
#include "Image.h"

class Screen :
	public Image
{
public:
	Screen(int x, int y, bool transFlg);
	~Screen() override = default;

	static Screen& GetBackScreen(void);
	static void Flip(void);

	void Setup(void) const;

	void Clear(void);

	Screen(const Screen&) = delete;
	Screen& operator=(const Screen&) = delete;

	Screen(Screen&&) = default;
	Screen& operator=(Screen&&) = default;

protected:
	Screen(int handle);

};

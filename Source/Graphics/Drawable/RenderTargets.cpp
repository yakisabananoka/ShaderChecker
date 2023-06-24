#include <ranges>
#include "RenderTargets.h"
#include "Graphics/Drawable/Screen.h"

RenderTargetsPtr RenderTargets::Create(void)
{
	return RenderTargetsPtr(new RenderTargets());
}

RenderTargetsPtr RenderTargets::Create(unsigned int num)
{
	Screens screens;
	for (unsigned i = 0; i < num; i++)
	{
		screens.emplace_back(Screen::Create());
	}
	return Create(std::move(screens));
}

RenderTargetsPtr RenderTargets::Create(Screens&& screens)
{
	return RenderTargetsPtr(new RenderTargets(std::move(screens)));
}

bool RenderTargets::IsAbleToSetupAsMultiRenderTarget(void) const
{
	return GetMultiDrawScreenNum() >= static_cast<int>(screens_.size());
}

const ScreenPtr& RenderTargets::Get(unsigned int index) const
{
	return screens_[index];
}

ScreenPtr& RenderTargets::Get(unsigned int index)
{
	return screens_[index];
}

void RenderTargets::Add(ScreenPtr screenPtr)
{
	screens_.emplace_back(std::move(screenPtr));
}

void RenderTargets::Erase(void)
{
	screens_.resize(0);
}

void RenderTargets::Remove(void)
{
	std::erase_if(screens_, [](const ScreenPtr& screen) { return !screen; });
}

void RenderTargets::Clear(void) const
{
	for (const auto& screen : screens_)
	{
		if (!screen)
		{
			continue;
		}

		screen->Clear();
	}
}

void RenderTargets::Begin(void) const
{
	//設定されたスクリーンの取り出し
	for (int i = 0; const auto & ptr : screens_)
	{
		//レンダーターゲットの設定
		ptr->Setup(i);
		i++;
	}
}

void RenderTargets::End(void) const
{
	//全レンダーターゲットの解除
	const int size = static_cast<int>(screens_.size());
	for (int i = 0; i < size; i++)
	{
		SetRenderTargetToShader(i, -1);
	}
}

size_t RenderTargets::GetSize(void) const
{
	return screens_.size();
}

void RenderTargets::operator+=(ScreenPtr screenPtr)
{
	Add(std::move(screenPtr));
}

const ScreenPtr& RenderTargets::operator[](unsigned int index) const
{
	return Get(index);
}

ScreenPtr& RenderTargets::operator[](unsigned int index)
{
	return Get(index);
}

RenderTargets::RenderTargets() = default;

RenderTargets::RenderTargets(Screens&& screens) :
	screens_(std::move(screens))
{
}

ScreenPtr* begin(RenderTargets& renderTargets)
{
	return &renderTargets[0];
}

ScreenPtr* end(RenderTargets& renderTargets)
{
	return std::next(&renderTargets[static_cast<unsigned int>(renderTargets.GetSize() - 1)]);
}

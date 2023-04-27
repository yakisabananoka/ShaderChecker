#include "StopWatch.h"

constexpr float NANO_DIV = 1000000000.f;		//ナノ秒から秒に変換するための定数

StopWatch::StopWatch() :
	elapsed_(0.0f)
{
}

void StopWatch::Start(void)
{
	//既にスタートしていない場合にスタートする
	if (!start_)
	{
		start_ = std::chrono::system_clock::now();
	}
}

void StopWatch::Stop(void)
{
	elapsed_ += GetNowCount();		//今までの経過時間を記録
	start_ = std::nullopt;			//開始時間を削除
}

void StopWatch::Reset(void)
{
	elapsed_ = 0.0f;				//経過時間を削除
	start_ = std::nullopt;			//開始時間を削除
}

float StopWatch::GetNowCount(void) const
{
	//開始していない場合は今までの経過時間を返す
	if (!start_)
	{
		return elapsed_;
	}

	//過去の経過時間と今までの経過時間を足して返す
	return elapsed_ + static_cast<float>(std::chrono::duration_cast<std::chrono::nanoseconds>(std::chrono::system_clock::now() - *start_).count()) / NANO_DIV;
}

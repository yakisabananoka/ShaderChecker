#pragma once
#include <chrono>
#include <optional>

class StopWatch
{
public:
	StopWatch();
	~StopWatch() = default;

	/// @brief 計測開始
	void Start(void);

	/// @brief 計測終了
	void Stop(void);

	/// @brief リセット
	void Reset(void);

	/// @brief 現在の経過時間を取得
	/// @return 経過時間(秒)
	float GetNowCount(void)const;

	StopWatch(const StopWatch&) = default;
	StopWatch& operator=(const StopWatch&) = default;

	StopWatch(StopWatch&&) = default;
	StopWatch& operator=(StopWatch&&) = default;
private:
	std::optional<std::chrono::system_clock::time_point> start_;		//計測開始時間
	float elapsed_;		//過去の経過時間
};


#pragma once

/// @brief アプリケーション
class Application
{
public:
	Application() = default;
	~Application() = default;

	/// @brief 実行
	/// @return true:成功 false:失敗
	bool Run(void);

	Application(const Application&) = delete;
	Application& operator=(const Application&) = delete;

	Application(Application&&) = default;
	Application& operator=(Application&&) = default;

private:
	/// @brief 初期化
	/// @return true:成功 false:失敗
	bool Initialize(void);

	/// @brief 更新
	void Update(void);
};

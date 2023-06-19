#pragma once
#include "Image.h"

/// @brief スクリーン
class Screen :
	public Image
{
public:
	/// @brief バックスクリーンと同じ大きさでスクリーンを生成
	/// @return スクリーン
	static ScreenPtr Create(void);

	/// @brief スクリーンを生成
	/// @param x 横の大きさ
	/// @param y 縦の大きさ
	/// @param transFlg 透過するか(true:する false:しない)
	/// @return スクリーン
	static ScreenPtr Create(int x, int y, bool transFlg);

	/// @brief バックスクリーンの参照を取得
	/// @return バックスクリーン
	static const Screen& GetBackScreen(void);

	/// @brief 前画面と後画面でスクリーンの入れ替え
	static void Flip(void);

	/// @brief デストラクタ
	~Screen() override = default;

	/// @brief スクリーンサイズの取得
	/// @param x 横の大きさ
	/// @param y 縦の大きさ
	void GetScreenSize(int& x, int& y) const;

	/// @brief 描画対象に設定
	void Setup(void) const;

	/// @brief シェーダー使用時のマルチレンダーターゲットとして描画対象に設定
	/// @param index 出力先の番号
	/// @param releaseFlg 設定を解除するか
	void Setup(int index, bool releaseFlg = false) const;

	/// @brief スクリーンの初期化
	void Clear(void) const;

	Screen(const Screen&) = delete;
	Screen& operator=(const Screen&) = delete;

	Screen(Screen&& screen) = delete;
	Screen& operator=(Screen&& screen) = delete;

protected:
	Screen(int handle);

private:
	Screen(int x, int y, bool transFlg);
};

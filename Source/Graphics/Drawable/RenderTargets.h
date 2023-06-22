#pragma once
#include <vector>
#include <functional>
#include "Graphics/UsingGraphics.h"

/// @brief 複数のレンダーターゲットを管理
class RenderTargets
{
public:
	using Screens = std::vector<ScreenPtr>;		//スクリーンの配列型

	/// @brief 生成関数
	/// @return レンダーターゲット管理オブジェクト
	static RenderTargetsPtr Create(void);

	/// @brief 生成関数
	/// @param num デフォルト生成で保持するスクリーンの数
	/// @return レンダーターゲットの管理オブジェクト
	static RenderTargetsPtr Create(unsigned int num);

	/// @brief 生成関数
	/// @param screens スクリーンの配列
	/// @return レンダーターゲット管理オブジェクト
	static RenderTargetsPtr Create(Screens&& screens);

	/// @brief マルチレンダーターゲットとして設定可能か
	/// @return true:可 false:不可
	bool IsAbleToSetupAsMultiRenderTarget(void) const;

	/// @brief スクリーンの取得
	/// @param index インデックス
	/// @return スクリーン
	const ScreenPtr& Get(unsigned int index) const;

	/// @brief スクリーンの取得(constなし)
	/// @param index インデックス
	/// @return スクリーン
	ScreenPtr& Get(unsigned int index);

	/// @brief スクリーンの追加
	/// @param screenPtr スクリーン
	void Add(ScreenPtr screenPtr);

	/// @brief 全削除
	void Erase(void);

	/// @brief nullptrが入っているスクリーンを除去
	void Remove(void);

	/// @brief 各スクリーンに対して任意の関数を実行
	/// @param func 任意の関数(返り値：trueで続行、falseで途中終了 第一引数：スクリーンの参照 第二引数：インデックス)
	void Visit(std::function<bool(ScreenPtr&, unsigned int)> func);

	/// @brief 全スクリーンを初期化
	void Clear(void) const;

	/// @brief 開始処理
	void Begin(void) const;

	/// @brief 終了処理
	void End(void) const;

	/// @brief 保持しているスクリーン数
	/// @return スクリーン数
	size_t GetSize(void) const;

	/// @brief 範囲for文用begin
	/// @return 先頭のスクリーンのポインタ
	ScreenPtr* begin(void);

	/// @brief 範囲for文用のend
	/// @return 最後の次のスクリーンのポインタ
	ScreenPtr* end(void);

	void operator+=(ScreenPtr screenPtr);

	const ScreenPtr& operator[](unsigned int index) const;

	ScreenPtr& operator[](unsigned int index);
private:
	/// @brief コンストラクタ
	RenderTargets();

	/// @brief コンストラクタ
	/// @param screens スクリーンの配列
	RenderTargets(Screens&& screens);

	Screens screens_;		//スクリーンの配列
};

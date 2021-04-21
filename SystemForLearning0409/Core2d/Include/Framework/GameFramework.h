#pragma once
#ifndef __GAMEFTAMEWORK_HEADER__
#define __GAMEFTAMEWORK_HEADER__

#ifdef CORE2D_EXPORTS
#define CORE2D_GAMEFPAMEWORK_CLASS __declspec(dllexport)
#else
#define CORE2D_GAMEFPAMEWORK_CLASS __declspec(dllimport)
#endif

#include <Windows.h>

namespace core2d
{

	class CORE2D_GAMEFPAMEWORK_CLASS GameFramework
	{
	public:
		// デフォルトのコンストラクタを呼び出し不可に
		GameFramework(void) = delete;
		GameFramework(unsigned int fps);
	protected:
		virtual ~GameFramework(void);

	public:
		// システムとゲームの初期化呼び出し
		bool initialize(HWND hwnd);
		// システムとゲームの終了処理呼び出し
		void finalize(void);
		// システムとゲームの更新処理呼び出し
		void step(void);

		// 画面サイズを取得
		float getDisplayWidth(void);
		float getDisplayHeight(void);

	private:
		// ユーザー定義のゲーム初期化処理
		virtual bool initializeGame(void) = 0;
		// ユーザー定義のゲーム終了処理
		virtual void finalizeGame(void) = 0;
		// ユーザー定義のゲーム更新処理
		virtual void updateGame(void) = 0;

	protected:
		GameFramework(const GameFramework&) = delete;
		GameFramework& operator=(const GameFramework&) = delete;

	private:
		class Impl;
		Impl* m_impl;

	};

}

#endif // __GAMEFTAMEWORK_HEADER__
#pragma once
#ifndef __CORE2D_GRAPHICSCORE_HEADER__
#define __CORE2D_GRAPHICSCORE_HEADER__

#ifdef CORE2D_EXPORTS
#define CORE2D_GRAPHICSCORE_CLASS __declspec(dllexport)
#else
#define CORE2D_GRAPHICSCORE_CLASS __declspec(dllimport)
#endif

struct ID3D11Device3;
struct ID3D11DeviceContext3;
struct IDXGISwapChain3;

namespace core2d
{

	// 前方宣言
	class GraphicsResourceManager;

	// シングルトンクラス
	class CORE2D_GRAPHICSCORE_CLASS GraphicsCore
	{
	public:
		// コアの初期化
		static bool initialize(HWND hwnd);
		// コアの終了処理
		static void finalize(void);
		// インスタンスの取得
		static GraphicsCore* get(void);

	private:
		GraphicsCore(void);
		~GraphicsCore(void);

		// 初期化処理を実行します
		bool initializeImpl(HWND hwnd);
		// 終了処理を実行します
		void finalizeImpl();

	public:
		// バックバッファをクリアします
		void clear();
		// 画面のフリップを行います
		void present();

	public:
		ID3D11Device3* getDevice();				// デバイスを取得
		ID3D11DeviceContext3* getContext();		// 3D描画コンテキストを取得
		IDXGISwapChain3* getSwapChain();		// スワップチェインを取得
		GraphicsResourceManager* getGraphicsResourceManager();	// リソース管理クラスを取得

		unsigned int getWindowWidth();		// ウインドウの幅を取得
		unsigned int getWindowHeight();		// ウインドウの高さを取得

	private:
		//コピー禁止
		GraphicsCore(const GraphicsCore&) = delete;
		GraphicsCore& operator=(const GraphicsCore&) = delete;

	private:
		class Impl;
		Impl* m_impl;

	};

} // core2d

#endif // __CORE2D_GRAPHICSCORE_HEADER__
#pragma once
#ifndef __CORE2D_GRAPHICSSYSTEM_HEADER__
#define __CORE2D_GRAPHICSSYSTEM_HEADER__

#ifdef CORE2D_EXPORTS
#define CORE2D_GRAPHICSSYSTEM_CLASS	__declspec(dllexport)
#else
#define CORE2D_GRAPHICSSYSTEM_CLASS	__declspec(dllimport)
#endif

namespace core2d
{

	class DrawObject;

	// 描画システムのシングルトンクラス
	class CORE2D_GRAPHICSSYSTEM_CLASS GraphicsSystem
	{
	public:
		// インスタンスを返します
		static GraphicsSystem* getInst();
		// 初期化処理
		static bool initialize();
		// 終了処理
		static void finalize();
		// システムの有効性確認
		static bool isValid();

	private:
		GraphicsSystem();
		~GraphicsSystem();

		// システムの初期化処理
		bool initializeImpl();
		// システムの終了処理
		void finalizeImpl();

	private:
		//コピー禁止
		GraphicsSystem(const GraphicsSystem&) = delete;
		GraphicsSystem& operator=(const GraphicsSystem&) = delete;

	public:
		// 描画物をシステムに登録します
		void registerDrawObject(DrawObject* object);

		// 描画処理を発行します
		bool render();

	private:
		class Impl;
		Impl* m_impl;

	};

}

#endif // __CORE2D_GRAPHICSSYSTEM_HEADER__
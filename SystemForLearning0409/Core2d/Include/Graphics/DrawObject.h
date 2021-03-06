#pragma once
#ifndef __CORE2D_DRAWOBJECT_HEADER__
#define __CORE2D_DRAWOBJECT_HEADER__

#ifdef CORE2D_EXPORTS
#define CORE2D_DRAWOBJECT_CLASS	__declspec(dllexport)
#else
#define CORE2D_DRAWOBJECT_CLASS	__declspec(dllimport)
#endif

namespace core2d
{
	// 前方宣言
	class Camera;

	// 描画物の基底クラス
	class CORE2D_DRAWOBJECT_CLASS DrawObject
	{
	protected:
		DrawObject();
		virtual ~DrawObject();

		// 継承先で描画処理の中身を記述
		virtual bool render(Camera* camera) = 0;

	public:
		// 生成番号を取得
		unsigned long long getGenNo(void);
		// 描画優先度を設定
		void setPriority(unsigned int priority);
		// 描画優先度を取得
		unsigned int getPriority(void);
		// 描画実行フラグを設定
		void setActive(bool flag = true);
		// 描画実行の状態を取得
		bool isActive(void);
		// 破棄を予約
		void reserveDestroy(void);
		// 破棄が予約されているかを取得
		bool isReservedDestroy(void);

	protected:
		// 比較関数
		static bool compare(DrawObject* lhs, DrawObject* rhs);

		// Z座標を取得
		float getZ(void);

		// コピー禁止
		DrawObject(const DrawObject&) = delete;
		DrawObject& operator=(const DrawObject&) = delete;

	private:
		class Impl;
		Impl* m_impl;

		friend class GraphicsSystem;
	};

}

#endif // __CORE2D_DRAWOBJECT_HEADER__
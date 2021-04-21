#pragma once
#ifndef __CORE2D_PRIMITIVEEDGESPRITE_HEADER__
#define __CORE2D_PRIMITIVEEDGESPRITE_HEADER__

#ifdef CORE2D_EXPORTS
#define CORE2D_PRIMITIVEEDGESPRITE_CLASS __declspec(dllexport)
#else
#define CORE2D_PRIMITIVEEDGESPRITE_CLASS __declspec(dllimport)
#endif

#include "DrawObject.h"

namespace core2d
{
	// 輪郭表示スプライトの基底クラス
	class CORE2D_PRIMITIVEEDGESPRITE_CLASS PrimitiveEdgeSprite : public DrawObject
	{
	public:
		// 破棄
		static void destroy(PrimitiveEdgeSprite* p);

	protected:
		PrimitiveEdgeSprite(void);
		virtual ~PrimitiveEdgeSprite(void);

	public:
		// 表示パラメータ設定
		virtual void setPosition(float x, float y);
		virtual void setScale(float x, float y);
		virtual void setRotation(float degree);
		virtual void setColor(float r, float g, float b, float a = 1.0f);

	private:
		//コピー禁止
		PrimitiveEdgeSprite(const PrimitiveEdgeSprite&) = delete;
		PrimitiveEdgeSprite& operator=(const PrimitiveEdgeSprite&) = delete;

	};

	// 円の輪郭線を描くクラス
	class CORE2D_PRIMITIVEEDGESPRITE_CLASS CircleEdgeSprite : public PrimitiveEdgeSprite
	{
	public:
		// 破棄
		static void destroy(CircleEdgeSprite* p);

		// 指定した半径で作成
		CircleEdgeSprite(float radius);

	private:
		virtual ~CircleEdgeSprite(void);

		bool render(Camera* camera) final;

	public:
		// 表示パラメータ設定
		void setPosition(float x, float y) final;
		void setScale(float x, float y) final;
		void setRotation(float degree) final;
		void setColor(float r, float g, float b, float a = 1.0f) final;

		// 半径を取得
		float getRadius(void);

	private:
		// デフォルトコンストラクタ呼び出し禁止
		CircleEdgeSprite() = delete;
		//コピー禁止
		CircleEdgeSprite(const CircleEdgeSprite&) = delete;
		CircleEdgeSprite& operator=(const CircleEdgeSprite&) = delete;

	private:
		class Impl;
		Impl* m_impl;

	};

	// 四角の輪郭線を描くクラス
	class CORE2D_PRIMITIVEEDGESPRITE_CLASS BoxEdgeSprite : public PrimitiveEdgeSprite
	{
	public:
		// 破棄
		static void destroy(BoxEdgeSprite* p);

		// 指定した幅と高さの四角を作成
		BoxEdgeSprite(float width, float height);

	private:
		virtual ~BoxEdgeSprite(void);

		bool render(Camera* camera) final;

	public:
		// 表示パラメータ設定
		void setPosition(float x, float y) final;
		void setScale(float x, float y) final;
		void setRotation(float degree) final;
		void setColor(float r, float g, float b, float a = 1.0f) final;

		// 幅と高さを取得
		float getWidth(void);
		float getHeight(void);

	private:
		// デフォルトコンストラクタ呼び出し禁止
		BoxEdgeSprite() = delete;
		//コピー禁止
		BoxEdgeSprite(const BoxEdgeSprite&) = delete;
		BoxEdgeSprite& operator=(const BoxEdgeSprite&) = delete;

	private:
		class Impl;
		Impl* m_impl;

	};

	// 線分を描くクラス
	class CORE2D_PRIMITIVEEDGESPRITE_CLASS LineSprite : public PrimitiveEdgeSprite
	{
	public:
		// 破棄
		static void destroy(LineSprite* p);
		// startとendを結ぶ線分を作成
		LineSprite(float startX, float startY, float endX, float endY);

	private:
		virtual ~LineSprite(void);

		bool render(Camera* camera) final;

	public:
		// 表示パラメータ設定
		void setPosition(float x, float y) final;
		void setScale(float x, float y) final;
		void setRotation(float degree) final;
		void setColor(float r, float g, float b, float a = 1.0f) final;

		// 線分を設定
		void setLine(float startX, float startY, float endX, float endY);
		void setStartPosition(float x, float y);
		void setEndPosition(float x, float y);

	private:
		// デフォルトコンストラクタ呼び出し禁止
		LineSprite() = delete;
		//コピー禁止
		LineSprite(const LineSprite&) = delete;
		LineSprite& operator=(const LineSprite&) = delete;

	private:
		class Impl;
		Impl* m_impl;

	};

	// 点を描くクラス
	class CORE2D_PRIMITIVEEDGESPRITE_CLASS PointSprite : public PrimitiveEdgeSprite
	{
	public:
		// 破棄
		static void destroy(PointSprite* p);

		PointSprite(float x, float y);

	private:
		virtual ~PointSprite(void);

		bool render(Camera* camera) final;

	public:
		// 表示パラメータ設定
		void setPosition(float x, float y) final;
		void setColor(float r, float g, float b, float a = 1.0f) final;

	private:
		// デフォルトコンストラクタ呼び出し禁止
		PointSprite() = delete;
		//コピー禁止
		PointSprite(const PointSprite&) = delete;
		PointSprite& operator=(const PointSprite&) = delete;

	private:
		class Impl;
		Impl* m_impl;

	};

}

#endif
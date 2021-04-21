#pragma once

#ifndef __COLLISION_H__
#define __COLLISION_H__

#ifdef CORE2D_EXPORTS
#define CORE2D_COLLISION_CLASS __declspec(dllexport)
#else
#define CORE2D_COLLISION_CLASS __declspec(dllimport)
#endif

namespace core2d
{
	namespace Collision
	{

		//
		//コリジョンタグ
		//
		enum class CollisionTag
		{
			None,

			Point,			//点
			SimpleRect,		//単純矩形
			Line,			//線
			Circle,			//円
			Rect,			//回転矩形
		};

		//
		//コリジョン規定クラス
		//
		class CORE2D_COLLISION_CLASS CollisionBase
		{
		public:
			CollisionBase() { m_Tag = CollisionTag::None; m_Number = 0; m_Active = true; }
			explicit CollisionBase(CollisionTag tag) { m_Tag = tag; m_Number = 0; m_Active = true; }

			//タグの取得
			const CollisionTag getTag() const { return m_Tag; } 

			//識別用の番号
			const unsigned int getNumber() { return m_Number; }
			void setNumber(unsigned int number) { m_Number = number; }

			//有効・無効フラグ
			void setActive(bool active) { m_Active = active; }
			bool isActive() { return m_Active; }

			virtual ~CollisionBase(){};

		private:
			CollisionTag m_Tag;
			unsigned int m_Number;

			bool m_Active;
		};


		//
		//点
		//
		struct CORE2D_COLLISION_CLASS PointF : public CollisionBase
		{

			PointF():CollisionBase(CollisionTag::Point), x(0), y(0) {}

			PointF(float _x, float _y) :CollisionBase(CollisionTag::Point)
			{
				x = _x;
				y = _y;
			}

			float x;
			float y;
		};

		//
		//単純矩形
		// 移動のみ
		// 回転、スケールの対応は無いが、処理は少し早い
		//
		struct CORE2D_COLLISION_CLASS SimpleRectF : public CollisionBase
		{
			SimpleRectF():CollisionBase(CollisionTag::SimpleRect), leftTop(), rightBottom(){}

			//float left;		//左上端のx座標
			//float top;		//左上端のy座標
			//float right;		//右下端のx座標
			//float bottom;		//右下端のy座標
			SimpleRectF(float left, float top, float right, float bottom) :CollisionBase(CollisionTag::SimpleRect)
			{
				leftTop = PointF(left, top);
				rightBottom = PointF(right, bottom);
			}

			SimpleRectF(const PointF& _leftTop, const PointF& _rightBottom) :CollisionBase(CollisionTag::SimpleRect)
			{
				leftTop = _leftTop;
				rightBottom = _rightBottom;
			}

			SimpleRectF(const PointF& center, float width, float height) :CollisionBase(CollisionTag::SimpleRect)
			{
				float hw = width * 0.5f;
				float hh = height * 0.5f;

				leftTop.x = center.x - hw;
				leftTop.y = center.y + hh;
				rightBottom.x = center.x + hw;
				rightBottom.y = center.y - hh;
			}

			PointF leftTop;		//左上の座標
			PointF rightBottom; //右下の座標
		};

		//
		//線分
		//
		struct CORE2D_COLLISION_CLASS LineF : public CollisionBase
		{

			LineF():CollisionBase(CollisionTag::Line), start(),end(){};

			LineF(const PointF& _start, const PointF& _end):CollisionBase(CollisionTag::Line)
			{
				start = _start;
				end = _end;
			}

			PointF start;//開始位置
			PointF end;	//終了位置
		};
		
		//
		//円
		//
		struct CORE2D_COLLISION_CLASS CircleF : public CollisionBase
		{

			CircleF():CollisionBase(CollisionTag::Circle),center(),radius(0.f){}

			CircleF(const PointF& _center, float _radius):CollisionBase(CollisionTag::Circle)
			{
				center = _center;
				radius = _radius;
			}

			PointF center;	//中心
			float radius;	//半径
		};

		//回転拡縮対応矩形
		/*
		*	1-------4
		*	|		|
		*	|		|
		*	2-------3
		* 
		*	上記の順番で頂点情報を持っている
		*/
		class CORE2D_COLLISION_CLASS RectF : public CollisionBase
		{
		public:
			RectF();
			explicit RectF(const SimpleRectF& rect);
			explicit RectF(const PointF& center, float width, float height);

			virtual ~RectF();

			//頂点座標の取得
			const PointF* getPoint(int index) const;

			//中心座標の取得
			const float getCenterX() const;
			const float getCenterY() const;

			//スケールの取得
			const float getScaleX() const;
			const float getScaleY() const;

			//回転(ラジアン)の取得
			const float getRotation() const;

			//回転(度)の取得
			const float getRotationDegree() const;

			//位置の設定
			void position(float x, float y);
			void setPosition(float x, float y);
			void move(float addX, float addY);

			//スケールの設定
			void scale(float scaleX, float scaleY);
			void addScale(float addX, float addY);

			//回転の設定(ラジアン)
			void rotation(float rad);
			void addRotation(float addRad);

			//回転の設定(度)
			void rotationDegree(float degree);
			void addRotationDegree(float addDegree);

			//位置、拡縮、回転の一斉計算
			void calc(float centerX, float centerY, float scaleX = 1.0f, float scaleY = 1.0f, float rad = 0.f);


			//初期設定
			void setup(const PointF& center, float width, float height);

		private:
			//コピーの禁止
			RectF(const RectF&) = delete;
			RectF& operator=(const RectF&) = delete;

		private:
			class Impl;
			Impl* m_Impl;
		};
		
	};
}

#endif


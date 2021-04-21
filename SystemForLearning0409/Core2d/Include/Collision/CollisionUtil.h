#pragma once

#ifndef __COLLISION_UTIL_H__
#define __COLLISION_UTIL_H__

#ifdef CORE2D_EXPORTS
#define CORE2D_COLLISION_UTIL __declspec(dllexport)
#else
#define CORE2D_COLLISION_UTIL __declspec(dllimport)
#endif

namespace core2d
{
	namespace Collision
	{

		class CollisionBase;
		struct PointF;
		struct LineF;
		struct SimpleRectF;
		struct CircleF;
		class RectF;
		/*=================================================================
		*
		* 衝突していた場合はtrueを返す関数群
		*
		===================================================================*/
		/*==============================================================
		* 点
		================================================================*/
		//点と点
		CORE2D_COLLISION_UTIL bool checkHitPointAndPoint(const PointF& point1, const PointF& point2);

		//点と単純矩形
		CORE2D_COLLISION_UTIL bool checkHitPointAndSimpleRect(const PointF& point, const SimpleRectF& rect);

		//点と線分
		CORE2D_COLLISION_UTIL bool checkHitPointAndLine(const PointF& point, const LineF& line);

		//点と円
		CORE2D_COLLISION_UTIL bool checkHitPointAndCircle(const PointF& point, const CircleF& circle);

		//点と矩形
		CORE2D_COLLISION_UTIL bool checkHitPointAndRect(const PointF& point, const RectF& rect);

		//内部で相手の形状を判定する
		CORE2D_COLLISION_UTIL bool checkHitPointAndBase(const PointF& point, CollisionBase& base);

		/*==============================================================
		* 単純矩形
		================================================================*/
		//単純矩形と点
		CORE2D_COLLISION_UTIL bool checkHitSimpleRectAndPoint(const SimpleRectF& rect, const PointF& point);

		//単純矩形と単純矩形
		CORE2D_COLLISION_UTIL bool checkHitSimpleRectAndSimpleRect(const SimpleRectF& rect1, const SimpleRectF& rect2);

		//単純矩形と線分
		CORE2D_COLLISION_UTIL bool checkHitSimpleRectAndLine(const SimpleRectF& rect, const LineF& line);

		//単純矩形と円
		CORE2D_COLLISION_UTIL bool checkHitSimpleRectAndCircle(const SimpleRectF& rect, const CircleF& circle);

		//単純矩形と矩形
		CORE2D_COLLISION_UTIL bool checkHitSimpleRectAndRect(const SimpleRectF& simpleRect, const RectF& rect);

		//内部で相手の形状を判定する
		CORE2D_COLLISION_UTIL bool checkHitSimpleRectAndBase(const SimpleRectF& simpleRect, CollisionBase& base);

		/*==============================================================
		* 線分
		================================================================*/
		//線分と点
		CORE2D_COLLISION_UTIL bool checkHitLineAndPoint(const LineF& line, const PointF& point);

		//線分と単純矩形
		CORE2D_COLLISION_UTIL bool checkHitLineAndSimpleRect(const LineF& line, const SimpleRectF& rect);

		//線分と線分
		CORE2D_COLLISION_UTIL bool checkHitLineAndLine(const LineF& line1, const LineF& line2);

		//線分と円
		CORE2D_COLLISION_UTIL bool checkHitLineAndCircle(const LineF& line, const CircleF& circle);

		//線分と矩形
		CORE2D_COLLISION_UTIL bool checkHitLineAndRect(const LineF& line, const RectF& rect);

		//内部で相手の形状を判定する
		CORE2D_COLLISION_UTIL bool checkHitLineAndBase(const LineF& line, CollisionBase& base);

		/*==============================================================
		* 円
		================================================================*/
		//円と点
		CORE2D_COLLISION_UTIL bool checkHitCircleAndPoint(const CircleF& circle, const PointF& point);

		//円と単純矩形
		CORE2D_COLLISION_UTIL bool checkHitCircleAndSimpleRect(const CircleF& circle, const SimpleRectF& rect);

		//円と線分
		CORE2D_COLLISION_UTIL bool checkHitCircleAndLine(const CircleF& circle, const LineF& line);

		//円と円
		CORE2D_COLLISION_UTIL bool checkHitCircleAndCircle(const CircleF& circle1, const CircleF& circle2);

		//円と矩形
		CORE2D_COLLISION_UTIL bool checkHitCircleAndRect(const CircleF& circle, const RectF& rect);

		//内部で相手の形状を判定する
		CORE2D_COLLISION_UTIL bool checkHitCircleAndBase(const CircleF& circle, CollisionBase& base);

		/*==============================================================
		* 矩形
		================================================================*/
		//矩形と点
		CORE2D_COLLISION_UTIL bool checkHitRectAndPoint(const RectF& rect, const PointF& point);

		//矩形と単純矩形
		CORE2D_COLLISION_UTIL bool checkHitRectAndSimpleRect(const RectF& rect, const SimpleRectF& simpleRect);

		//矩形と線分
		CORE2D_COLLISION_UTIL bool checkHitRectAndLine(const RectF& rect, const LineF& line);

		//矩形と円
		CORE2D_COLLISION_UTIL bool checkHitRectAndCircle(const RectF& rect, const CircleF& circle);

		//矩形と矩形
		CORE2D_COLLISION_UTIL bool checkHitRectAndRect(const RectF& rect1, const RectF& rect2);

		//内部で相手の形状を判定する
		CORE2D_COLLISION_UTIL bool checkHitRectAndBase(const RectF& rect, CollisionBase& base);

		/*==============================================================
		* 内部でコリジョンの種類を判定して衝突を確認する
		================================================================*/
		CORE2D_COLLISION_UTIL bool checkHit(CollisionBase& col1, CollisionBase& col2);
	}
}

#endif
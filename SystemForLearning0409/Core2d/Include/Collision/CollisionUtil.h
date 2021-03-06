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
		* ÕËµÄ¢½êÍtrueðÔ·ÖQ
		*
		===================================================================*/
		/*==============================================================
		* _
		================================================================*/
		//_Æ_
		CORE2D_COLLISION_UTIL bool checkHitPointAndPoint(const PointF& point1, const PointF& point2);

		//_ÆPé`
		CORE2D_COLLISION_UTIL bool checkHitPointAndSimpleRect(const PointF& point, const SimpleRectF& rect);

		//_Æüª
		CORE2D_COLLISION_UTIL bool checkHitPointAndLine(const PointF& point, const LineF& line);

		//_Æ~
		CORE2D_COLLISION_UTIL bool checkHitPointAndCircle(const PointF& point, const CircleF& circle);

		//_Æé`
		CORE2D_COLLISION_UTIL bool checkHitPointAndRect(const PointF& point, const RectF& rect);

		//àÅèÌ`óð»è·é
		CORE2D_COLLISION_UTIL bool checkHitPointAndBase(const PointF& point, CollisionBase& base);

		/*==============================================================
		* Pé`
		================================================================*/
		//Pé`Æ_
		CORE2D_COLLISION_UTIL bool checkHitSimpleRectAndPoint(const SimpleRectF& rect, const PointF& point);

		//Pé`ÆPé`
		CORE2D_COLLISION_UTIL bool checkHitSimpleRectAndSimpleRect(const SimpleRectF& rect1, const SimpleRectF& rect2);

		//Pé`Æüª
		CORE2D_COLLISION_UTIL bool checkHitSimpleRectAndLine(const SimpleRectF& rect, const LineF& line);

		//Pé`Æ~
		CORE2D_COLLISION_UTIL bool checkHitSimpleRectAndCircle(const SimpleRectF& rect, const CircleF& circle);

		//Pé`Æé`
		CORE2D_COLLISION_UTIL bool checkHitSimpleRectAndRect(const SimpleRectF& simpleRect, const RectF& rect);

		//àÅèÌ`óð»è·é
		CORE2D_COLLISION_UTIL bool checkHitSimpleRectAndBase(const SimpleRectF& simpleRect, CollisionBase& base);

		/*==============================================================
		* üª
		================================================================*/
		//üªÆ_
		CORE2D_COLLISION_UTIL bool checkHitLineAndPoint(const LineF& line, const PointF& point);

		//üªÆPé`
		CORE2D_COLLISION_UTIL bool checkHitLineAndSimpleRect(const LineF& line, const SimpleRectF& rect);

		//üªÆüª
		CORE2D_COLLISION_UTIL bool checkHitLineAndLine(const LineF& line1, const LineF& line2);

		//üªÆ~
		CORE2D_COLLISION_UTIL bool checkHitLineAndCircle(const LineF& line, const CircleF& circle);

		//üªÆé`
		CORE2D_COLLISION_UTIL bool checkHitLineAndRect(const LineF& line, const RectF& rect);

		//àÅèÌ`óð»è·é
		CORE2D_COLLISION_UTIL bool checkHitLineAndBase(const LineF& line, CollisionBase& base);

		/*==============================================================
		* ~
		================================================================*/
		//~Æ_
		CORE2D_COLLISION_UTIL bool checkHitCircleAndPoint(const CircleF& circle, const PointF& point);

		//~ÆPé`
		CORE2D_COLLISION_UTIL bool checkHitCircleAndSimpleRect(const CircleF& circle, const SimpleRectF& rect);

		//~Æüª
		CORE2D_COLLISION_UTIL bool checkHitCircleAndLine(const CircleF& circle, const LineF& line);

		//~Æ~
		CORE2D_COLLISION_UTIL bool checkHitCircleAndCircle(const CircleF& circle1, const CircleF& circle2);

		//~Æé`
		CORE2D_COLLISION_UTIL bool checkHitCircleAndRect(const CircleF& circle, const RectF& rect);

		//àÅèÌ`óð»è·é
		CORE2D_COLLISION_UTIL bool checkHitCircleAndBase(const CircleF& circle, CollisionBase& base);

		/*==============================================================
		* é`
		================================================================*/
		//é`Æ_
		CORE2D_COLLISION_UTIL bool checkHitRectAndPoint(const RectF& rect, const PointF& point);

		//é`ÆPé`
		CORE2D_COLLISION_UTIL bool checkHitRectAndSimpleRect(const RectF& rect, const SimpleRectF& simpleRect);

		//é`Æüª
		CORE2D_COLLISION_UTIL bool checkHitRectAndLine(const RectF& rect, const LineF& line);

		//é`Æ~
		CORE2D_COLLISION_UTIL bool checkHitRectAndCircle(const RectF& rect, const CircleF& circle);

		//é`Æé`
		CORE2D_COLLISION_UTIL bool checkHitRectAndRect(const RectF& rect1, const RectF& rect2);

		//àÅèÌ`óð»è·é
		CORE2D_COLLISION_UTIL bool checkHitRectAndBase(const RectF& rect, CollisionBase& base);

		/*==============================================================
		* àÅRWÌíÞð»èµÄÕËðmF·é
		================================================================*/
		CORE2D_COLLISION_UTIL bool checkHit(CollisionBase& col1, CollisionBase& col2);
	}
}

#endif
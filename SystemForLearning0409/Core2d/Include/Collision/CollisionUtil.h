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
		* �Փ˂��Ă����ꍇ��true��Ԃ��֐��Q
		*
		===================================================================*/
		/*==============================================================
		* �_
		================================================================*/
		//�_�Ɠ_
		CORE2D_COLLISION_UTIL bool checkHitPointAndPoint(const PointF& point1, const PointF& point2);

		//�_�ƒP����`
		CORE2D_COLLISION_UTIL bool checkHitPointAndSimpleRect(const PointF& point, const SimpleRectF& rect);

		//�_�Ɛ���
		CORE2D_COLLISION_UTIL bool checkHitPointAndLine(const PointF& point, const LineF& line);

		//�_�Ɖ~
		CORE2D_COLLISION_UTIL bool checkHitPointAndCircle(const PointF& point, const CircleF& circle);

		//�_�Ƌ�`
		CORE2D_COLLISION_UTIL bool checkHitPointAndRect(const PointF& point, const RectF& rect);

		//�����ő���̌`��𔻒肷��
		CORE2D_COLLISION_UTIL bool checkHitPointAndBase(const PointF& point, CollisionBase& base);

		/*==============================================================
		* �P����`
		================================================================*/
		//�P����`�Ɠ_
		CORE2D_COLLISION_UTIL bool checkHitSimpleRectAndPoint(const SimpleRectF& rect, const PointF& point);

		//�P����`�ƒP����`
		CORE2D_COLLISION_UTIL bool checkHitSimpleRectAndSimpleRect(const SimpleRectF& rect1, const SimpleRectF& rect2);

		//�P����`�Ɛ���
		CORE2D_COLLISION_UTIL bool checkHitSimpleRectAndLine(const SimpleRectF& rect, const LineF& line);

		//�P����`�Ɖ~
		CORE2D_COLLISION_UTIL bool checkHitSimpleRectAndCircle(const SimpleRectF& rect, const CircleF& circle);

		//�P����`�Ƌ�`
		CORE2D_COLLISION_UTIL bool checkHitSimpleRectAndRect(const SimpleRectF& simpleRect, const RectF& rect);

		//�����ő���̌`��𔻒肷��
		CORE2D_COLLISION_UTIL bool checkHitSimpleRectAndBase(const SimpleRectF& simpleRect, CollisionBase& base);

		/*==============================================================
		* ����
		================================================================*/
		//�����Ɠ_
		CORE2D_COLLISION_UTIL bool checkHitLineAndPoint(const LineF& line, const PointF& point);

		//�����ƒP����`
		CORE2D_COLLISION_UTIL bool checkHitLineAndSimpleRect(const LineF& line, const SimpleRectF& rect);

		//�����Ɛ���
		CORE2D_COLLISION_UTIL bool checkHitLineAndLine(const LineF& line1, const LineF& line2);

		//�����Ɖ~
		CORE2D_COLLISION_UTIL bool checkHitLineAndCircle(const LineF& line, const CircleF& circle);

		//�����Ƌ�`
		CORE2D_COLLISION_UTIL bool checkHitLineAndRect(const LineF& line, const RectF& rect);

		//�����ő���̌`��𔻒肷��
		CORE2D_COLLISION_UTIL bool checkHitLineAndBase(const LineF& line, CollisionBase& base);

		/*==============================================================
		* �~
		================================================================*/
		//�~�Ɠ_
		CORE2D_COLLISION_UTIL bool checkHitCircleAndPoint(const CircleF& circle, const PointF& point);

		//�~�ƒP����`
		CORE2D_COLLISION_UTIL bool checkHitCircleAndSimpleRect(const CircleF& circle, const SimpleRectF& rect);

		//�~�Ɛ���
		CORE2D_COLLISION_UTIL bool checkHitCircleAndLine(const CircleF& circle, const LineF& line);

		//�~�Ɖ~
		CORE2D_COLLISION_UTIL bool checkHitCircleAndCircle(const CircleF& circle1, const CircleF& circle2);

		//�~�Ƌ�`
		CORE2D_COLLISION_UTIL bool checkHitCircleAndRect(const CircleF& circle, const RectF& rect);

		//�����ő���̌`��𔻒肷��
		CORE2D_COLLISION_UTIL bool checkHitCircleAndBase(const CircleF& circle, CollisionBase& base);

		/*==============================================================
		* ��`
		================================================================*/
		//��`�Ɠ_
		CORE2D_COLLISION_UTIL bool checkHitRectAndPoint(const RectF& rect, const PointF& point);

		//��`�ƒP����`
		CORE2D_COLLISION_UTIL bool checkHitRectAndSimpleRect(const RectF& rect, const SimpleRectF& simpleRect);

		//��`�Ɛ���
		CORE2D_COLLISION_UTIL bool checkHitRectAndLine(const RectF& rect, const LineF& line);

		//��`�Ɖ~
		CORE2D_COLLISION_UTIL bool checkHitRectAndCircle(const RectF& rect, const CircleF& circle);

		//��`�Ƌ�`
		CORE2D_COLLISION_UTIL bool checkHitRectAndRect(const RectF& rect1, const RectF& rect2);

		//�����ő���̌`��𔻒肷��
		CORE2D_COLLISION_UTIL bool checkHitRectAndBase(const RectF& rect, CollisionBase& base);

		/*==============================================================
		* �����ŃR���W�����̎�ނ𔻒肵�ďՓ˂��m�F����
		================================================================*/
		CORE2D_COLLISION_UTIL bool checkHit(CollisionBase& col1, CollisionBase& col2);
	}
}

#endif
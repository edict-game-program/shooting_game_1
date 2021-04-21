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
		//�R���W�����^�O
		//
		enum class CollisionTag
		{
			None,

			Point,			//�_
			SimpleRect,		//�P����`
			Line,			//��
			Circle,			//�~
			Rect,			//��]��`
		};

		//
		//�R���W�����K��N���X
		//
		class CORE2D_COLLISION_CLASS CollisionBase
		{
		public:
			CollisionBase() { m_Tag = CollisionTag::None; m_Number = 0; m_Active = true; }
			explicit CollisionBase(CollisionTag tag) { m_Tag = tag; m_Number = 0; m_Active = true; }

			//�^�O�̎擾
			const CollisionTag getTag() const { return m_Tag; } 

			//���ʗp�̔ԍ�
			const unsigned int getNumber() { return m_Number; }
			void setNumber(unsigned int number) { m_Number = number; }

			//�L���E�����t���O
			void setActive(bool active) { m_Active = active; }
			bool isActive() { return m_Active; }

			virtual ~CollisionBase(){};

		private:
			CollisionTag m_Tag;
			unsigned int m_Number;

			bool m_Active;
		};


		//
		//�_
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
		//�P����`
		// �ړ��̂�
		// ��]�A�X�P�[���̑Ή��͖������A�����͏�������
		//
		struct CORE2D_COLLISION_CLASS SimpleRectF : public CollisionBase
		{
			SimpleRectF():CollisionBase(CollisionTag::SimpleRect), leftTop(), rightBottom(){}

			//float left;		//����[��x���W
			//float top;		//����[��y���W
			//float right;		//�E���[��x���W
			//float bottom;		//�E���[��y���W
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

			PointF leftTop;		//����̍��W
			PointF rightBottom; //�E���̍��W
		};

		//
		//����
		//
		struct CORE2D_COLLISION_CLASS LineF : public CollisionBase
		{

			LineF():CollisionBase(CollisionTag::Line), start(),end(){};

			LineF(const PointF& _start, const PointF& _end):CollisionBase(CollisionTag::Line)
			{
				start = _start;
				end = _end;
			}

			PointF start;//�J�n�ʒu
			PointF end;	//�I���ʒu
		};
		
		//
		//�~
		//
		struct CORE2D_COLLISION_CLASS CircleF : public CollisionBase
		{

			CircleF():CollisionBase(CollisionTag::Circle),center(),radius(0.f){}

			CircleF(const PointF& _center, float _radius):CollisionBase(CollisionTag::Circle)
			{
				center = _center;
				radius = _radius;
			}

			PointF center;	//���S
			float radius;	//���a
		};

		//��]�g�k�Ή���`
		/*
		*	1-------4
		*	|		|
		*	|		|
		*	2-------3
		* 
		*	��L�̏��ԂŒ��_���������Ă���
		*/
		class CORE2D_COLLISION_CLASS RectF : public CollisionBase
		{
		public:
			RectF();
			explicit RectF(const SimpleRectF& rect);
			explicit RectF(const PointF& center, float width, float height);

			virtual ~RectF();

			//���_���W�̎擾
			const PointF* getPoint(int index) const;

			//���S���W�̎擾
			const float getCenterX() const;
			const float getCenterY() const;

			//�X�P�[���̎擾
			const float getScaleX() const;
			const float getScaleY() const;

			//��](���W�A��)�̎擾
			const float getRotation() const;

			//��](�x)�̎擾
			const float getRotationDegree() const;

			//�ʒu�̐ݒ�
			void position(float x, float y);
			void setPosition(float x, float y);
			void move(float addX, float addY);

			//�X�P�[���̐ݒ�
			void scale(float scaleX, float scaleY);
			void addScale(float addX, float addY);

			//��]�̐ݒ�(���W�A��)
			void rotation(float rad);
			void addRotation(float addRad);

			//��]�̐ݒ�(�x)
			void rotationDegree(float degree);
			void addRotationDegree(float addDegree);

			//�ʒu�A�g�k�A��]�̈�Čv�Z
			void calc(float centerX, float centerY, float scaleX = 1.0f, float scaleY = 1.0f, float rad = 0.f);


			//�����ݒ�
			void setup(const PointF& center, float width, float height);

		private:
			//�R�s�[�̋֎~
			RectF(const RectF&) = delete;
			RectF& operator=(const RectF&) = delete;

		private:
			class Impl;
			Impl* m_Impl;
		};
		
	};
}

#endif


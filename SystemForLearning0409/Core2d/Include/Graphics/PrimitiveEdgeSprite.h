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
	// �֊s�\���X�v���C�g�̊��N���X
	class CORE2D_PRIMITIVEEDGESPRITE_CLASS PrimitiveEdgeSprite : public DrawObject
	{
	public:
		// �j��
		static void destroy(PrimitiveEdgeSprite* p);

	protected:
		PrimitiveEdgeSprite(void);
		virtual ~PrimitiveEdgeSprite(void);

	public:
		// �\���p�����[�^�ݒ�
		virtual void setPosition(float x, float y);
		virtual void setScale(float x, float y);
		virtual void setRotation(float degree);
		virtual void setColor(float r, float g, float b, float a = 1.0f);

	private:
		//�R�s�[�֎~
		PrimitiveEdgeSprite(const PrimitiveEdgeSprite&) = delete;
		PrimitiveEdgeSprite& operator=(const PrimitiveEdgeSprite&) = delete;

	};

	// �~�̗֊s����`���N���X
	class CORE2D_PRIMITIVEEDGESPRITE_CLASS CircleEdgeSprite : public PrimitiveEdgeSprite
	{
	public:
		// �j��
		static void destroy(CircleEdgeSprite* p);

		// �w�肵�����a�ō쐬
		CircleEdgeSprite(float radius);

	private:
		virtual ~CircleEdgeSprite(void);

		bool render(Camera* camera) final;

	public:
		// �\���p�����[�^�ݒ�
		void setPosition(float x, float y) final;
		void setScale(float x, float y) final;
		void setRotation(float degree) final;
		void setColor(float r, float g, float b, float a = 1.0f) final;

		// ���a���擾
		float getRadius(void);

	private:
		// �f�t�H���g�R���X�g���N�^�Ăяo���֎~
		CircleEdgeSprite() = delete;
		//�R�s�[�֎~
		CircleEdgeSprite(const CircleEdgeSprite&) = delete;
		CircleEdgeSprite& operator=(const CircleEdgeSprite&) = delete;

	private:
		class Impl;
		Impl* m_impl;

	};

	// �l�p�̗֊s����`���N���X
	class CORE2D_PRIMITIVEEDGESPRITE_CLASS BoxEdgeSprite : public PrimitiveEdgeSprite
	{
	public:
		// �j��
		static void destroy(BoxEdgeSprite* p);

		// �w�肵�����ƍ����̎l�p���쐬
		BoxEdgeSprite(float width, float height);

	private:
		virtual ~BoxEdgeSprite(void);

		bool render(Camera* camera) final;

	public:
		// �\���p�����[�^�ݒ�
		void setPosition(float x, float y) final;
		void setScale(float x, float y) final;
		void setRotation(float degree) final;
		void setColor(float r, float g, float b, float a = 1.0f) final;

		// ���ƍ������擾
		float getWidth(void);
		float getHeight(void);

	private:
		// �f�t�H���g�R���X�g���N�^�Ăяo���֎~
		BoxEdgeSprite() = delete;
		//�R�s�[�֎~
		BoxEdgeSprite(const BoxEdgeSprite&) = delete;
		BoxEdgeSprite& operator=(const BoxEdgeSprite&) = delete;

	private:
		class Impl;
		Impl* m_impl;

	};

	// ������`���N���X
	class CORE2D_PRIMITIVEEDGESPRITE_CLASS LineSprite : public PrimitiveEdgeSprite
	{
	public:
		// �j��
		static void destroy(LineSprite* p);
		// start��end�����Ԑ������쐬
		LineSprite(float startX, float startY, float endX, float endY);

	private:
		virtual ~LineSprite(void);

		bool render(Camera* camera) final;

	public:
		// �\���p�����[�^�ݒ�
		void setPosition(float x, float y) final;
		void setScale(float x, float y) final;
		void setRotation(float degree) final;
		void setColor(float r, float g, float b, float a = 1.0f) final;

		// ������ݒ�
		void setLine(float startX, float startY, float endX, float endY);
		void setStartPosition(float x, float y);
		void setEndPosition(float x, float y);

	private:
		// �f�t�H���g�R���X�g���N�^�Ăяo���֎~
		LineSprite() = delete;
		//�R�s�[�֎~
		LineSprite(const LineSprite&) = delete;
		LineSprite& operator=(const LineSprite&) = delete;

	private:
		class Impl;
		Impl* m_impl;

	};

	// �_��`���N���X
	class CORE2D_PRIMITIVEEDGESPRITE_CLASS PointSprite : public PrimitiveEdgeSprite
	{
	public:
		// �j��
		static void destroy(PointSprite* p);

		PointSprite(float x, float y);

	private:
		virtual ~PointSprite(void);

		bool render(Camera* camera) final;

	public:
		// �\���p�����[�^�ݒ�
		void setPosition(float x, float y) final;
		void setColor(float r, float g, float b, float a = 1.0f) final;

	private:
		// �f�t�H���g�R���X�g���N�^�Ăяo���֎~
		PointSprite() = delete;
		//�R�s�[�֎~
		PointSprite(const PointSprite&) = delete;
		PointSprite& operator=(const PointSprite&) = delete;

	private:
		class Impl;
		Impl* m_impl;

	};

}

#endif
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
	// �O���錾
	class Camera;

	// �`�敨�̊��N���X
	class CORE2D_DRAWOBJECT_CLASS DrawObject
	{
	protected:
		DrawObject();
		virtual ~DrawObject();

		// �p����ŕ`�揈���̒��g���L�q
		virtual bool render(Camera* camera) = 0;

	public:
		// �����ԍ����擾
		unsigned long long getGenNo(void);
		// �`��D��x��ݒ�
		void setPriority(unsigned int priority);
		// �`��D��x���擾
		unsigned int getPriority(void);
		// �`����s�t���O��ݒ�
		void setActive(bool flag = true);
		// �`����s�̏�Ԃ��擾
		bool isActive(void);
		// �j����\��
		void reserveDestroy(void);
		// �j�����\�񂳂�Ă��邩���擾
		bool isReservedDestroy(void);

	protected:
		// ��r�֐�
		static bool compare(DrawObject* lhs, DrawObject* rhs);

		// Z���W���擾
		float getZ(void);

		// �R�s�[�֎~
		DrawObject(const DrawObject&) = delete;
		DrawObject& operator=(const DrawObject&) = delete;

	private:
		class Impl;
		Impl* m_impl;

		friend class GraphicsSystem;
	};

}

#endif // __CORE2D_DRAWOBJECT_HEADER__